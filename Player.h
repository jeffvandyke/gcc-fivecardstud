#ifndef __PLAYER_H
#define __PLAYER_H

#include "Card.h"

#include <string>
#include <vector>

using namespace std;

class Player
{
public:
	Player(void);
	~Player(void);
	void dealHiddenCard(Card card) { hiddenCard = card; }
	void dealVisibleCard(Card card) { visibleCards.push_back(card); }

	vector<Card> collectCards(vector<Card> &deck); //empties out the visible cards vector and puts them back in the deck vector
private:


	vector<Card>visibleCards;
	Card hiddenCard;	
};

#endif