//#include <iostream>
//#include "stu.h"
//using namespace std;
//
//class Group {
//private:
//    int studentCount = 0;
//    Student** students = nullptr;
//    string groupName;
//    string groupSpecialization;
//    int classNumber = 2;
//    int passingGrade = 7;
//
//public:
//    Group();
//    Group(string groupName, string groupSpecialization);
//    Group(const Group& original);
//    void ShowGroup();
//    void AddStudent(Student& student);
//    void MergeGroup(Group& g2);
//    void TransferStudent(int index, Group& g2);
//    void ExpelStudents();
//    void ExpelBadStudent();
//    void SetGroupName(string groupName);
//    string GetGroupName() const;
//    void SetGroupSpecialization(string groupSpecialization);
//    string GetGroupSpecialization() const;
//    void SetPassingGrade(int passingGrade);
//    int GetPassingGrade() const;
//    friend  ostream& operator<<(ostream& os, const Group& group);
//    ~Group();
//};
//
//Group::Group() : Group("P26", "Prog") {}
//
//Group::Group(string groupName, string groupSpecialization) {
//    SetGroupName(groupName);
//    SetGroupSpecialization(groupSpecialization);
//}
//
//Group::Group(const Group& original) {
//    this->groupName = original.groupName;
//    this->groupSpecialization = original.groupSpecialization;
//    this->students = new Student * [original.studentCount];
//    for (int i = 0; i < studentCount; i++) {
//        this->students[i] = new Student(*original.students[i]);
//    }
//}
//
//void Group::ShowGroup() {
//    cout << "Group: " << groupName << ", Specialization: " << groupSpecialization << "\n";
//    cout << "Students:\n";
//    for (int i = 0; i < studentCount; i++) {
//        cout << "Student " << i + 1 << ":\n";
//        students[i]->PrintStudent();
//        cout << "\n";
//    }
//}
//
//void Group::AddStudent(Student& student) {
//    Student** temp = new Student * [studentCount + 1];
//    for (int i = 0; i < studentCount; i++) {
//        temp[i] = students[i];
//    }
//    temp[studentCount] = new Student(student);
//    studentCount++;
//    delete[] students;
//    students = temp;
//}
//
//void Group::MergeGroup(Group& g2) {
//    int otherStudentCount = g2.studentCount;
//
//    Student** temp = new Student * [studentCount + otherStudentCount];
//    for (int i = 0; i < studentCount; i++) {
//        temp[i] = students[i];
//    }
//
//    for (int i = 0; i < otherStudentCount; i++) {
//        temp[studentCount + i] = new Student(*g2.students[i]);
//    }
//    studentCount += otherStudentCount;
//    delete[] students;
//    students = temp;
//}
//
//void Group::TransferStudent(int index, Group& g2) {
//    if (index >= 0 && index < studentCount) {
//        Student* transfer = students[index];
//        Student** temp = new Student * [studentCount - 1];
//        int tempIndex = 0;
//        for (int i = 0; i < studentCount; i++) {
//            if (i != index) {
//                temp[tempIndex++] = students[i];
//            }
//        }
//        delete students[index];
//        delete[] students;
//        students = temp;
//        studentCount--;
//        g2.AddStudent(*transfer);
//    }
//}
//
//void Group::ExpelStudents() {
//    Student** temp = new Student * [studentCount];
//    int index = 0;
//
//    for (int i = 0; i < studentCount; ++i) {
//        bool passedExam = false;
//
//        for (int j = 0; j < students[i]->GetExamRatesCount(1); ++j) {
//            if (students[i]->GetExamRatesCount(j) >= passingGrade) {
//                passedExam = true;
//                break;
//            }
//        }
//
//        if (!passedExam) {
//            cout << "Expelling student " << students[i]->GetName() << " for failing exam.\n";
//            delete students[i];
//        }
//        else {
//            temp[index++] = students[i];
//        }
//    }
//
//    delete[] students;
//    students = temp;
//    studentCount = index;
//}
//
//void Group::ExpelBadStudent() {
//    if (studentCount == 0) {
//        cout << "No students in the group to expel.\n";
//        return;
//    }
//
//    int minIndex = 0;
//    double minAverageGrade = students[0]->CalculateAverageGrade();
//    for (int i = 1; i < studentCount; ++i) {
//        double averageGrade = students[i]->CalculateAverageGrade();
//        if (averageGrade < minAverageGrade) {
//            minIndex = i;
//            minAverageGrade = averageGrade;
//        }
//    }
//
//    cout << "Expelling the least performing student " << students[minIndex]->GetName() << "\n";
//    delete students[minIndex];
//
//    for (int i = minIndex; i < studentCount - 1; ++i) {
//        students[i] = students[i + 1];
//    }
//    studentCount--;
//}
//
//void Group::SetGroupName(string groupName) {
//    this->groupName = groupName;
//}
//
//string Group::GetGroupName() const {
//    return groupName;
//}
//
//void Group::SetGroupSpecialization(string groupSpecialization) {
//    this->groupSpecialization = groupSpecialization;
//}
//
//string Group::GetGroupSpecialization() const {
//    return groupSpecialization;
//}
//
//void Group::SetPassingGrade(int passingGrade) {
//    this->passingGrade = passingGrade;
//}
//
//int Group::GetPassingGrade() const {
//    return passingGrade;
//}
//
//Group::~Group() {
//    for (int i = 0; i < studentCount; i++) {
//        delete students[i];
//    }
//    delete[] students;
//}