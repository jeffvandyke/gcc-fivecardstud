#include "Player.h"
#include <vector>

using namespace std;

Player::Player(void)
{
	id = 0;
	name = "Newbie";
	checked = false;
	bank = 0;
	visibleCards.clear();
	hiddenCard = Card();
	//new line
}


Player::~Player(void)
{
}

void Player::collectCards(vector<Card> &deck){
	for(int i = 0; i < static_cast<int>(visibleCards.size()); i++){
		deck.push_back(visibleCards[i]);
	}
	visibleCards.clear();
	deck.push_back(hiddenCard);
}


int Player::getHandValue() { // returns the value of the complete 5 card set 

}


int Player::getVisibleHandValue() { // evaluates who starts betting by looking at the set of 4 or less cards to find 

}


// ui functions

void Player::ui_requestName() { // prompts the player to input a name, storing it into the local variable

}


void Player::ui_requestBet() { // asks for a bet, makes sure that the player can bet the set amount
	
}
