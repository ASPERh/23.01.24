#include "stu.h"
#include "frac.h"
using namespace std;

class Date {
    unsigned short day;
    unsigned short month;
    long long year;
public:
    Date() : Date(23, 12, 2023) {}

    Date(unsigned short day, unsigned short month, long long year)
    {
        SetDay(day);
        SetMonth(month);
        SetYear(year);
    }
    Date(unsigned short day, unsigned short month) : Date(day, month, 2005) {}


    void PrintDate() const
    {
        cout << day << "." << month << "." << year << "\n";
    }
    void SetDay(unsigned short day)
    {
        if (day == 0 || day > 31) throw "ERROR!!! The day must be from 0 to 31 !!!";
        this->day = day;
    }
    unsigned short GetDay() const
    {
        return day;
    }
    void SetMonth(unsigned short month)
    {
        if (month == 0 || month > 12) throw "ERROR!!! The day must be from 1 to 12 !!!";
        this->month = month;
    }

    unsigned short GetMonth() const
    {
        return month;
    }
    void SetYear(long long year)
    {
        this->year = year;
    }
    long long GetYear() const
    {
        return year;
    }

    operator string()
    {
        return to_string(day) + "." + to_string(month) + "." + to_string(year);
    }
};

class Group {
private:
    int studentCount = 0;
    Student** students = nullptr;
    string groupName;
    string groupSpecialization;
    int classNumber = 2;
    int passingGrade = 7;
    friend ostream& operator << (ostream& o, Group& g);
    friend istream& operator >> (istream& i, Group& g);
public:

    Group() : Group("P26", "Prog") {}

    Group(string groupName, string groupSpecialization)
    {
        SetGroupName(groupName);
        SetGroupSpecialization(groupSpecialization);
    }

    Group(const Group& original)
    {
        this->groupName = original.groupName;
        this->groupSpecialization = original.groupSpecialization;
        this->studentCount = original.studentCount;
        this->students = new Student * [original.studentCount];
        for (int i = 0; i < original.studentCount; i++)
        {
            this->students[i] = new Student(*original.students[i]);
        }
    }

    void ShowGroup()
    {
        cout << "Group: " << groupName << ", Specialization: " << groupSpecialization << "\n";
        cout << "Students:\n";
        for (int i = 0; i < studentCount; i++)
        {
            cout << "Student " << i + 1 << ":\n";
            students[i]->PrintStudent();
            cout << "\n";
        }
    }

    void AddStudent(Student& student)
    {
        Student** temp = new Student * [studentCount + 1];
        for (int i = 0; i < studentCount; i++)
        {
            temp[i] = students[i];
        }
        temp[studentCount] = new Student(student);
        studentCount++;
        delete[] students;
        students = temp;
    }

    void MergeGroup(Group& g2)
    {
        int otherStudentCount = g2.studentCount;

        Student** temp = new Student * [studentCount + otherStudentCount];
        for (int i = 0; i < studentCount; i++)
        {
            temp[i] = students[i];
        }

        for (int i = 0; i < otherStudentCount; i++)
        {
            temp[studentCount + i] = new Student(*g2.students[i]);
        }
        studentCount += otherStudentCount;
        delete[] students;
        students = temp;
    }

    void TransferStudent(int index, Group& g2)
    {
        if (index >= 0 && index < studentCount)
        {
            Student* transfer = students[index];
            Student** temp = new Student * [studentCount - 1];
            int tempIndex = 0;
            for (int i = 0; i < studentCount; i++)
            {
                if (i != index)
                {
                    temp[tempIndex++] = students[i];
                }
            }
            delete students[index];
            delete[] students;
            students = temp;
            studentCount--;
            g2.AddStudent(*transfer);
        }
    }

    void ExpelStudents()
    {
        Student** temp = new Student * [studentCount];
        int index = 0;

        for (int i = 0; i < studentCount; ++i)
        {
            bool passedExam = false;

            for (int j = 0; j < students[i]->GetExamRatesCount(1); ++j)
            {
                if (students[i]->GetExamRatesCount(j) >= passingGrade)
                {
                    passedExam = true;
                    break;
                }
            }

            if (!passedExam)
            {
                cout << "Expelling student " << students[i]->GetName() << " for failing exam.\n";
                delete students[i];
            }
            else
            {
                temp[index++] = students[i];
            }
        }

        delete[] students;
        students = temp;
        studentCount = index;
    }

    void ExpelBadStudent()
    {
        if (studentCount == 0)
        {
            cout << "No students in the group to expel.\n";
            return;
        }

        int minIndex = 0;
        double minAverageGrade = students[0]->CalculateAverageGrade();
        for (int i = 1; i < studentCount; ++i)
        {
            double averageGrade = students[i]->CalculateAverageGrade();
            if (averageGrade < minAverageGrade)
            {
                minIndex = i;
                minAverageGrade = averageGrade;
            }
        }

        cout << "Expelling the least performing student " << students[minIndex]->GetName() << "\n";
        delete students[minIndex];

        for (int i = minIndex; i < studentCount - 1; ++i)
        {
            students[i] = students[i + 1];
        }
        studentCount--;
    }

    void SetGroupName(string groupName)
    {
        this->groupName = groupName;
    }

    string GetGroupName() const
    {
        return groupName;
    }

    void SetGroupSpecialization(string groupSpecialization)
    {
        this->groupSpecialization = groupSpecialization;
    }

    string GetGroupSpecialization() const
    {
        return groupSpecialization;
    }

    void SetPassingGrade(int passingGrade)
    {
        this->passingGrade = passingGrade;
    }

    int GetPassingGrade() const
    {
        return passingGrade;
    }

