/*
@Author
Şafak Özkan Pala
150210016
*/

#include <string>
#include <iostream>
#include "Computer.h"

// start of ALU methods

ALU::ALU(const int numPerCores) : m_numPerCores{numPerCores}{ // we assign our constant cores in initializer list and print the screen appropraite message.
    std::cout << "ALU is ready" << std::endl;
}

const int ALU::add(const int num1,const int num2) const{ // we return the sum and since we dont change anything it is a constant method.
    return num1 + num2;
}

const int ALU::subtract(const int num1,const int num2) const{ // we return the subtraction and since we dont change anything it is a constant method.
    return num1 - num2;
}

const int ALU::multiply(const int num1,const int num2) const{ // we return the multiplication and since we dont change anything it is a constant method.
    return num1 * num2;
}

const int ALU::getAluCores(){ // we return number of cores of alu.
    return this->m_numPerCores;
}

// end of ALU methods

// start of CUDA methods

CUDA::CUDA(const int numCores) : m_numCores{numCores}{ // we assign our constant cores in initializer list and print the screen appropraite message.
    std::cout << "CUDA is ready" << std::endl;
}

std::string CUDA::render() const{ // we return the result and since we dont change anythingit is a constant method.
    return "Video is rendered";
}

std::string CUDA::trainModel() const{ // we return the result and since we dont change anythingit is a constant method.
    return "AI Model is trained";
}

const int CUDA::getCudaCores(){ // we return number of cores of cuda.
    return this->m_numCores;
}

// end of CUDA methods

// start of CPU methods

CPU::CPU(const int m_numPerCores) : m_alu{m_numPerCores}{ // we crate an ALU object and point it to be our alu object than print the message.
    std::cout << "CPU is ready" << std::endl;
}

const ALU CPU::getALU() const{ //we return our alu object.
    return this->m_alu;
}

void CPU::execute(std::string operation) const{ // we get the operation and than take two integer after that for a given operation we choose necessary operation and set the numbers to alu object to do the operations and print the result that returned by alu object.
    std::cout << "Enter two integers" << std::endl;
    int num1,num2;
    std::cin >> num1 >> num2;

    if(operation == "add"){
        std::cout << this->m_alu.add(num1,num2) << std::endl;
    }
    else if(operation == "subtract"){
        std::cout << this->m_alu.subtract(num1,num2) << std::endl;
    }
    else if(operation == "multiply"){
        std::cout <<  this->m_alu.multiply(num1,num2) << std::endl;
    }
    else{ // if operation is not in our operation list than we simply print this message. I know this wasnt mentioned in instructions but i just want to add this.
        std::cout << "Invalid operation." << std::endl;
    }
}

// end of CPU methods

// start of GPU methods

GPU::GPU(const int m_numCores) : m_cuda{m_numCores}{  // we crate an CUDA object and point it to be our cuda object than print the message.
    std::cout << "GPU is ready" << std::endl;
}

const CUDA GPU::get_CUDA() const{ //we return our cuda object.
    return this->m_cuda; 
}

void GPU::execute(std::string operation) const{ // we get the operation and choose the necessary operation and send it to our cuda object and print the result that returned by cuda object.
    if(operation == "render"){
        std::cout << this->m_cuda.render() << std::endl;
    }
    else if(operation == "trainModel"){
        std::cout << this->m_cuda.trainModel() << std::endl;
    }
    else{ // if operation is not in our operation list than we simply print this message. I know this wasnt mentioned in instructions but i just want to add this too.
        std::cout << "Invalid operation." << std::endl;
    }
}


// end of GPU methods

// start of Computer methods

Computer::Computer(){ // we create our computer object without any attached cpu and gpu and print the message.
    this->attachedCPU = nullptr;
    this->attachedGPU = nullptr;
    std::cout << "Computer is ready" << std::endl;
}

Computer::~Computer(){ //we assign all pointers to null before deletion.
    this->attachedCPU = nullptr;
    this->attachedGPU = nullptr;
}

void Computer::operator+(GPU& m_gpu){ // we check for out computer object wheter has a gpu or not and if it doesnt have any gpu that we point to the given gpu.
    if(this->attachedGPU == nullptr){
        this->attachedGPU = &m_gpu;
        std::cout << "GPU is attached" << std::endl;
    }
    else{ // if there is a gpu we print this message.
        std::cout << "There is already a GPU" << std::endl;
    }
}

void Computer::operator+(CPU& m_cpu){ // we check for out computer object wheter has a cpu or not and if it doesnt have any cpu that we point to the given cpu.
    if(this->attachedCPU == nullptr){
        this->attachedCPU = &m_cpu;
        std::cout << "CPU is attached" << std::endl;
    }
    else{ // if there is a cpu we print this message.
        std::cout << "There is already a CPU" << std::endl;
    }
}

void Computer::execute(std::string operation) const{ // we get the operation and send it to the responsible part of the computer.
    if(operation == "add" || operation == "subtract" || operation == "multiply"){
        this->attachedCPU->execute(operation);
    }
    else if(operation == "render" || operation == "trainModel"){
        this->attachedGPU->execute(operation);
    }
    else{ // if operation is not in our operation list than we simply print this message. I know this wasnt mentioned in instructions but i just want to add this too.
        std::cout << "Undefined operation." << std::endl;
    }
}
