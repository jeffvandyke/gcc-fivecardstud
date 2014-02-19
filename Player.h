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

	int cardsCount() { return (visibleCards.size() > 0) ? visibleCards.size() + 1 : 0; }
	void collectCards(vector<Card> &deck); //empties out the visible cards vector and puts them back in the deck vector
	int getHandValue(); // returns the value of the complete 5 
	int getVisibleHandValue();
private:

	short id; // may be optional: should match the index in vector array
	string name;
	int bank;
	vector<Card>visibleCards;
	Card hiddenCard;	
};

#endif