    void SetStudentCount(int studentCount)
    {
        this->studentCount = studentCount;
    }

    int GetStudentCount() const
    {
        return studentCount;
    }

    operator string()
    {
        return groupName + " " + groupSpecialization + " " + to_string(studentCount) + " students\n";
    }

    ~Group() {
        for (int i = 0; i < studentCount; i++)
        {
            delete students[i];
        }
        delete[] students;
    }

};

istream& operator >> (const istream& i, Student s)
{
    string answer;
    cout << "Какая у тебя фамилия: ";
    cin >> answer;
    s.SetSurname(answer);
    cout << "Как тебя зовут: ";
    cin >> answer;
    s.SetName(answer);
    cout << "Какое у тебя отчество: ";
    cin >> answer;
    s.SetMiddlName(answer);
    return cin;
}

ostream& operator << (ostream& o, Student s)
{
    s.PrintStudent();
    return cout;
}

ostream& operator << (ostream& o, Group& g)
{
    cout << "Group: " << g.groupName << ", Specialization: " << g.groupSpecialization << "\n";
    cout << "Students:\n";
    for (int i = 0; i < g.studentCount; i++)
    {
        cout << "Student " << i + 1 << ":\n";
        g.students[i]->PrintStudent();
        cout << "\n";
    }
    return cout;
}

istream& operator>>(istream& i, Group& g)
{
    cout << "Enter group name: ";
    cin >> g.groupName;
    cout << "Enter group specialization: ";
    cin >> g.groupSpecialization;
    return cin;
}

Group operator + (Group& g, Group& g2)
{
    Group result = g;
    result.MergeGroup(g2);
    return result;
}

bool operator > (Group& g, Group& g2)
{
    if (g.GetStudentCount() > g2.GetStudentCount())
    {
        cout << "First group greater then second\n";
        return true;
    }
    return false;
}

bool operator < (Group& g, Group& g2)
{
    if (g.GetStudentCount() < g2.GetStudentCount())
    {
        cout << "First group less then second\n";
        return true;
    }
    return false;
}

bool operator >= (Group& g, Group& g2)
{
    if (g.GetStudentCount() >= g2.GetStudentCount())
    {
        cout << "First group greater or equal then second\n";
        return true;
    }
    return false;
}

bool operator <= (Group& g, Group& g2)
{
    if (g.GetStudentCount() <= g2.GetStudentCount())
    {
        cout << "First group less or equal then second\n";
        return true;
    }
    return false;
}

bool operator == (Group& g, Group& g2)
{
    if (g.GetStudentCount() == g2.GetStudentCount())
    {
        cout << "First group equal to second\n";
        return true;
    }
    return false;
}

bool operator != (Group& g, Group& g2)
{
    return !(g == g2);
}

bool operator < (Student& s, Student& s2)
{
    if (s.CalculateAverageGrade() < s2.CalculateAverageGrade())
    {
        cout << "The first student has a lower average score than the second\n";
        return true;
    }
    return false;
}

bool operator > (Student& s, Student& s2)
{
    if (s.CalculateAverageGrade() > s2.CalculateAverageGrade())
    {
        cout << "The first student has a higher average score than the second\n";
        return true;
    }
    return false;
}

bool operator <= (Student& s, Student& s2)
{
    if (s.CalculateAverageGrade() <= s2.CalculateAverageGrade())
    {
        cout << "The first student has a lower or equal average score than the second\n";
        return true;
    }
    return false;
}

bool operator >= (Student& s, Student& s2)
{
    if (s.CalculateAverageGrade() >= s2.CalculateAverageGrade())
    {
        cout << "The first student has a higher or equal average score than the second\n";
        return true;
    }
    return false;
}

bool operator == (Student& s, Student& s2)
{
    if (s.CalculateAverageGrade() == s2.CalculateAverageGrade())
    {
        cout << "Students have the same average score\n";
        return true;
    }
    return false;
}

bool operator != (Student& s, Student& s2)
{
    return !(s == s2);
}

Group operator += (Group& g, Student& s)
{
    g.AddStudent(s);
    return g;
}

int operator - (const Date& left, const Date& right)
{
    int days = 0;
    bool leapYear = false;

    for (int i = left.GetYear(); i < right.GetYear(); ++i)
    {
        if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
        {
            leapYear = true;
            days += 366;
        }
        else
        {
            leapYear = false;
            days += 365;
        }
    }

    days += right.GetDay() - left.GetDay();

    for (int i = left.GetMonth(); i < right.GetMonth(); ++i)
    {
        switch (i)
        {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            days += 31;
            break;
        case 4: case 6: case 9: case 11:
            days += 30;
            break;
        case 2:
            if (leapYear)
                days += 29;
            else
                days += 28;
            break;
        }
    }

    return days;
}

int main()
{
    Student s;
    Student s2;
    Student s3;
    Student s4;

    s.AddExam(8);
    s2.AddExam(7);
    s3.AddExam(9);
    s4.AddExam(9);
    s.AddHomeWork(6);
    s2.AddHomeWork(6);
    s3.AddHomeWork(8);
    s4.AddHomeWork(8);

    Group g;
    Group g2("P25", "prog");

    g.AddStudent(s);
    g.AddStudent(s2);

    g2.AddStudent(s3);
    g2.AddStudent(s4);
    g2.AddStudent(s);

    Group c = g + g2;
    cout << c << "\n";

    Date d(23, 1, 2024);
    Date d2(11, 4, 2024);
    int days = d - d2;
    cout << days << "\n";
    cout << "!!!FRACTION PART!!!" << "\n";
    Fraction a(3, 2);
    double x = 1.3;
    Fraction b = x + a;
    cout << b << "\n";
}