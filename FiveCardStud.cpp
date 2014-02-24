#include "FiveCardStud.h"
#include "Player.h"
#include "Dealer.h"
<<<<<<< HEAD
=======
#include <cmath>
>>>>>>> 91a91671b579f1506da1a04ae36d5b36e163b4b7


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
<<<<<<< HEAD
=======
		player.setName("Player " + std::to_string(i));
>>>>>>> 91a91671b579f1506da1a04ae36d5b36e163b4b7
		
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

	// TODO: change after implementation
	//shuffleDeck();

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
<<<<<<< HEAD
=======
		// reindex after erasure

		for (int i = 0; i < static_cast<int>(players.size()); i++) {
			players[i].setId(i);
		}

>>>>>>> 91a91671b579f1506da1a04ae36d5b36e163b4b7
	} while (players.size() > 1);
}

// DONE
void FiveCardStud::packUp() {
	for (int i = 0; i < static_cast<int>(players.size()); i++) {
		players[i].collectCards(deck);
	}
}

// DONE
int FiveCardStud::nPlayersBetting() { 
	int nBetting = 0;
	for( int i = 0; i < static_cast<int>(players.size()); i++ ){
		if (players[i].isBetting())
			nBetting++;
	}
	return nBetting;
}

// private:

void FiveCardStud::playRound() {
<<<<<<< HEAD
	
	//deal cards
	while(players[0].cardsCount() < 5){ // don't deal

		//if first time...
		if(players[0].cardsCount() == 0) {
			// ... deal a round of hidden cards
			for(int i = 0; i < static_cast<int>(players.size()); i++) {
				
				Player& player = players[i]; // this player
				Card card = deck.back();
				deck.pop_back();

=======

	// initialize round
	roundBet = 0;
	minRaise = 0;

	// for each round that we need to deal cards for up to 5 cards... (at least two people still in the round)
	while(players[0].cardsCount() < 5 && nPlayersBetting() > 1){

		//if round 1 ...
		if(players[0].cardsCount() == 0) {
			// ... deal a round of hidden cards
			for(int i = 0; i < static_cast<int>(players.size()); i++) {
				
				Player& player = players[i]; // this player
				Card card = deck.back();
				deck.pop_back();

>>>>>>> 91a91671b579f1506da1a04ae36d5b36e163b4b7
				player.dealHiddenCard(card);
			}

		}

<<<<<<< HEAD
		for(int i = 0; i < static_cast<int>(players.size()); i++) {
			Player& player = players[i]; // this player
			// deal round of visible cards
			Card card = deck.back();
			deck.pop_back();
				
			player.dealVisibleCard(card);
				
		}

=======
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
		
>>>>>>> 91a91671b579f1506da1a04ae36d5b36e163b4b7
	}

	// round is over, clean up and prepare for the next round

	rewardRoundWinner();

	// collect each player's cards
	for(int i = 0; i < static_cast<int>(players.size()); i++) {
		players[i].collectCards(deck);
	}

}


void FiveCardStud::performBetting() {
	// betting starts with the person with the highest visible card / hand goes first
<<<<<<< HEAD
	// only allow betting for players that have not checked

}

void FiveCardStud::shuffleDeck() {
=======
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

	// find the winner

	Player* winner = &players[0];
	for( int i = 0; i < static_cast<int>(players.size()); i++ ){
		if ((players[i].getHandValue() > winner->getVisibleHandValue() // winner's hand is higher than guess
			|| winner->hasFolded()
			) && !players[i].hasFolded() ) // winner hasn't folded
		{
			winner = &players[i];
		}
	}
>>>>>>> 91a91671b579f1506da1a04ae36d5b36e163b4b7

	// give the player the pot
	winner->addBank(pot);
	pot = 0;
}

<<<<<<< HEAD
// ui functions

void FiveCardStud::ui_renderPlayerView(int playerId) {

=======

void FiveCardStud::shuffleDeck() {
	
}

// ui functions

void FiveCardStud::ui_renderPlayerView(int playerId) {
	
>>>>>>> 91a91671b579f1506da1a04ae36d5b36e163b4b7
}


void FiveCardStud::ui_showWinner(int playerId){

}