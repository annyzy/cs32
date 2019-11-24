/*
 * Deck.cpp
 *
 *  Created on: Nov 17, 2017
 *      Author: student
 */

#include "Deck.h"
#include "Card.h"
#include <utility>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

/*
 * Default Constructor: Iterates though all suit and ranks to create the deck
 */
Deck::Deck() {
	/**
	 * Check each suit;
	 */
	for (int s = 0; s < 4; s++) {
		/**
		 * Check each rank of each suit
		 */
		for (int r = 1; r <= 13; r++) {
			/**
			 * Add the card;
			 */
			cardDeck.push_back(Card(Card::Suit(s), Card::Rank(r)));
		}
	}
    nextCard = 0;
}

Deck::~Deck() {

}

/*
 * Shuffle function: iterates through deck and swaps a card with a random card
 */
void Deck::shuffle() {
	/**
	 * See the rand so that the sequence will not be the same;
	 */
	srand( (int)time(NULL) );
    for (size_t i = 0; i < cardDeck.size(); i++) {
        swap(cardDeck[i], cardDeck[rand() % 52]);
    }
}

/*
 * Check if deck is empty
 */
bool Deck::isEmpty() const {
	return ( nextCard >= 52 );
}

/**
 * Copy top card on deck and check if the deck out of range
 */
const Card Deck::draw() {
	if (nextCard >= 52)
		cout << "Out of Range!"<<endl;
	Card c = cardDeck[nextCard];
	nextCard ++;
	return c;
}


