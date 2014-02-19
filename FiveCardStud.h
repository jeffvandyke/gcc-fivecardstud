#ifndef __GAME_H
#define __GAME_H

#include "Player.h"
#include "Card.h"

#include <iostream>
#include <vector>
#include <string>
#include <math.h>


class FiveCardStud
{
	static const int PLAYER_STARTING_BANK = 100;
	static const int ante = 1;
public:
	FiveCardStud();
	~FiveCardStud();
	
	void setup(int nPlayers); //initiates a game with the set number of players
	void play(); // plays multiple rounds until someone runs out of money
	void packUp(); // after a game has finished
private:
	int getPot() { return pot; } // dollars
	void emptyPot() { pot = 0; }
	void addPot(int value) { pot += value * 100; }

	// implementable
	void playRound(); // runs many times per game, one winner per round, goes through a few betting rounds
	void performBetting(); // asks for a round of bets, starting from the dealer's left (or next in vector array, first if dealer is last), adding to the pot from player's banks

	void shuffleDeck();

	// ui functions
	void ui_renderPlayerView(int playerId); // renders complete game view as it appears to player, clears screen and prompts for input
	void ui_showWinner(int playerId);



	std::vector<Player> players;
	int dealerId; // contains the index for the player
	//UserInterface ui;
	std::vector<Card> deck;
	int pot;
};

#endif