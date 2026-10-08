# Student Attendance Management System

A console-based C++ application for maintaining student attendance records.

## Features
- Add students
- Mark daily attendance
- Store records locally using file handling
- Search students by roll number
- Calculate attendance percentage
- View an attendance report

## Technologies
- C++
- STL `vector`
- File handling (`fstream`)
- Functions, structures, loops and conditional statements

## Run
```bash
g++ main.cpp -std=c++17 -o attendance
./attendance
```

On Windows:
```bash
g++ main.cpp -std=c++17 -o attendance.exe
attendance.exe
```

The program creates `attendance.txt` automatically when records are saved.
