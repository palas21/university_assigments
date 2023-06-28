/* @Author
 * Student Name:  Şafak Özkan Pala
 * Student ID : 150210016
 */
#pragma once

#include <string>
#include <time.h>

class Student{

    private: // we initialy assign our values
        std::string name = "";
        float GPA = 0;
        float GRE = 0;
        float TOEFL = 0;
        int number_of_applications = 0;
        
    public:
        Student(const Student&);
        Student(std::string,float,float,float);
        ~Student();
        void set_name(std::string);
        std::string get_name();
        void set_gpa(float);
        float get_gpa();
        void set_gre(float);
        float get_gre();
        void set_toefl(float);
        float get_toefl();
        void new_application();
};
