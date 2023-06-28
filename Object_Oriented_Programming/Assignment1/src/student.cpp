/* @Author
 * Student Name:  Şafak Özkan Pala
 * Student ID : 150210016
 */

#include "student.h"
#include <iostream>

Student::Student(const Student& student_base){ // this is copy constructer. we reset our application number
    Student& student_new = const_cast<Student&>(student_base);
    this->name = student_new.get_name();
    this->GPA = student_new.get_gpa();
    this->GRE = student_new.get_gre();
    this->TOEFL = student_new.get_toefl();
    this->number_of_applications = 0;
    std::cout << name << " logged in to the system." << std::endl;
}

Student::Student(std::string name,float gpa,float gre,float toefl){ // we assign given values the proper variables and print the message
    this->name = name;
    this->GPA = gpa;
    this->GRE = gre;
    this->TOEFL = toefl;
    std::cout << name << " logged in to the system." << std::endl;
}

Student::~Student(){ // we print the message and then delete the variable
    std::cout << name << " logged out of the system with " << this->number_of_applications << " application(s)." << std::endl;
}

void Student::set_name(std::string name){
    this->name = name;
}

std::string Student::get_name(){
    return this->name;
}

void Student::set_gpa(float gpa){
    this->GPA = gpa;
}

float Student::get_gpa(){
    return this->GPA;
}

void Student::set_gre(float gre){
    this->GRE = gre;
}

float Student::get_gre(){
    return this->GRE;
}

void Student::set_toefl(float toefl){
    this->TOEFL = toefl;
}

float Student::get_toefl(){
    return this->TOEFL;
}

void Student::new_application(){ // we increase out application number
    this->number_of_applications++;
}
