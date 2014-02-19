#include "Player.h"
#include <vector>

using namespace std;

Player::Player(void)
{
	id = 0;
	name = "Newbie";
	checked = false;
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
	if((getCardInt(sortedHand[0]) - getCardInt(sortedHand[1])) == (getCardInt(sortedHand[1]) - getCardInt(sortedHand[2])) == (getCardInt(sortedHand[2])-getCardInt(sortedHand[3]))== (getCardInt(sortedHand[3])-getCardInt(sortedHand[4]))==1 );
	straight = true;



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

}
