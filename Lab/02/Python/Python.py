from flask import Flask, request 
import openpyxl 
import os.path 
import datetime 

app = Flask(__name__)

STORAGE_LEN = 0 
storage = [] 

pwd = os.path.abspath(os.path.dirname(__file__))

@app.route('/', methods=['POST', 'GET'])
def index():
   global storage 
   if request.method == 'POST': 
      storage += [request.json]
      print('req.body:', storage[-1]) 
      if (len(storage) > STORAGE_LEN):
         save_excel() 
         storage = [] 
      return 'OK' 
      
   elif request.method == 'GET':
      return 'Это GET запрос'

# функция сохранения содержимого в эксель
def save_excel():
   global storage 
   
   STORAGE_FILE = os.path.join(pwd, 'data.xlsx') 
  
   book = None
   
   if not os.path.exists(STORAGE_FILE):
      book = openpyxl.Workbook() # создаем пустую книгу
      # добавляем в неё заголовки
      book.active['A1'] = 'N'
      book.active['B1'] = 'User ID'
      book.active['C1'] = 'Datetime'
      book.active['D1'] = 'Item'
      book.active['E1'] = 'Prise'
      book.save(STORAGE_FILE) 
   else: # если же существовал
      book = openpyxl.open(STORAGE_FILE) # то открываем его
   sheet = book.active # устанавливаем первый лист основным
   
   max_row = len(sheet['A']) 
   nowtime = datetime.datetime.now() # берём текущее время
   
   row = max_row + 1 
   for dataset in storage:
      id = dataset['user_id'] 
      check = dataset['check'] 
      
      for item in check: 
         # выводим информацию на лист
         sheet[row][0].value = row - 1
         sheet[row][1].value = id
         sheet[row][2].value = nowtime
         sheet[row][3].value = item['name']
         sheet[row][4].value = item['price']
         row += 1
   
   book.save(STORAGE_FILE) 
   book.close() 



if __name__ == '__main__':
   app.run()
