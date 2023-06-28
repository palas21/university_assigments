/*
    @Author
    Şafak Özkan Pala
    150210016
*/

#include "arena.h"
#include <iostream>
#include <random>

Arena::~Arena(){ // if there are some pokemons added and not simulated a battle than we must delete them. 
    // we check for wheter there is or not. if there is we delete it.
    if(!this->m_electricPokemon){
        delete this->m_electricPokemon;
    }

    if(!this->m_pyschicPokemon){
        delete this->m_pyschicPokemon;
    }
    // and make the pointers null to avoid problems.
    this->m_electricPokemon = nullptr;
    this->m_pyschicPokemon = nullptr;
}

void Arena::simulateBattle(){
    this->restartTerrain(); // we choose the terrain.
    int round = 0; // we start the counter.
    while(true){ // this loop will continue until the one of the pokemon will be fainted. 
        round++; // we increase the round number.
        int firstHit = rand() % 2; // 0 for electricPokemon and 1 for pyschicPokemon

        // we check terrains for both pokemon.
        this->m_electricPokemon->checkForTerrain(this->m_terrain); 
        this->m_pyschicPokemon->checkForTerrain(this->m_terrain);

        int damage; // this is the damage variable i want to use this for clearity.
        
        if(firstHit == 0){ // if first hit will be coming from electric pokemon.
            damage = this->m_electricPokemon->getGivenDamage(); // we calculate the damage.
            this->m_pyschicPokemon->damageTaken(damage); // we calculate the new hitpoint of the pyschic pokemon.
            if(!this->m_pyschicPokemon->getIsFainted()){ // if it is not fainted it will counter attack.
                damage = this->m_pyschicPokemon->getGivenDamage(this->m_electricPokemon); // we calculate the damage.
                this->m_electricPokemon->damageTaken(damage); // we calculate the new hitpoint of the electric pokemon.
            }
            else{ // if it is fainted than we print the round status and break the loop for match result.
                this->printRoundStates(round,firstHit);
                break;
            }
        }
        else{ // if first hit will be coming from pyschic pokemon.
            damage = this->m_pyschicPokemon->getGivenDamage(this->m_electricPokemon); // we calculate the damage.
            this->m_electricPokemon->damageTaken(damage); // we calculate the new hitpoint of the electric pokemon.
            if(!this->m_electricPokemon->getIsFainted()){ // if it is not fainted it will counter attack.
                damage = this->m_electricPokemon->getGivenDamage(); // we calculate the damage.
                this->m_pyschicPokemon->damageTaken(damage); // we calculate the new hitpoint of the pyschic pokemon.
            }
            else{ // if it is fainted than we print the round status and break the loop for match result.
                this->printRoundStates(round,firstHit);
                break;
            }
        }
        if(this->m_electricPokemon->getIsFainted() || this->m_pyschicPokemon->getIsFainted()){ // we check for both pokemon wheter one of them is fainted. if one of them is fainted than this battle is finished and we print the round status and break the loop.
            this->printRoundStates(round,firstHit);
            break;
        }
        this->printRoundStates(round,firstHit); // if neither of the pokemon is fainted than we print the round status and continue.
        this->spawnTerrain();// we call this method to calculate the new terrain.
    }
    this->printMatchResults(); // if battle is over we print the match result.
    
    // we delete both pokemon and make their pointer null to avoid problems.
    delete this->m_electricPokemon; 
    delete this->m_pyschicPokemon;
    this->m_electricPokemon = nullptr;
    this->m_pyschicPokemon = nullptr;
}

void Arena::addPokemon(char type,std::string name,int hp,int damage){ // we choose pokemon by their type and call their constructor and point them. if there is no such type pokemon it will print a error message this was not mentioned in the pdf but i just want to add it.
    if(type == 'e'){// this is for electric pokemon.
        this->m_electricPokemon = new electricPokemon(name,hp,damage,20,3);
    }
    else if(type == 'p'){// this is for pyschic pokemon.
        this->m_pyschicPokemon = new pyschicPokemon(name,hp,damage,30,5); 
    }
    else{//this is the error message.
        std::cout << "There is no such type pokemon." << std::endl;
    }
}

