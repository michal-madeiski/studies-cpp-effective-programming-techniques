#include <iostream>
#include "constants.h"
#include "Course.h"
#include "Student.h"

Student::Student() {
	indexNumber = DEFAULT_INDEX_NUMBER;
	coursesTab = new Course*[DEFAULT_COURSES_TAB_LENGTH];
	currentCoursesAmount = 0;
}

Student::Student(int index_number) {
	indexNumber = index_number;
	coursesTab = new Course*[DEFAULT_COURSES_TAB_LENGTH];
	currentCoursesAmount = 0;
}

int Student::getIndexNumber() {
	return indexNumber;
}

void Student::enroll(Course &course) {
	if (course.getStudentsAmount() >= DEFAULT_STUDENTS_TAB_LENGTH) {
		std::cout << "Kurs jest pelny! \n";
		return;
	}
	course.addStudent(this);
	coursesTab[currentCoursesAmount++] = &course;
}

Student::~Student() {
	for (int i = 0; i < currentCoursesAmount; ++i) {
		coursesTab[i]->removeStudent(this);
	}

	std::cout << "Usunieto z bazy " << indexNumber << "\n\n";

	delete[] coursesTab;
}

