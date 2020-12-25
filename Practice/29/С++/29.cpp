#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

string arr[] = { "Math", "Phys", "Hist", "Progg" };

struct Student
{
    string name;
    int group;
    // Math | Phys | Hist | Prog
    map<string, int> exams;
    map<string, int>::iterator examsInit;
    int n;
    void init()
    {
        cout << "Name of students: ";
        cin >> name;
        cout << "Group: ";
        cin >> group;
        for (int i = 0; i < 4; i++)
        {
           cout << arr[i] << " score: ";
           cin >> exams[arr[i]];
        }
        cout << '\n';
    }

};

std::ostream& operator<<(std::ostream& out, Student st)
{
      //Ввод и вывод на английском, потому что корявый вывод русского, даже с локалью
    out << "| Name       | Group |";
    for (int i = 0; i < 4; i++)
    {
        out << std::setw(6) << arr[i] << "|";
    }
    out << '\n';
    out << '|' << std::setw(12) << st.name << '|' << std::setw(7) << st.group << '|';
    for (st.examsInit = st.exams.begin(); st.examsInit != st.exams.end(); st.examsInit++)
    {
        out << std::setw(6) << st.examsInit->second << '|';
    }
    out << '\n';
    return out;
}


int main()
{
    int n;
    cout << "How mant studensts?\n";
    cin >> n;

    vector<Student> students(n);
    for (auto& student : students)
        student.init();
    cout << students[0];
}