void Arena::spawnTerrain(){ // we determine the current terrain.  
    if(m_remaningForNewTerrain == 0 || this->m_terrain == "none"){ // if it is time for the change or it is 'none' terrain we choose a new random terrain.
        int random = rand() % 10; // we get a random value to calculate new terrain.
        if(random < 2){ // 20% change for pyschic and it will stand for 5 rounds.
            this->m_terrain = "pyschic";
            this->m_remaningForNewTerrain = 4;
        }
        else if(random < 4){ // 20% change for electric and it will stand for 5 rounds.
            this->m_terrain = "electric";
            this->m_remaningForNewTerrain = 4;
        }
        else{
            this->m_terrain = "none"; // 60% change for none and it will stand for just one round.
            this->m_remaningForNewTerrain = 0;
        }
    }
    else{ // if it is not we just decrease the remaning round.
        this->m_remaningForNewTerrain--;
    }
}

void Arena::restartTerrain(){ // beginning of every battle we choose a new random terrain.
    int random = rand() % 10;
    if(random < 2){ // 20% change for electric and it will stand for 5 rounds.
        this->m_terrain = "electric";
        this->m_remaningForNewTerrain = 4;
    }
    else if(random < 4){ //20% change for pyschic and it will stand for 5 rounds.
        this->m_terrain = "pyschic";
        this->m_remaningForNewTerrain = 4;
    }
    else{
        this->m_terrain = "none";// 60% change for none and it will stand for just one round.
        this->m_remaningForNewTerrain = 0;
    }
}

void Arena::printRoundStates(int round,int head){ // we print the necessary values.
    std::cout << "Round: " << round << std::endl;
    std::cout << "Current Terrain: " << this->m_terrain << std::endl;
    std::string firstHit = (head == 0) ? this->m_electricPokemon->getName() : this->m_pyschicPokemon->getName(); // we determine who hits first.
    std::cout << firstHit << " goes first."  << std::endl;
    
    // this is for power up we first print who hits first if it is powered up than the second one.
    if(head == 0){
        if(this->m_electricPokemon->getPowerUpState()){
            std::cout << this->m_electricPokemon->getName() << " has initiated a power up." << std::endl;
        }
        if(this->m_pyschicPokemon->getPowerUpState()){
            std::cout << this->m_pyschicPokemon->getName() << " has initiated a power up." << std::endl;
        }
    }
    else{
        if(this->m_pyschicPokemon->getPowerUpState()){
            std::cout << this->m_pyschicPokemon->getName() << " has initiated a power up." << std::endl;
        }
        if(this->m_electricPokemon->getPowerUpState()){
            std::cout << this->m_electricPokemon->getName() << " has initiated a power up." << std::endl;
        }
    }
    // end of printing power ups.

    std::cout << this->m_electricPokemon->getName() << " HP:" << this->m_electricPokemon->getHP() << std::endl;
    std::cout << this->m_pyschicPokemon->getName() << " HP:" << this->m_pyschicPokemon->getHP() << std::endl;
    std::string leadPokemon = (this->m_electricPokemon->getHP() > this->m_pyschicPokemon->getHP()) ? this->m_electricPokemon->getName() : this->m_pyschicPokemon->getName(); // we determine who is in the lead.
    std::cout << leadPokemon << " is in the lead!" << std::endl << std::endl << std::endl;
}

void Arena::printMatchResults(){ // we print the match result.
    std::cout << "Match Results:" << std::endl;
    std::string winner = this->m_pyschicPokemon->getIsFainted() ? this->m_electricPokemon->getName() : this->m_pyschicPokemon->getName();
    std::cout << winner << " has won the match!" << std::endl <<std::endl << std::endl;
}