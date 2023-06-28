/* @Author
 * Student Name:  Şafak Özkan Pala
 * Student ID : 150210016
 */
#pragma once

#include <string>
#include "student.h"
#include <random>

class University{
    private: // we initially assign our values
        std::string name = "";
        float gpa_weight;
        float gre_weight;
        float toefl_weight;
        float bias_value;
        std::string country = "";

    public:
        University(std::string,float,float,float,float,std::string);
        University(std::string,float,float,float,float);
        ~University();
        void evaluate_student(Student&);
        void evaluate_student(const Student&) const;
};
