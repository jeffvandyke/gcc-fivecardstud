#include "Player.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

Player::Player(void)
{
	id = 0;
	name = "Newbie";
	<<<<<<< HEAD
		checked = false;
	=======
		folded = false;
	>>>>>>> 91a91671b579f1506da1a04ae36d5b36e163b4b7
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


<<<<<<< HEAD
	// Pre-conditions: The full hand of 5 cards must have been dealt already and in proper location
	// Post-conditions: an integer with the hand value will be created and available.

	int Player::getHandValue() { // returns the value of the complete 5 card set 

		int handValue = 0; // final hand value.
		int topCard = 0;// top card of the hand 
		int secondID = 0;// the next identifying card value: dependent on hand type.

		// value will be in terms of an integer ranking with each increment of 100 being the next rank: as follows
		// 90000: straight flush, 80000: 4 of a kind, 70000: full house, 60000: flush
		// 50000: straight, 40000: three of a kind, 20000: two pair, 10000: single pair, 00000: high card

		bool flush = false;
		bool straight = false;
		int modifier = 0; // for classifying the hand within the type will be latter 4 digits, the first two
		// the first two digits being the first identifying card, the latter two being the second
		// the second identifying card.

		Card sortedHand[5];
		Card buffer;
		int bubbleCheck = 0;


		// top card check: it stores the int value of the top card in the top card 
		for(int i = 0; i<4; i++){

			if(getCardInt(visibleCards[i])*100 > topCard)
				topCard = getCardInt(visibleCards[i])*100;

		}

		if(getCardInt(hiddenCard)*100 > topCard)
			topCard = getCardInt(hiddenCard)*100;

		// flush check
		if(visibleCards[0].getSuit() == visibleCards[1].getSuit() == visibleCards[2].getSuit() == visibleCards[3].getSuit() == hiddenCard.getSuit())
			flush = true;

		// straight check
		// first loading all cards into a single hand array
		for(int i = 0; i<4; i++){

			sortedHand[i]= visibleCards[i];

		}
		sortedHand[4]= hiddenCard;

		// now sorting by value via bubble sort

		do{
			bubbleCheck = 0;
			for(int i = 0; i<4; i++){
				if(getCardInt(sortedHand[i]) < getCardInt(sortedHand[i+1])){
					buffer = sortedHand[i];
					sortedHand[i] = sortedHand[i+1];
					sortedHand[i+1] = buffer;

					bubbleCheck++;
				}


			}



		}while(bubbleCheck != 0);
		// now checking consecutive values
		if((getCardInt(sortedHand[0]) - getCardInt(sortedHand[1])) == (getCardInt(sortedHand[1]) - getCardInt(sortedHand[2])) == (getCardInt(sortedHand[2])-getCardInt(sortedHand[3]))== (getCardInt(sortedHand[3])-getCardInt(sortedHand[4]))==1 ){
			straight = true;
		}


		return handValue;
}

int Player::getCardInt(Card input){ // returns the integer value of a card based upon the card class's "value" property
	int val = 0;

	switch (input.getValue()){
	case deuce:
		val = 2;
		break;
	case trey:
		val = 3;
		break;
	case four:
		val = 4;
		break;
	case five:
		val = 5;
		break;
	case six:
		val = 6;
		break;
	case seven:
		val = 7;
		break;
	case eight:
		val = 8;
		break;
	case nine:
		val = 9;
		break;
	case ten:
		val = 10;
		break;
	case jack:
		val = 11;
		break;
	case queen:
		val = 12;
		break;
	case king:
		val = 13;
		break;
	case ace:
		val = 14;
		break;
	default:
		val = -1; //ERROR FLAG: THIS SHOULD NOT OCCUR!

	}

	return val;
}


int Player::getVisibleHandValue() { // evaluates who starts betting by looking at the set of 4 or less cards to find value



	return 0;
}


// ui functions

void Player::ui_requestName() { // prompts the player to input a name, storing it into the local variable

}


void Player::ui_requestBet() { // asks for a bet, makes sure that the player can bet the set amount

	=======
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

		if (folded)
			return 0;


		if (bank == 0){
			cout << "Player " << name << ", ";
			cout << "you are all in, press Enter\n";
			cin.get();
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
