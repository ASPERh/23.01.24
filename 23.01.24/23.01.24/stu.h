#pragma once
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

class Student {
    string surname;
    string name;
    string middlename;
    string adress;
    string phonenumber;
    unsigned int countpractic = 0;
    unsigned int counthomework = 0;
    unsigned int countexam = 0;
    int* grade_of_practic = nullptr;
    int* grade_of_homework = nullptr;
    int* grade_of_exam = nullptr;

public:
    Student(const Student& original);

    Student();

    Student(string surname, string name, string middlname, string adress, string phonenumber);

    Student(string surname, string name, string middlname, string adress);

    ~Student();

    void PrintStudent() const;

    void AddPractic(int newcountry);

    void PrintPractic() const;

    int GePracticRatesCount(unsigned int index) const;

    void AddHomeWork(int newcountry);

    double CalculateAverageGrade() const;

    void PrintHomeWork() const;

    int GetHomeWorkRatesCount(unsigned int index) const;

    void AddExam(int newcountry);

    void PrintExam() const;

    int GetExamRatesCount(unsigned int index) const;

    void SetSurname(string surname);

    string GetSurname() const;

    void SetName(string name);

    string GetName() const;

    void SetMiddlName(string middlname);

    string GetMiddlName() const;

    void SetAdress(string adress);

    string GetAdress() const;

    void SetPhone(string phonenumber);

    string GetPhone() const;

    operator string()
    {
        return surname + " " + name + " " + middlename + " " + to_string(CalculateAverageGrade()) + " " + phonenumber;

    }
};