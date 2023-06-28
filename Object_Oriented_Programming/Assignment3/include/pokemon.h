/*
    @Author
    Şafak Özkan Pala
    150210016
*/

#pragma once 

#include <string>
#include <iostream>

class Pokemon{
    public:
        Pokemon(std::string,int,int,double,int);
        const std::string getName();
        const int getHP();
        void damageTaken(int); // it recieve given damage as a paramater and calculate the mew hitpoint if new hitpoint is below or equal to zero than pokemon will be fainted and new hitpoint will be zero.
        const int getDamage();
        const double getPowerUpChance();
        const int getRecharge();
        const bool getIsFainted(); 
        const bool getPowerUpState();
        const bool getIsPowerUp(); // it calculates the power up state and return it and make the status true or false.
        const int getRemaingRoundForPowerUp(); 
        void setRemainingRoundForPowerUp(int);
        const bool getIsInOwnTerrain();
        void setIsOwnTerrain(bool);
    private:
        const std::string m_name;
        int m_hitpoint;
        const int m_damage;
        const double m_powerUpChance;
        const int m_recharge;
        bool m_powerUpState = false;
        int m_remaingRoundForPowerUp = 0; // it is a counter for remaning round of power ups.
        bool m_isInOwnTerrain = false;
        bool m_isFainted = false;
};