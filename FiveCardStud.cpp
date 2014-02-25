#include "FiveCardStud.h"
#include "Player.h"
#include "Card.h"
#include <cmath>
#include <iostream>
#include <time.h>
using namespace std;


FiveCardStud::FiveCardStud(void) {
	pot = 0;
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
		// player.setName("Player " + std::to_string(i+1));
		
		
		player.ui_requestName();   
		
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
	cout  << endl << endl 
		<< "Each player is dealt one card face-down and one card face up." << endl
		<< "Then there will be a round of betting." << endl
		<< "To bet type fold, check (if current bet = 0), raise #, bet #, # (to raise/bet), or call." << endl
		<< "There is a minimum entry bet, or ante, of $" << ANTE << "." << endl
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

vector<Player*> FiveCardStud::getRoundWinners() {
	// find the winner

	vector<Player*> winners;

	// prefill with a valid player
	winners.push_back(&getBettingPlayer());

	for( int i = 0; i < static_cast<int>(players.size()); i++ ){
		if ((players[i].getHandValue() >= winners[0]->getVisibleHandValue() // winner's hand is higher than guess
			) && players[i].isBetting() ) // winner hasn't folded
		{
			// here, we either add to or replace the winners
			if( players[i].getHandValue() > winners[0]->getHandValue() ){
				winners.clear();
				winners.push_back(&players[i]);
			}
			else
			{
				// add another player
				winners.push_back(&players[i]);
			}
		}
	}
	winners.shrink_to_fit();
	return winners;
}

void FiveCardStud::playRound() {

	// initialize round, playing with an ante, so this is the opening bet for anyone playing.

	roundBet = ANTE;
	minRaise = 0;

	// before the round begins, collect ante from players
	for(int i = 0; i < static_cast<int>(players.size()); i++){
		addPot( players[i].subtractBank(ANTE) );
	}

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
	
	// the highest - value player goes first in betting
	int highId = 0;
	
	// find the highest value player
	for (int i = 0; i < static_cast<int>(players.size()); i++) {
		if (players[i].getVisibleHandValue()
			> players[highId].getVisibleHandValue()) 
		{
			highId = i;
		}
	}

	// get bets from players
	for(int i = 0; i < static_cast<int>(players.size()); i++) {
		// our index needs to cycle around starting at the highId

		int pIndex = (i + highId) % players.size();
		// skip if they have folded or if there is only one left
		if(players[pIndex].isBetting()
			&& nPlayersBetting() > 1)
		{
			// display player view

			ui_renderPlayerView(pIndex);
			int playerBet = players[pIndex].ui_getBet(roundBet, minRaise);
			addPot(playerBet);
		}
	}

}

// DONE
void FiveCardStud::rewardRoundWinner() {

	vector<Player*> winners = getRoundWinners();

	// give the winners (usually 1) the pot
	int nWinners = static_cast<int>(winners.size());
	for(int i = 0; i < nWinners; i++){
		winners[i]->addBank(pot / nWinners);
	}
	pot = pot % nWinners;
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



void clearScreen() {
	for(int i = 0; i < 800; i++)
		cout << endl;
}

void FiveCardStud::ui_renderPlayerView(int playerId) {
	clearScreen();
	cout << "It's " << players[playerId].getName() << "'s turn, press ENTER" << endl;
	system("pause");
	// display ui for this player

	cout << "The pot contains $" << pot << endl; 
	for(int i = 0; i < nPlayersBetting(); i++){
		if((playerId) != i){
			if(players[i].isBetting()){
				cout << players[i].getName() << ": \n";
				players[i].ui_renderHiddenView();
				cout << endl;
			} else {
				cout << players[i].getName() << " is no longer betting.\n";
			}
		}
	}
	cout << "Your information is: \n";
	players[playerId].ui_renderOwnView(); 
	cout << endl;
}


void FiveCardStud::ui_displayEndOfRound(){

	vector<Player*> winners = getRoundWinners();

	for(int i = 0; i < static_cast<int>(winners.size()); i++) {
		cout << endl << winners[i]->getName() << " is ";
		if(i != 0)
			cout << "also ";
		cout << " the winner of this round!" << endl;
	}

	cout << endl;
	
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