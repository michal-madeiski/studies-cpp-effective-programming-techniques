#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include "constants.h"

class Student;

class Course {
private:
	std::string courseName;
	Student **studentsTab;
	int currentStudentsAmount;
public:
	Course();
	Course(std::string course_name);
	int getStudentsAmount();
	void addStudent(Student *student);
	void removeStudent(Student *student);
	void printCourse();
};

#endif
