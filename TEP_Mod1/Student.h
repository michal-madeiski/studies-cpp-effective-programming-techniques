#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include "constants.h"

class Course;

class Student {
private:
	int indexNumber;
	Course **coursesTab;
	int currentCoursesAmount;
public:
	Student();
	Student(int index_number);
	int getIndexNumber();
	void enroll(Course &course);
	~Student();
};

#endif
