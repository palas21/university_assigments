/*
    @Author
    Şafak Özkan Pala
    150210016
*/

#pragma once

#include "pokemon.h"

class electricPokemon : public Pokemon{
    public:
        electricPokemon(std::string,int,int,double,int);
        void checkForTerrain(const std::string);
        bool getIsConfused(); // checks for confusion and if there is one decrease remaning round.
        void setIsConfused(int);
        int getGivenDamage(); // calculates the given damage.
        
    private:
        const std::string m_type = "electric";
        int m_isConfused = 0; // it is the remain round of confusion if it is not confused than it is 0.
};