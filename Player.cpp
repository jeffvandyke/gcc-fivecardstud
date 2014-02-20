#include "Player.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

Player::Player(void)
{
	id = 0;
	name = "Newbie";
	folded = false;
	bank = 0;
	visibleCardsCount = 0;
	hiddenCard = Card();
	//new line
}


Player::~Player(void)
{
}

void Player::collectCards(vector<Card> &deck){
	if( visibleCardsCount > 0 ) {
		for(int i = 0; i < visibleCardsCount; i++){
			deck.push_back(visibleCards[i]);
		}

		visibleCardsCount = 0;
		deck.push_back(hiddenCard);
	}
}


void maxAssign(int &target, int &source) {
	if (source > target)
		target = source;
}

int Player::getHandValue() { // returns the value of the complete 5 card set 
	
	return 0;
}



int Player::getVisibleHandValue() { // evaluates who starts betting by looking at the set of 4 or less cards to find value
	int handValue = 0;

	


	return 0;
}





// ui functions

void clearScreen() {
	
}

void Player::ui_requestName() { // prompts the player to input a name, storing it into the local variable

}


void printBettingInstructions(int currentBet, int minRaise) {
	// prints instructions to the screen for betting
	cout << "To place a bet, your bet must be at least the current round bet "
		<< "for this round, which is $" << currentBet << ". You may type ""call"" to bid this amount.\n"
		<< "If you want to ""raise"" the round bet, you must raise by at least the amount someone has"
		<< "raised before, ";
	if (minRaise > 0) {
		cout << "which would be $" << minRaise << " this time, making your total bet equal to "
			<< "at least $"	<< currentBet + minRaise << ". ";
	} 
	else {
		cout << "which is nothing right now, so you could raise by however much you want. ";
	}
	cout << "\n";
	if (currentBet == 0) {
		cout << "You can also ""check"" to bid nothing, and if you raise, anything you raise will not be a requirement "
			<< "for other players to raise because this is the ""opening"" bet. \n";
	}

	// TODO: give examples (call, raise 10, 50)
}

int Player::ui_getBet(int &currentBet, int &minRaise) { 
	// asks for a bet, makes sure that the player can bet the set amount according to betting rules,
	// if the player raises, it must be at least
	
	cout << "Player " << name << ", how will you bet?" << endl;

	int bet = 0;
	string input;

	// keywords to check
	string call("call"), raise("raise"), check("check");

	bool error = false;  // check for errors
	do{
		// get input
		getline(cin, input, '\n');

		// convert to lowercase
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		


		// TODO: why doesn't this work?

		bet = atoi(input.c_str()); // converts string with numbers to number, returns 0 if no number there

		// check for arguments and do appropriate action
		if( input.length() >= call.length() ) {
		
			if (mismatch(call.begin(), call.end(), input.begin()).first == call.end()) {
				
			} else if (mismatch(raise.begin(), raise.end(), input.begin()).first == raise.end()) {

			} else if (mismatch(check.begin(), check.end(), input.begin()).first == check.end()) {
				bet = 0;
			}

		}

		if(!(bet >= currentBet + minRaise || bet == currentBet)) { // if this is NOT a valid bet
			error = true;
			cout << "You can't do that!\n";
			printBettingInstructions(currentBet, minRaise);
		}

		//ask until no errors
	} while( error );

	// process player's bet with the system

	// adjust minRaise if this is not the opening bid

	if(currentBet != 0 && bet >= currentBet + minRaise)
		minRaise = bet - currentBet;

	if (bet >= currentBet)
		currentBet = bet;

	


	return bet;
}
