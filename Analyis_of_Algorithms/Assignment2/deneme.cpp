#include <iostream>
#include <string>


int main(){
    std::string k_string = "k532145";
    // std::string k_string as 532145
    
    k_string.erase(0,1);

    std::cout << std::stoi(k_string) << std::endl;
    return 0;
}