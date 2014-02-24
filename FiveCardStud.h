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
	static const int PLAYER_STARTING_BANK = 1000;
	static const int ANTE = 1;
public:
	FiveCardStud();
	~FiveCardStud();
	
	void setup(int nPlayers); //initiates a game with the set number of players
	void printInstructions(); //instructs players how to play
	void play(); // plays multiple rounds until only one person is left
	void packUp(); // after a game has finished

private:
	void addPot(int value) { pot += value; }
	int nPlayersBetting(); // returns number of players that have not checked
	Player& getBettingPlayer(); // returns a reference to a valid betting player
	Player& getRoundWinner(); // returns a reference to the round winner
	// implementable
	void playRound(); // runs many times per game, one winner per round, goes through a few betting rounds
	void performBetting(); // asks for a round of bets from players who can bet
	
	void rewardRoundWinner(); // finds the round winner and awards him the pot
	
	void shuffleDeck();

	// ui functions
	void ui_renderPlayerView(int playerId); // renders complete game view as it appears to player, clears screen and prompts for input
	void ui_displayEndOfRound();
	void displayFanfare();



	std::vector<Player> players;
	int dealerId; // contains the index for the dealer player
	//UserInterface ui;
	std::vector<Card> deck;

	int roundBet;
	int minRaise;
	int pot;
};

#endif