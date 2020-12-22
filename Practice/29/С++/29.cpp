#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

string arr[] = { "math", "phys", "hist", "prog" };

struct Student
{
    string name;
    int group;
    map<string, int> exams;
    map<string, int>::iterator examsInit;
    int n;

    void vvod()
    {
        cout << "Имя: "; cin >> name;
        cout << "Группа: "; cin >> group;
        for (int i = 0; i < 4; i++)
        {
            cout << arr[i] << " категория: ";
            cin >> exams[arr[i]];
        }
        cout << '\n';
    }
};




int main()
{
    setlocale(0, "");
    int n;
    cout << "сколько студентов?\n";
    cin >> n;
    vector<Student> students(n);
    for (auto& student : students)
        student.vvod();
}