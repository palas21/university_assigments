/*
    @Author
    Şafak Özkan Pala
    150210016
*/

#pragma once 

#include "pokemon.h"
#include "electricPokemon.h"

class pyschicPokemon : public Pokemon{
    public:
        pyschicPokemon(std::string,int,int,double,int);
        void checkForTerrain(const std::string);
        int getGivenDamage(electricPokemon*&); // calculates the given damage.
    private:
        const std::string m_type = "pyschic";
};