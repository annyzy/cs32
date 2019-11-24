/*
 * TerminalPlayer.h
 *
 *  Created on: Nov 22, 2017
 *      Author: student
 */

#ifndef TERMINALPLAYER_H_
#define TERMINALPLAYER_H_

#include "Player.h"
#include "Card.h"

class TerminalPlayer: public Player {
public:
	/**
	 * Constructor;
	 */
	TerminalPlayer(std::string name);

	/**
	 * Destructor;
	 */
	virtual ~TerminalPlayer();

	/**
	 * Play a card. If the player receives a joker then this player is going first
	 */
	const Card playCard(const Card opponentCard);
};

#endif /* TERMINALPLAYER_H_ */
