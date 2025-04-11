#include <iostream>
#include "constants.h"
#include "Course.h"
#include "Student.h"

int main() {
    Student* student1 = new Student(111);
    Student *student2 = new Student(222);
    Student *student3 = new Student(333);
    Student *student4 = new Student(444);

    Course *course1 = new Course("kurs1");
    Course *course2 = new Course("kurs2");

    student1->enroll(*course1);
    student2->enroll(*course1);
    student3->enroll(*course1);
    student1->enroll(*course2);
    student4->enroll(*course2);
    
    course1->printCourse();
    course2->printCourse();

    std::cout << "\n";
    delete student1;
    std::cout << "\n";

    course1->printCourse();
    course2->printCourse();
}

