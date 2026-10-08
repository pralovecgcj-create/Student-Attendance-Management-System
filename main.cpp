#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
using namespace std;

struct Student {
    int rollNo;
    string name;
    int present = 0;
    int total = 0;
};

const string FILE_NAME = "attendance.txt";

void saveStudents(const vector<Student>& students) {
    ofstream file(FILE_NAME);
    for (const auto& s : students)
        file << s.rollNo << "|" << s.name << "|" << s.present << "|" << s.total << "\n";
}

void loadStudents(vector<Student>& students) {
    ifstream file(FILE_NAME);
    if (!file) return;

    Student s;
    string roll, name, present, total;
    while (getline(file, roll, '|') &&
           getline(file, name, '|') &&
           getline(file, present, '|') &&
           getline(file, total)) {
        try {
            s.rollNo = stoi(roll);
            s.name = name;
            s.present = stoi(present);
            s.total = stoi(total);
            students.push_back(s);
        } catch (...) {
            // Ignore malformed records.
        }
    }
}

int findStudent(const vector<Student>& students, int rollNo) {
    for (int i = 0; i < (int)students.size(); ++i)
        if (students[i].rollNo == rollNo) return i;
    return -1;
}

void addStudent(vector<Student>& students) {
    Student s;
    cout << "\nEnter roll number: ";
    cin >> s.rollNo;

    if (findStudent(students, s.rollNo) != -1) {
        cout << "Student already exists.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter student name: ";
    getline(cin, s.name);

    students.push_back(s);
    saveStudents(students);
    cout << "Student added successfully.\n";
}

void markAttendance(vector<Student>& students) {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }

    cout << "\nMark attendance (P = Present, A = Absent)\n";
    for (auto& s : students) {
        char status;
        cout << s.rollNo << " - " << s.name << ": ";
        cin >> status;

        if (status == 'P' || status == 'p') s.present++;
        s.total++;
    }

    saveStudents(students);
    cout << "Attendance saved.\n";
}

void viewReport(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }

    cout << "\n" << left << setw(10) << "Roll"
         << setw(25) << "Name"
         << setw(10) << "Present"
         << setw(10) << "Total"
         << "Percent\n";
    cout << string(65, '-') << "\n";

    for (const auto& s : students) {
        double percent = s.total ? (100.0 * s.present / s.total) : 0.0;
        cout << left << setw(10) << s.rollNo
             << setw(25) << s.name
             << setw(10) << s.present
             << setw(10) << s.total
             << fixed << setprecision(2) << percent << "%\n";
    }
}

void searchStudent(const vector<Student>& students) {
    int rollNo;
    cout << "Enter roll number: ";
    cin >> rollNo;

    int i = findStudent(students, rollNo);
    if (i == -1) {
        cout << "Student not found.\n";
        return;
    }

    const auto& s = students[i];
    double percent = s.total ? (100.0 * s.present / s.total) : 0.0;
    cout << "\nName: " << s.name
         << "\nRoll No: " << s.rollNo
         << "\nAttendance: " << s.present << "/" << s.total
         << "\nPercentage: " << fixed << setprecision(2) << percent << "%\n";
}

int main() {
    vector<Student> students;
    loadStudents(students);

    int choice;
    do {
        cout << "\n===== Student Attendance Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Mark Attendance\n";
        cout << "3. View Attendance Report\n";
        cout << "4. Search Student\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(students); break;
            case 2: markAttendance(students); break;
            case 3: viewReport(students); break;
            case 4: searchStudent(students); break;
            case 5: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
