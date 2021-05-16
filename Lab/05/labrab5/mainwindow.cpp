#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QImage>
#include <QFileDialog>
#include <QMessageBox>
#include <QBitArray>
#include <QFile>
#include <QTextStream>

#define NDEBUG

void setBit(QImage &img, int index, bool val) {
    int pixelIndex = index / 3;
    int x = pixelIndex % img.width();
    int y = pixelIndex / img.width();
#ifndef NDEBUG
    if (y >= img.height())
        throw std::out_of_range("выход за пределы картинки");
#endif
    switch (index % 3) {
    case 0:
        img.setPixel(x, y, (img.pixel(x, y) & ~0x010000) | (val << 16));
    case 1:
        img.setPixel(x, y, (img.pixel(x, y) & ~0x000100) | (val << 8));
    default:
        img.setPixel(x, y, (img.pixel(x, y) & ~0x000001) | val);
    }
}

bool getBit(const QImage &img, int index) {
    int pixelIndex = index / 3;

    int x = pixelIndex % img.width();
    int y = pixelIndex / img.width();
#ifndef NDEBUG
    if (y >= img.height())
        throw std::out_of_range("индекс бита выходит за пределы картинки");
#endif
    switch (index % 3) {
    case 0:
        return (img.pixel(x, y) >> 16) & 1;
    case 1:
        return (img.pixel(x, y) >> 8) & 1;
    default:
        return img.pixel(x, y) & 1;
    }
    Q_UNREACHABLE();
}
QByteArray readBytes(const QImage& img, size_t begin, size_t length) {
    QByteArray byteArray;
    char buf = 0;
    size_t end = (begin + length) * 8;
#ifndef NDEBUG
    if (static_cast<size_t>(img.width() * img.height() * 8 * 3) <= end)
        throw std::out_of_range("попытка прочитать биты вне картинки");
#endif
    for (size_t i = begin * 8; i < end; ++i) {
        buf = (buf << 1) | getBit(img, i);
        if (i % 8 == 7) {
            byteArray.push_back(buf);
            buf = 0;
        }
    }
    return byteArray;
}

void writeBytes(QImage& img, size_t begin, QByteArray& byteArray) {
    size_t end = (begin + byteArray.size()) * 8;

#ifndef NDEBUG
    if (static_cast<size_t>(img.width() * img.height() * 8 * 3) <= end)
        throw std::out_of_range("попытка записать биты вне картинки");
#endif

    for (size_t i = begin * 8; i < end; ++i) {
        setBit(img, i, (byteArray[i / 8] >> (7 - i % 8)) & 1);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->loadImgButton, &QPushButton::clicked, this, &MainWindow::loading_image);
    connect(ui->saveImgButton, &QPushButton::clicked, this, &MainWindow::saving_image);
    connect(ui->encodeMsgButton, &QPushButton::clicked, this, &MainWindow::encoding_text);
    connect(ui->decodeMsgButton, &QPushButton::clicked, this, &MainWindow::decoding_text);
    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, this, &MainWindow::Changed_the_message);
    ui->outputLabel->setWordWrap(true);
    imageCapacity = -1; // по-умолчанию размер картинки невалидный
    usedBytes = 0;
    imageLoaded = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loading_image()    //Загружаем изображение
{
    imageLoaded = false;
    QString filepath = QFileDialog::getOpenFileName(this, tr("Открыть изображение"), "", tr("Допустимые форматы (*.png)"));
    if (!img.load(filepath, "PNG")) {
        show_the_Message(tr("Изображение не загружено"));
        return;
    }
    img.convertTo(QImage::Format_ARGB32);
    imageCapacity = (img.width() * img.height() * 3) / 8 - marker.size() - messageInfoLength;
    show_the_Message(tr("Изображение успешно загружено"));
    imageLoaded = true;
}

void MainWindow::saving_image() //Сохраняем изображение
{
    if (!imageLoaded) {
        show_the_Message(tr("Изображение не загружено"));
        return;
    }
    QString filepath = QFileDialog::getSaveFileName(this, tr("Сохранить изображение"), "", tr("Допустимые форматы (*.png)"));
    if (img.save(filepath, "PNG")) {
        show_the_Message(tr("Изображение сохранено").arg(filepath));
    } else {
        show_the_Message(tr("Изображение не сохранено"));
    }
}

void MainWindow::encoding_text()    //Кодируем введенный текст
{
    if (!imageLoaded) { //Если нет изображения
        show_the_Message(tr("Изображение не загружено!"));
        return;
    }
    usedBytes = ui->plainTextEdit->toPlainText().toUtf8().size();
    if (imageCapacity < usedBytes) {    //Если не хватает памяти
        show_the_Message(tr("Слишком мало места!"));
        return;
    }
    QByteArray byteArray;
    byteArray.push_back(marker);
    for (int i = messageInfoLength - 1; i >= 0; --i) {
        byteArray.push_back((usedBytes >> i*8) & 0xff);
    }
    byteArray.push_back(ui->plainTextEdit->toPlainText().toUtf8());
    writeBytes(img, 0, byteArray);
    show_the_Message(tr("Сообщение загружено в изображение!"));
}

void MainWindow::decoding_text()           //Проводим раскодировку текста
{
    if (!imageLoaded) { //Если нет изображения
        show_the_Message(tr("Изображение не загружено"));
        return;
    }
    int headerSize = marker.size() + messageInfoLength;
    QByteArray byteArray;
    byteArray = readBytes(img, 0, headerSize);
    for (size_t i = 0; i < marker.size(); ++i) {
        if (marker[i] != byteArray[i]) { //Если нет закодированного текста
            show_the_Message(tr("Сообщение не обнаружено"));
            return;
        }
    }
    size_t messageSize = 0;
    for (size_t i = marker.size(); i < marker.size() + messageInfoLength; ++i) {
        messageSize = (messageSize << 8) + static_cast<unsigned char>(byteArray[i]);
    }
    if (messageSize > imageCapacity) {
        show_the_Message(tr("Размер сообщения превышает размер изображения"));
        return;
    }
    byteArray = readBytes(img, headerSize, messageSize);
    QString text = QString::fromUtf8(byteArray);
    ui->plainTextEdit->setPlainText(text);
    show_the_Message(tr("Присутствует сообщение длиной в %1 байт").arg(messageSize));
}

void MainWindow::Changed_the_message()         //Вводим текст
{
    if (imageCapacity < 0) return;
    usedBytes = ui->plainTextEdit->toPlainText().toUtf8().size();
    if (imageCapacity < usedBytes) {       //Если не хватает памяти
        show_the_Message(tr("Размер сообщения превышен на: %1 байт").arg(usedBytes - imageCapacity));
    } else {
        show_the_Message(tr("%1 байт доступно для ввода").arg(imageCapacity - usedBytes));
    }
}

void MainWindow::show_the_Message(QString msg)        //Выводим текст
{
    ui->outputLabel->setText(msg);
}

