/*
    @Author
    Şafak Özkan Pala
    150210016
*/

#include "pokemon.h"
#include <random>

Pokemon::Pokemon(std::string name,int hp,int damage,double powerup,int recharge) : m_name{name}, m_damage{damage}, m_powerUpChance{powerup}, m_recharge{recharge}{
    this->m_hitpoint = hp;
}

const std::string Pokemon::getName(){
    return this->m_name;
}

const int Pokemon::getHP(){
    return this->m_hitpoint;
}

void Pokemon::damageTaken(int takenDamage){ // it calculates new hitpoint and make necessary adjusments.
    this->m_hitpoint -= takenDamage;
    if(this->m_hitpoint <= 0){
        this->m_hitpoint = 0;
        this->m_isFainted = true;
    }
}

const int Pokemon::getDamage(){
    return this->m_damage;
}

const double Pokemon::getPowerUpChance(){
    return this->m_powerUpChance;
}

const int Pokemon::getRecharge(){
    return this->m_recharge;
}

const bool Pokemon::getIsPowerUp(){ // first we check if there isnt a reamaing round if there is than we decrease it and continue. if there isnt we calculate a random value and than wheter make it true or false. 
    if(this->m_remaingRoundForPowerUp == 0){
        int random = rand() % 100;
        if(this->getPowerUpChance() > random){
            this->m_remaingRoundForPowerUp = this->m_recharge;
            this->m_powerUpState = true;
            return true;
        }
        else {
            this->m_powerUpState = false;
            return false;
        }       
    }
    else{
        this->m_remaingRoundForPowerUp--;
        this->m_powerUpState = false;
        return false;
    }
}

const int Pokemon::getRemaingRoundForPowerUp(){
    return this->m_remaingRoundForPowerUp;
}

void Pokemon::setRemainingRoundForPowerUp(int remain){
    this->m_remaingRoundForPowerUp = remain;
}

const bool Pokemon::getIsInOwnTerrain(){
    return this->m_isInOwnTerrain;
}

void Pokemon::setIsOwnTerrain(bool isit){
    this->m_isInOwnTerrain = isit;
}

const bool Pokemon::getIsFainted(){
    return this->m_isFainted;
}

const bool Pokemon::getPowerUpState(){
    return this->m_powerUpState;
}
