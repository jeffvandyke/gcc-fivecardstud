#ifndef __PLAYER_H
#define __PLAYER_H

#include "Card.h"

#include <string>
#include <vector>


class Player
{
public:
	Player(void);
	~Player(void);

	void setId(short value) { id = value; }
	int getId() { return id; }
	bool isBetting() { return !(checked); }
	void setBank(int value) { bank = value; }
	bool isBroke() { return bank == 0; }

	int cardsCount() { return (visibleCardsCount > 0) ? visibleCardsCount + 1 : 0; }
	void dealHiddenCard(Card card) { hiddenCard = card; }
	void dealVisibleCard(Card card) { visibleCards[visibleCardsCount++] = card; }
	
	// implementable

	void collectCards(std::vector<Card> &deck); //empties out the visible cards vector and puts them back in the deck vector
	int getHandValue(); // returns the value of the complete 5 card set 
	int getVisibleHandValue(); // evaluates who starts betting by looking at the set of 4 or less cards to find 
	int getCardInt(Card); // returns the integer value of a card from 2-14


	// ui functions
	void ui_requestName(); // prompts the player to input a name, storing it into the local variable
	void ui_requestBet(); // asks for a bet, makes sure that the player can bet the set amount

private:


	int id; // may be optional: should match the index in vector array
	std::string name;
	bool checked;
	int bank;
	Card visibleCards[4]; // fixed-size array allows vector to allocate "Player" correctly
	int visibleCardsCount;
	Card hiddenCard;	
};

#endif
