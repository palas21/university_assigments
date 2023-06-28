/*
BLG 252E - Assignment 3
Spring 2023
*/

#include "arena.h"

int main()
{
	srand(2002);
	Arena myArena;

	myArena.addPokemon('e', "Betul", 1000, 100); 
	myArena.addPokemon('p', "Safak", 950, 110);
	myArena.simulateBattle();

	/*
	myArena.addPokemon('e', "Jolteon", 150, 10); 
	myArena.addPokemon('p', "Kadabra", 100, 20); 
	myArena.simulateBattle();
	*/

	return 0;
}