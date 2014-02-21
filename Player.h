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

<<<<<<< HEAD
	void setId(short value) { id = value; }
	int getId() { return id; }
	bool isBetting() { return !(checked); }
	void setBank(int value) { bank = value; }
=======
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
>>>>>>> 91a91671b579f1506da1a04ae36d5b36e163b4b7
	bool isBroke() { return bank == 0; }

	int cardsCount() { return (visibleCardsCount > 0) ? visibleCardsCount + 1 : 0; }
	void dealHiddenCard(Card card) { hiddenCard = card; }
	void dealVisibleCard(Card card) { visibleCards[visibleCardsCount++] = card; }
<<<<<<< HEAD
	
	// implementable

	void collectCards(std::vector<Card> &deck); //empties out the visible cards vector and puts them back in the deck vector
	int getHandValue(); // returns the value of the complete 5 card set 
	int getVisibleHandValue(); // evaluates who starts betting by looking at the set of 4 or less cards to find 
	int getCardInt(Card); // returns the integer value of a card from 2-14


	// ui functions
	void ui_requestName(); // prompts the player to input a name, storing it into the local variable
	void ui_requestBet(); // asks for a bet, makes sure that the player can bet the set amount
=======

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
>>>>>>> 91a91671b579f1506da1a04ae36d5b36e163b4b7

private:
	int getBetInput(int currentBet, int minRaise);

<<<<<<< HEAD

	int id; // may be optional: should match the index in vector array
	std::string name;
	bool checked;
=======
	int id; // should match the index in vector array
	std::string name;
	bool folded;
>>>>>>> 91a91671b579f1506da1a04ae36d5b36e163b4b7
	int bank;
	Card visibleCards[4]; // fixed-size array allows vector to allocate "Player" correctly
	int visibleCardsCount;
	Card hiddenCard;	
};

#endif
