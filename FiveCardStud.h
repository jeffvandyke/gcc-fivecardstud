#ifndef __GAME_H
#define __GAME_H

#include "Player.h"
#include "Card.h"

#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

class FiveCardStud
{
	static const int PLAYER_STARTING_BANK = 100;
public:
	FiveCardStud();
	~FiveCardStud();
	
	void setup(short nPlayers); //initiates a game with the set number of players
	void play(); // plays multiple rounds until someone runs out of money
	void packUp(); // after a game has finished
private:
	void playRound(); // runs many times per game, one winner per round, goes through a few betting rounds
	void performBetting(); // asks for a round of bets, starting from the dealer's left (or next in vector array, first if dealer is last), adding to the pot from player's banks

	int getPot() { return pot; } // dollars
	void emptyPot() { pot = 0; }
	void addPot(int value) { pot += value * 100; }

	//ui functions
	void ui_showPlayerView(short playerId); // make sure you clear the screen and wait for 'ENTER' before showing a player's view!
	void ui_showWinner(short playerId);



	vector<Player> players;
	short dealerId; // contains the index for the player
	//UserInterface ui;
	vector<Card> deck;
	int pot;
};

#endif