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
<<<<<<< HEAD
	static const int PLAYER_STARTING_BANK = 100;
	static const int ante = 1;
=======
	static const int PLAYER_STARTING_BANK = 1000;
	static const int ANTE = 1;
>>>>>>> 91a91671b579f1506da1a04ae36d5b36e163b4b7
public:
	FiveCardStud();
	~FiveCardStud();
	
	void setup(int nPlayers); //initiates a game with the set number of players
<<<<<<< HEAD
	void play(); // plays multiple rounds until someone runs out of money
=======
	void play(); // plays multiple rounds until only one person is left
>>>>>>> 91a91671b579f1506da1a04ae36d5b36e163b4b7
	void packUp(); // after a game has finished

private:
<<<<<<< HEAD
	int getPot() { return pot; } // dollars
	void emptyPot() { pot = 0; }
	void addPot(int value) { pot += value * 100; }

	// implementable
	void playRound(); // runs many times per game, one winner per round, goes through a few betting rounds
	void performBetting(); // asks for a round of bets, starting from the dealer's left (or next in vector array, first if dealer is last), adding to the pot from player's banks

	void shuffleDeck();

=======
	void addPot(int value) { pot += value; }
	int nPlayersBetting(); // returns number of players that have not checked
	
	// implementable
	void playRound(); // runs many times per game, one winner per round, goes through a few betting rounds
	void performBetting(); 
	// asks for a round of bets from players who can bet

	void rewardRoundWinner(); // finds the round winner and awards him the pot
	
	void shuffleDeck();

>>>>>>> 91a91671b579f1506da1a04ae36d5b36e163b4b7
	// ui functions
	void ui_renderPlayerView(int playerId); // renders complete game view as it appears to player, clears screen and prompts for input
	void ui_showWinner(int playerId);



	std::vector<Player> players;
<<<<<<< HEAD
	int dealerId; // contains the index for the player
	//UserInterface ui;
	std::vector<Card> deck;
=======
	int dealerId; // contains the index for the dealer player
	//UserInterface ui;
	std::vector<Card> deck;

	int roundBet;
	int minRaise;
>>>>>>> 91a91671b579f1506da1a04ae36d5b36e163b4b7
	int pot;
};

#endif