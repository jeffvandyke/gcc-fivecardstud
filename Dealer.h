#ifndef __DEALER_H
#define __DEALER_H

#include "Card.h"
#include "Player.h"


class Dealer{


public:
	Dealer();
	static double getVal(Card[],Card);
	static double getVal(Card[], int);
	
private:
	static int evalCard(Card);
	



};



#endif