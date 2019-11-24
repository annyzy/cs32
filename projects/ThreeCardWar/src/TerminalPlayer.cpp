/*
 * TerminalPlayer.cpp
 *
 *  Created on: Nov 22, 2017
 *      Author: student
 */

#include "TerminalPlayer.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

/**
 * Constructor;
 */
TerminalPlayer::TerminalPlayer(string name) : Player(name) {

}


TerminalPlayer::~TerminalPlayer() {
	// TODO Auto-generated destructor stub
}

/**
 * Play a card. If the player receives a joker then this player is going first
 */
const Card TerminalPlayer::playCard(const Card opponentCard) {

	unsigned int cardIndex = 0;

	/**
	 * Tell the player if they are going first (they receive a joker)
	 */
	if(opponentCard.isJoker())
	{
	    cout << "It is Player 1 turn" <<endl;
	}

	cout << "Cards in Player 1 hands are: " << endl;

	/**
	 * Display the cards in the player's hand (could be 1 - 3) cards
	 */
	for(unsigned int i = 0; i < hand.size(); i++)
	{
	    cout << i << " -- " << hand[i] << endl;
	}

	/**
	 * Prompt the player for the card they want to play
	 */
	cout << "What card you want to play? Please enter 0 - " << (hand.size() - 1) << endl;
	cin >> cardIndex;

	/**
	 * Removed the chosen card from the player's hand and return the chosen card
	 */
	while(cardIndex > (hand.size() - 1))
	{
	    cout << "Invalid card, please try again..." <<endl;
	    cin >> cardIndex;
	}
	Card cardChosen = hand[cardIndex];
	hand.erase(hand.begin() + cardIndex);
	return cardChosen;

}

/**
 * Output the players name
 */
ostream& operator <<(std::ostream& out, const Player& p){
	out << p.name;
    return out;
}

