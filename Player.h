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

	void startRound() { folded = false; }
	void setId(int value) { id = value; }
	int getId() { return id; }
	std::string getName() {return name; }
	void setName(std::string value) { name = value; }
	bool isBetting() { return !(folded); }
	bool hasFolded() { return (folded); }
	void setBank(int value) { bank = value; }
	void addBank(int value) { bank += value; }
	void subtractBank(int value) { 
		if (value < bank) {
			bank -= value; 
		} else { bank = 0; } 
	}
	bool isBroke() { return bank == 0; }

	int cardsCount() { return (visibleCardsCount > 0) ? visibleCardsCount + 1 : 0; }
	void dealHiddenCard(Card card) { hiddenCard = card; }
	void dealVisibleCard(Card card) { visibleCards[visibleCardsCount++] = card; }

	// implementable

	void collectCards(std::vector<Card> &deck); 
	//empties out the visible cards vector and puts them back in the deck vector
	int getHandValue(); 
	// returns the value of the complete 5 card set 
	int getVisibleHandValue(); 
	// evaluates who starts betting by looking at the set of 4 or less cards to find 

	// ui functions

	void ui_requestName(); 
	// prompts the player to input a name, storing it into the local variable
	int ui_getBet(int &currentBet, int &minRaise); 
	// asks for a bet, makes sure that the player can bet the set amount
	void ui_renderHiddenView(); 
	// outputs this character's cards (hiding the hidden one) showing what he looks like to other players

private:
	void fold() { folded = true; }

	int id; // should match the index in vector array
	std::string name;
	bool folded;
	int bank;
	Card visibleCards[4]; // fixed-size array allows vector to allocate "Player" correctly
	int visibleCardsCount;
	Card hiddenCard;	
};

#endif
