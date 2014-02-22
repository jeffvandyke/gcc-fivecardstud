#include "FiveCardStud.h"
#include "Player.h"
#include <cmath>


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

	// initialize round
	roundBet = 0;
	minRaise = 0;

	// for each round that we need to deal cards for up to 5 cards... (at least two people still in the round)
	// TODO - get valid player (i.e. make sure the players you're talking about haven't folded)
	while(players[0].cardsCount() < 5 && nPlayersBetting() > 1){

		//if first deal ...
		// TODO, same as before
		if(players[0].cardsCount() == 0) {
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

	// give the player the pot
	winner->addBank(pot);
	pot = 0;
}


void FiveCardStud::shuffleDeck() {
	
}

// ui functions

void FiveCardStud::ui_renderPlayerView(int playerId) {
	
}


void FiveCardStud::ui_showWinner(int playerId){

}