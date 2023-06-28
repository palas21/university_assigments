/*
    @Author
    Şafak Özkan Pala
    150210016
*/

#include "psychicPokemon.h"


pyschicPokemon::pyschicPokemon(std::string in_name, int in_hp, int in_damage, double in_powerUpChance, int in_recharge) : Pokemon{in_name, in_hp,in_damage, in_powerUpChance, in_recharge}{
    std::cout << "Psychic Pokemon " << in_name << " has entered the arena." << std::endl;
    std::cout << "Class: Psychic" << std::endl;
    std::cout << "        Name: " << in_name << std::endl;
    std::cout << "        HP: " << in_hp << std::endl;
    std::cout << "        Damage: " << in_damage << std::endl << std::endl << std::endl;
}

void pyschicPokemon::checkForTerrain(const std::string terrain){ // if it is in its own terrain we set own terrain true otherwise false.
    if(terrain == this->m_type){
        this->setIsOwnTerrain(true);
    }
    else{
        this->setIsOwnTerrain(false);
    }
}

int pyschicPokemon::getGivenDamage(electricPokemon*& in_electricPokemon){ // for calculating given damage we check for 2 things.
    if(this->getIsInOwnTerrain()){ // firstly, if it is in its own terrain if it is we double the damage.
        if(this->getIsPowerUp()){ // secondly, if its power is up than we make electric pokemon confused for three round.
            in_electricPokemon->setIsConfused(3);
            return this->getDamage() * 2;
        }
        else{ // otherwise just give the calculated damage to the electric pokemon.
            return this->getDamage() * 2;
        }
    }
    else{
        if(this->getIsPowerUp()){ // if its power is up than we make electric pokemon confused for three round.
            in_electricPokemon->setIsConfused(3);
            return this->getDamage();
        }
        else{ // otherwise just give the calculated damage to the electric pokemon.
            return this->getDamage();
        }
    }
}