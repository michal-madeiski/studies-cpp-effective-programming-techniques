#include <iostream>
#include "constants.h"
#include "Course.h"
#include "Student.h"

Course::Course() {
	courseName = DEFAULT_COURSE_NAME;
	currentStudentsAmount = 0;
	studentsTab = new Student*[DEFAULT_STUDENTS_TAB_LENGTH];
}

Course::Course(std::string course_name) {
	courseName = course_name;
	currentStudentsAmount = 0;
	studentsTab = new Student*[DEFAULT_STUDENTS_TAB_LENGTH];
}

int Course::getStudentsAmount() {
	return currentStudentsAmount;
}

void Course::addStudent(Student *student) {
	studentsTab[currentStudentsAmount++] = student;
}

void Course::removeStudent(Student *student) {
	for (int i = 0; i < currentStudentsAmount; ++i) {
		if (studentsTab[i] == student) {
			for (int j = i; j < currentStudentsAmount - 1; ++j) {
				studentsTab[j] = studentsTab[j + 1];
			}
			currentStudentsAmount--;
			return;
		}
	}
}

void Course::printCourse() {
	std::cout << courseName << ": \n";
	std::cout << "Liczba studentow: " << currentStudentsAmount << "\n";
	std::cout << "Lista studentow: ";
	for (int i = 0; i < currentStudentsAmount; ++i) {
		if (studentsTab[i] != NULL) {
			if (i < currentStudentsAmount - 1) {
				std::cout << studentsTab[i]->getIndexNumber() << ", ";
			}
			else {
				std::cout << studentsTab[i]->getIndexNumber() << "\n";
			}
		}
	}
	std::cout << "\n";
}
