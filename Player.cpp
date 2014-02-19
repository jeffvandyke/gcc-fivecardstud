#include "Player.h"
#include <vector>

using namespace std;

Player::Player(void)
{
	//new line
}


Player::~Player(void)
{
}

void Player::collectCards(vector<Card> &deck){
	for(int i; i < visibleCards.size(); i++){
		deck.push_back(visibleCards[i]);
	}
	visibleCards.clear();
	deck.push_back(hiddenCard);
}
