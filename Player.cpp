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



void printBettingInstructions(int currentBet, int minRaise);
int extractNumber(string input);


// DONE!!!
int Player::ui_getBet(int &currentBet, int &minRaise) { 
	// asks for a bet, makes sure that the player can bet the set amount according to betting rules,
	// if the player raises, it must be at least the last raised value

	if (folded) {
		cout << name << " has folded.\n";
		return 0;
	}


	if (bank == 0){
		cout << name << " is all in.\n";
		return 0;
	}

	int bet = getBetInput(currentBet, minRaise);

	// check to see if player folded
	if (bet == -1) {
		folded = true;
		return 0;
	}

	// process player's bet with the system

	// adjust minRaise if this is not the opening bid

	if(currentBet != 0 && bet >= currentBet + minRaise)
		minRaise = bet - currentBet;

	// set current bet if not an all in
	if (bet >= currentBet)
		currentBet = bet;

	// empty bank accordingly

	subtractBank(bet);

	// all done!
	return bet;
}

void Player::ui_renderHiddenView() {
	
}




// private:

// DONE
int Player::getBetInput(int currentBet, int minRaise) {
	// this function parses user input to get a bet from the user.
	// the return value will be the amount coming out of the player's bank
	// , or -1 if the player folded.
	
	// keywords to check
	string s_bet("bet"), call("call"), raise("raise"), check("check"), fold("fold");

	bool error = false;  // check for errors

	int bet = 0; // value to return
	
	do{
		error = false; // reset
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
		getline(cin, input);

		// convert to lowercase
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		

		bet = extractNumber(input); // converts string with numbers to number, returns 0 if no number there

		// check for arguments and do appropriate action
		if( input.length() >= 1 ) {
		
			// the mismatch snippet check to see if string contains the keyword specified
			if (mismatch(s_bet.begin(), s_bet.end(), input.begin()).first == s_bet.end()) {
				// 'bet 20'
				// do nothing, bet is correct value
			} else if (mismatch(call.begin(), call.end(), input.begin()).first == call.end()) {
				// 'call'
				bet = currentBet;
			} else if (mismatch(raise.begin(), raise.end(), input.begin()).first == raise.end()) {
				// 'raise 50' - real bet is 50 more than current bet

				if ( bet == 0 )
					//if they just typed in 'raise'
					bet = minRaise;

				if( bet >= minRaise ) { // if raise is valid
					bet = currentBet + bet;
				} else { // user tried to set an invalid raise
					
					error = true;
				}
			} else if (mismatch(check.begin(), check.end(), input.begin()).first == check.end()) {
				// 'check'
				bet = 0;
			} else if (mismatch(fold.begin(), fold.end(), input.begin()).first == fold.end()) {
				// 'fold' - player folds, stop further processing
				return -1;
			} else { 
				// no matches, check if input is not just a number
				if ( !isdigit(input[0]) )
					error = true;
			}
		} else { // if we made it this far, the user just pushed enter
			error = true;
		}
		
		// check for all-in
		if (bet > bank)
			bet = bank;

		// has to either = bet, be greater than minRaise + bet, but exceptions are made for 'all in's
		if(!(bet >= currentBet + minRaise || bet == currentBet) && bet < bank) { 
			// if this is an invalid bet (and it's not an 'all in')
			error = true;
		}


		if (error) {
			cout << "You can't do that!\n";
			printBettingInstructions(currentBet, minRaise);
		}

		//ask until no errors
	} while( error );

	return bet;
}






// supplemental ui functions

// DONE
void printBettingInstructions(int currentBet, int minRaise) {
	// prints instructions to the screen for betting
	cout << "Betting Instructions: \n"
		<< "To place a bet, your bet must be at least the current round bet for this\n"
		<< "round, which is $" << currentBet << ". ";
	if( currentBet > 0 )
		cout << "You may type 'call' to bid this amount. \n";

	cout << "If you want, you can 'raise' the current bet, but you must raise by at least \n"
		<< "the amount someone has raised before, ";
	if (minRaise > 0) {
		cout << "which would be $" << minRaise << " this time, making your total bet equal to "
			<< "at least $"	<< currentBet + minRaise << ". \n";
	} 
	else {
		cout << "which is nothing right now, so you could raise by however much you want. \n";
	}
	if (currentBet == 0) {
		cout << "You can also 'check' to bid nothing, and if you raise, anything you raise will not be a requirement "
			<< "for other players to raise because this is the opening bet. \n";
	}

	cout << "examples: 'check', 'bet 50', '50', 'raise 10', 'fold', 'call' \n";
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
