#include "FiveCardStud.h"
#include "Player.h"


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
	} while (players.size() > 1);
}

void FiveCardStud::packUp() {

}

// private:

void FiveCardStud::playRound() {
	
	//deal cards
	while(players[0].cardsCount() < 5){ // don't deal

		//if first time...
		if(players[0].cardsCount() == 0) {
			// ... deal a round of hidden cards
			for(int i = 0; i < static_cast<int>(players.size()); i++) {
				
				Player& player = players[i]; // this player
				Card card = deck.back();
				deck.pop_back();

				player.dealHiddenCard(card);
			}

		}

		for(int i = 0; i < static_cast<int>(players.size()); i++) {
			Player& player = players[i]; // this player
			// deal round of visible cards
			Card card = deck.back();
			deck.pop_back();
				
			player.dealVisibleCard(card);
				
		}

	}
}

void FiveCardStud::performBetting() {
	// betting starts with the person with the highest visible card / hand goes first
	// only allow betting for players that have not checked

}

void FiveCardStud::shuffleDeck() {

}

// ui functions

void FiveCardStud::ui_renderPlayerView(int playerId) {

}


void FiveCardStud::ui_showWinner(int playerId){

}