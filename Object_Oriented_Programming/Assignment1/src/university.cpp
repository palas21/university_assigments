/* @Author
 * Student Name:  Şafak Özkan Pala
 * Student ID : 150210016
 */

#include "university.h"
#include <iostream>

University::University(std::string name,float gpa,float gre,float toefl,float bias,std::string country){ // we assign values to the proper variables.
    this->name = name;
    this->gpa_weight = gpa;
    this->gre_weight = gre;
    this->toefl_weight = toefl;
    this->bias_value = bias;
    this->country = country;
}

University::University(std::string name,float gpa,float gre,float toefl,float bias){ // we assign values to the proper variables.
    this->name = name;
    this->gpa_weight = gpa;
    this->gre_weight = gre;
    this->toefl_weight = toefl;
    this->bias_value = bias;
}

University::~University(){
    
}

void University::evaluate_student(Student& student){ // we evaulate students through the given formula
    //if student is eligable we admit him to the university and increase application number.
    if(((student.get_gpa() * this->gpa_weight) + (student.get_gre() * this->gre_weight) + (student.get_toefl() * this->toefl_weight) + this->bias_value) >= 0){ 
        std::cout << student.get_name() << " is admitted to " << this->name << "." << std::endl;
        student.new_application();
    }
    else{//if he/she is not eligable we reject him and increase the application number.
        std::cout << student.get_name() << " is rejected from " << this->name << "." << std::endl;
        student.new_application();
    }
}

void University::evaluate_student(const Student& student1) const{
    Student& student = const_cast<Student&>(student1);
    if(((student.get_gpa() * this->gpa_weight) + (student.get_gre() * this->gre_weight) + (student.get_toefl() * this->toefl_weight) + this->bias_value) >= 0){
        std::cout << student.get_name() << " is admitted to " << this->name << "." << std::endl;
        student.new_application();
    }
    else{
        std::cout << student.get_name() << " rejected from " << this->name << "." << std::endl;
        student.new_application();
    }
}