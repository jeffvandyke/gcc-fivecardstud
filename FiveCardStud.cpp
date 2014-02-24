#include "FiveCardStud.h"
#include "Player.h"
#include <cmath>
#include <iostream>
#include <time.h>
using namespace std;


FiveCardStud::FiveCardStud(void) {
	
}


FiveCardStud::~FiveCardStud(void) {

}




void FiveCardStud::setup(int nPlayers){

	players.clear();
	players.reserve(nPlayers);
	for(int i = 0; i < nPlayers; i++) {
		Player player;

		// prepare the character
		player.setId(i);
		player.setName("Player " + std::to_string(i+1));
		
		// TODO: change after implementation
		// player.ui_requestName();   
		
		player.setBank(PLAYER_STARTING_BANK);

		players.push_back(player);


	}

	// set up deck
	for(int nSuit = 0; nSuit < 4; nSuit++) {
		for(int nValue = 0; nValue < 13; nValue++) {
			Card card = Card(static_cast<Value>(nValue), static_cast<Suit>(nSuit));
			deck.push_back(card);
		}
	}
	
	shuffleDeck();

}

void FiveCardStud::printInstructions(){
	cout << "Each player is dealt one card face-down and one card face up." << endl
		<< "Then there will be a round of betting. To bet type fold, check (if current bet = 0), raise #, bet #, # (to raise/bet), or call." << endl
		<< "There is a minimum entry bet, or ante, of $1." << endl
		<< "The next three rounds will consist of players being dealt one card face-up and a round of betting." << endl
		<< "For each round of betting the first player to bet will be the player with the highest card showing." << endl
		<< "At the end of each round the player with the best hand gets the pot." << endl
		<< "Once all players but one have lost their money, the one remaining wins!" << endl;
	
	system("PAUSE");

	for(int i=0; i < 200; i++)
		cout << endl;

}

void FiveCardStud::play() {
	// game ends when all players are broke, players are removed on becoming broke 
	do {
		playRound();

		// remove broke players
		for(int i = static_cast<int>(players.size()) - 1; i >= 0 ; i--) { // work backwards to avoid indexing issues
			if( players[i].isBroke() )
				players.erase(players.begin() + i);
		}
		// reindex after erasure

		for (int i = 0; i < static_cast<int>(players.size()); i++) {
			players[i].setId(i);
		}

	} while (players.size() > 1);

	displayFanfare();
}

// DONE
void FiveCardStud::packUp() {
	for (int i = 0; i < static_cast<int>(players.size()); i++) {
		players[i].collectCards(deck);
	}
}

// private:

// DONE
int FiveCardStud::nPlayersBetting() { 
	int nBetting = 0;
	for( int i = 0; i < static_cast<int>(players.size()); i++ ){
		if (players[i].isBetting())
			nBetting++;
	}
	return nBetting;
}

Player& FiveCardStud::getBettingPlayer() {
	for( int i = 0; i < static_cast<int>(players.size()); i++ ) {
		if (players[i].isBetting())
			return players[i];
	}

	// if no betting players, we shouldn't be calling this function - the code should forbid it
	throw new exception("no betting players");
}

Player& FiveCardStud::getRoundWinner() {
	// find the winner

	Player* winner = &getBettingPlayer();
	for( int i = 0; i < static_cast<int>(players.size()); i++ ){
		if ((players[i].getHandValue() > winner->getVisibleHandValue() // winner's hand is higher than guess
			) && players[i].isBetting() ) // winner hasn't folded
		{
			winner = &players[i];
		}
	}

	return *winner;
}

void FiveCardStud::playRound() {

	// initialize round
	roundBet = 0;
	minRaise = 0;

	// for each round that we need to deal cards for up to 5 cards... (at least two people still in the round)
	// TODO - get valid player (i.e. make sure the players you're talking about haven't folded)
	while(getBettingPlayer().cardsCount() < 5 && nPlayersBetting() > 1){

		//if first deal ...
		// TODO, same as before
		if(getBettingPlayer().cardsCount() == 0) {
			// ... deal a round of hidden cards
			for(int i = 0; i < static_cast<int>(players.size()); i++) {
				
				Player& player = players[i]; // this player
				Card card = deck.back();
				deck.pop_back();

				player.dealHiddenCard(card);
			}

		}

		// ... deal a round of visible cards
		for(int i = 0; i < static_cast<int>(players.size()); i++) {
			Player& player = players[i]; // this player
			if( player.isBetting() ) {
				Card card = deck.back();
				deck.pop_back();
				
				player.dealVisibleCard(card);
			}
				
		}

		performBetting();
		
	}

	// round is over, clean up and prepare for the next round

	rewardRoundWinner();

	// collect each player's cards
	for(int i = 0; i < static_cast<int>(players.size()); i++) {
		players[i].collectCards(deck);
	}

	ui_displayEndOfRound();

	shuffleDeck();

}


void FiveCardStud::performBetting() {
	// betting starts with the person with the highest visible card / hand goes first
	// only allow betting for players that have not folded
	// players have to bet at least the "round bet"


	// for testing, remove as desired
	for(int i = 0; i < static_cast<int>(players.size()); i++) {
		int playerBet = players[i].ui_getBet(roundBet, minRaise);
		addPot(playerBet);
	}

}

// DONE
void FiveCardStud::rewardRoundWinner() {

	Player winner = getRoundWinner();

	// give the player the pot
	winner.addBank(pot);
	pot = 0;
}


void FiveCardStud::shuffleDeck() {

	Card place_hold;
	srand(time(0));

	for(int k = 1; k < 100010; k++) {
		for(int i = 0; i < (static_cast<int>(deck.size()) - 1 ); i++) {
			if(rand() > rand()) {
				place_hold = deck[i];
				deck[i] = deck[i+1];
				deck[i+1] = place_hold;
			}
		}

	}

}

// ui functions

void FiveCardStud::ui_renderPlayerView(int playerId) {
	std::cout << "The pot contains " << pot << std::endl; 
	players[playerId-1].ui_renderOwnView();  
	for(int i = 0; i < nPlayersBetting(); i++){
		if((playerId-1) != i){
			std::cout << players[i].getName() << ": \n";
			players[i].ui_renderHiddenView();
		}
		std::cout << "All other players are no longer betting.\n";
	}

}


void FiveCardStud::ui_displayEndOfRound(){

	Player winner = getRoundWinner();

	cout << endl << winner.getName() << " is the winner of this round." << endl << endl;

	for(int i = 0; i <  static_cast<int>(players.size()); i++)
		cout << players[i].getName() << " has $" << players[i].getBank() << " remaining." << endl;

	cout << endl << endl << endl;
	system("pause");


}

void FiveCardStud::displayFanfare() {
	for(int i = 0; i < 100; i++) {
		cout << "0     1          0  1          1    1     1  1     1     0    1"
			<< "    1     0      1     1     0          1         0      0     0 "
			<< " 1         0        1        0    1   0        1   1   0  0 1    1  "
			<< "1     0        0    1    0    1    0       1   0   0   0"
			<< "         0    1   1     1    0      1      1         1    1    0    0     0  ";
	}

	cout << endl << "Congratulations: " << players[0].getName() << endl << "You are the victor!" << endl;
}