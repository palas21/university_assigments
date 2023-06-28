/*
@Author
Şafak Özkan Pala
150210016
*/

#pragma once

#include <string>

class ALU{
    public:
        ALU(const int);
        const int add(const int,const int) const;
        const int subtract(const int,const int) const;
        const int multiply(const int,const int) const;
        const int getAluCores();
    private:
        const int m_numPerCores;
};

class CUDA{
    public:
        CUDA(int);
        std::string render() const;
        std::string trainModel() const;
        const int getCudaCores();
    private:
        const int m_numCores;
};

class CPU{
    public:
        CPU(const int);
        void execute(std::string) const;
        const ALU getALU() const;
    private:
        const ALU m_alu;
};

class GPU{
    public:
        GPU(const int);
        void execute(std::string) const;
        const CUDA get_CUDA() const;
    private:
        const CUDA m_cuda;
}; 

class Computer{
    public:
        Computer();
        ~Computer();
        void operator+(GPU&);
        void operator+(CPU&);
        void execute(std::string) const;

    private:
        const CPU* attachedCPU = nullptr;
        const GPU* attachedGPU = nullptr;
};
