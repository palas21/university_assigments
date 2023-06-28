/*
    @Author
    Şafak Özkan Pala
    150210016
*/

#include "electricPokemon.h"

electricPokemon::electricPokemon(std::string in_name, int in_hp, int in_damage, double in_powerUpChance, int in_recharge) : Pokemon{in_name, in_hp,in_damage, in_powerUpChance, in_recharge}{
    std::cout << "Electric Pokemon " << in_name << " has entered the arena." << std::endl;
    std::cout << "Class: Electric" << std::endl;
    std::cout << "        Name: " << in_name << std::endl;
    std::cout << "        HP: " << in_hp << std::endl;
    std::cout << "        Damage: " << in_damage << std::endl << std::endl << std::endl;   
}

void electricPokemon::checkForTerrain(const std::string terrain){ // if it is in its own terrain we set own terrain true otherwise false.
    if(terrain == this->m_type){
        this->setIsOwnTerrain(true);
    }
    else{
        this->setIsOwnTerrain(false);
    }
}

int electricPokemon::getGivenDamage(){ // for calculating given damage we check for 3 things.
    if(this->getIsInOwnTerrain()){ // firstly if its in its own terrain. if it is than it will not be confused so we make the counter 0 and calculate the damage.
        this->m_isConfused = 0; 
        if(this->getIsPowerUp()){ // secondly if its power is up than we triple the damage. 
            return this->getDamage() * 3;
        }
        else{ // otherwise just the regular damage.
            return this->getDamage();
        }
    }
    else{
        if(this->getIsConfused()){ // thirdly if it is not in its own terrain than we check for confusion if it is confused than given damage is zero.
            if(this->getIsPowerUp()){ // it is not important that wheter its power is up or not but for counter of remaining round for power up method must be called so we call this method. 
                return 0;
            }
            else{ // either way it is zero.
                return 0;
            }
        }
        else{ // if it is not confused than we check for power up and if its power is up it triples the damage.
            if(this->getIsPowerUp()){
                return this->getDamage() * 3;
            }
            else{ // otherwise just the regular damage.
                return this->getDamage();
            }
        }
    }
}

bool electricPokemon::getIsConfused(){ // this method calculates and return the confusion state.
    if(this->m_isConfused == 0){
        return false;
    }
    else{
        this->m_isConfused--;
        return true;
    }
}

void electricPokemon::setIsConfused(int remaining){ // this is for setting the new remaning round for confusion.
    this->m_isConfused = remaining;
}