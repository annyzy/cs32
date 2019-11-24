/*
 * Card.cpp
 *
 *  Created on: Nov 22, 2017
 *      Author: student
 */

#include "Card.h"

using namespace std;

/**
 * Constructor;
 */
Card::Card(Suit s, Rank r) :
		cardSuit(s), cardRank(r) {

}

/**
 * Joker constructor
 */
Card::Card() :
		cardSuit(Suit::Spades), cardRank(Rank::Joker) {
}

/**
 * Output the card to an output stream as "rank of suit"
 */
ostream& operator <<(std::ostream&s, const Card&c) {
    if (c.cardRank == 0) {
        s << "Joker";
    }
    else {
        s << rankNames[c.cardRank] << " of " << suitNames[c.cardSuit];
    }
    return s;
}

/**
 * Compare operators. For the game of war we only care about the rank
 */

//Determines whether two cards tie;
bool operator ==(const Card &lhs, const Card &rhs) {
	return lhs.cardRank == rhs.cardRank;
}

bool operator <(const Card &lhs, const Card &rhs) {
	return lhs.cardRank < rhs.cardRank;
}







