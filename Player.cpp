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

void Player::ui_requestName() { // prompts the player to input their name

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


// DONE
int extractNumber(string input) {
	string numbers;
	for( int i = 0; i < static_cast<int>(input.size()); i++ ) {
		char c = input.at(i);
		if ( isdigit(c) )
			numbers += c;
	}
	return atoi(numbers.c_str());
}

int Player::ui_getBet(int &currentBet, int &minRaise) { 
	// asks for a bet, makes sure that the player can bet the set amount according to betting rules,
	// if the player raises, it must be at least the last raised value

	if (bank == 0){
		cout << "Player " << name << ", ";
		cout << "you are all in, press Enter\n";
		return 0;
	}

	int bet = 0;

	// keywords to check
	string call("call"), raise("raise"), check("check"), fold("fold");

	bool error = false;  // check for errors
	do{

		cout << "Player " << name << ", how will you bet?" << endl;
		cout << "Your Bank is " << bank 
			<< ", current bet is " << (currentBet != 0 ? "$" + to_string(currentBet) : "open");
		if(minRaise > 0) {
			cout << ", minimum raise is $" << minRaise;
		}
		cout << ".\n";

		string input;

		// get input
		input.clear();
		getline(cin, input,'\n');

		// convert to lowercase
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		

		bet = extractNumber(input); // converts string with numbers to number, returns 0 if no number there

		// check for arguments and do appropriate action
		if( input.length() >= 1 ) {
		
			// check to see if string contains
			if (mismatch(call.begin(), call.end(), input.begin()).first == call.end()) {
				bet = currentBet;
			} else if (mismatch(raise.begin(), raise.end(), input.begin()).first == raise.end()) {
				// he typed in 'raise 50', real bet is 50 more than current bet
				bet = currentBet + bet;
			} else if (mismatch(check.begin(), check.end(), input.begin()).first == check.end()) {
				bet = 0;
			} else if (mismatch(fold.begin(), fold.end(), input.begin()).first == fold.end()) {
				// player folds, stop further processing
				folded = true;
				return 0;
			} else { 
			}

		} else { // if we made it this far, the user just pushed enter
			error = true;
		}

		if(bet < currentBet + minRaise && bet != currentBet && !(bet >= bank)) { 
			// if this is an invalid bet (or an 'all in')
			error = true;
		}


		if (error) {
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

	// empty bank accordingly

	subtractBank(bet);


	return bet;
}
