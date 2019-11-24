//============================================================================
// Name        : Lab13.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <vector>

#include "Deck.h"
#include "Card.h"
#include "TerminalPlayer.h"
#include "Player.h"

using namespace std;

int main() {
	Deck gameDeck; //Create a deck of card;
	Card joker;
	TerminalPlayer player("terminal"); //Create a terminal player called terminal;
	gameDeck.shuffle(); //Shuffle the card;

	/**
	 * draw three cards;
	 */
	player.receiveCard(gameDeck.draw());
	player.receiveCard(gameDeck.draw());
	player.receiveCard(gameDeck.draw());

	Card returnedCard = player.playCard(joker); //return the joker to play
	cout << "Player " << player << " played a " << returnedCard << endl; //print out who play what card;

}
