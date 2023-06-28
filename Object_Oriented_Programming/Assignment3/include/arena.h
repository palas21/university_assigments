/*
    @Author
    Şafak Özkan Pala
    150210016
*/

#pragma once

#include <random>
#include "electricPokemon.h"
#include "psychicPokemon.h"

class Arena{
    public:
        ~Arena();
        void simulateBattle();
        void addPokemon(char,std::string,int,int);
        void spawnTerrain();
        void restartTerrain();
        void printRoundStates(int,int);
        void printMatchResults();
    private:
        electricPokemon* m_electricPokemon;
        pyschicPokemon* m_pyschicPokemon;
        int m_remaningForNewTerrain = 0; // this is a counter for terrain to change.
        std::string m_terrain;
};