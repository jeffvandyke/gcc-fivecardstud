#include "Dealer.h"
#include "Card.h"
#include <array>
#include <algorithm>
using namespace std;


double Dealer::getVal(Card up[], Card hidden){ // up being the face up cards, should be an array of 4 cards. hidden being the player's hidden cards.
	double handVal = 0;

	int type = 0, iD1 = 0, iD2 = 0, iD3 = 0, iD4 = 0, iD5 = 0;

	// Hand value is ranked as follows: 9000000.0000 for straight flushes, 8000000.0000 for 4 of a kind, 7000000.0000 for full house, 6000000.0000 for a flush,
	// 5000000.0000 for a straight, 4000000.0000 for three of a kind, 3000000.0000 for two pair, 2000000.0000 for a pair, 1000000.0000 for high card
	// The series of digits following will be the hand rank according to Identifying cards in the hand.


	bool flush = false;
	bool straight = false;
	Card sortedHand[5];

	// for hand sorting
	int check = 0;
	Card bubbleBuffer;


	//hand sorter/ construction via bubblesort
	for (int i = 0; i<4;i++){

		sortedHand[i] = up[i];

	}
	sortedHand[4] = hidden;

	do{
		check = 0;
		for(int i = 0; i<4; i++){

			if(evalCard(sortedHand[i]) < evalCard(sortedHand[i+1])){
				bubbleBuffer = sortedHand[i];
				sortedHand[i] = sortedHand[i+1];
				sortedHand[i+1] = bubbleBuffer;
				check++;
			}

		}
	}while(check != 0);


	//flush check

	if(sortedHand[0].getSuit() == sortedHand[1].getSuit() == sortedHand[2].getSuit() == sortedHand[3].getSuit() == sortedHand[4].getSuit()){
		flush = true;
	}

	// straight check
	if(	((evalCard(sortedHand[0])-evalCard(sortedHand[1]))== // check for normal straight
		(evalCard(sortedHand[1])-evalCard(sortedHand[2]))==
		(evalCard(sortedHand[2])-evalCard(sortedHand[3]))==
		(evalCard(sortedHand[3])-evalCard(sortedHand[4]))== 1) 
		||
		(evalCard(sortedHand[0])-evalCard(sortedHand[1]))== // check for lowest possible straight with ace at bottom.
		(evalCard(sortedHand[1])-evalCard(sortedHand[2]))==
		(evalCard(sortedHand[2])-evalCard(sortedHand[3]))== 1 && 
		(evalCard(sortedHand[3]) - evalCard(sortedHand[4]) == -12)) 
	{

		straight = true;
	}

	//Hand Rank assignment

	do{

		// straight flush check
		if(straight && flush){
			type = 9;

			if(evalCard(sortedHand[4]) == 2 && evalCard(sortedHand[0])== 14)
				iD1 = 5;
			else
				iD1 = evalCard(sortedHand[0]);
		}

		if(type > 0){ break;}//loop scope break

		// four of a kind check

		for(int i = 2; i<14;i++){
			check = 0;
			if(evalCard(sortedHand[0])== i){check++;}
			if(evalCard(sortedHand[1])== i){check++;}
			if(evalCard(sortedHand[2])== i){check++;}
			if(evalCard(sortedHand[3])== i){check++;}
			if(evalCard(sortedHand[4])== i){check++;}

			if(check == 4){
				type = 8;
				iD1 = i;

			}

		}
		for(int i = 0; i<4; i++){
			if(type == 8 && evalCard(sortedHand[i]) != iD1){
				iD2 = evalCard(sortedHand[i]);
			}
		}

		if(type > 0){ break;}//loop scope break

		//full House Check

		for(int i = 2; i<14;i++){
			check = 0;
			if(evalCard(sortedHand[0])== i){check++;}
			if(evalCard(sortedHand[1])== i){check++;}
			if(evalCard(sortedHand[2])== i){check++;}
			if(evalCard(sortedHand[3])== i){check++;}
			if(evalCard(sortedHand[4])== i){check++;}

			if(check == 3){
				iD1 = i;
			}

		}
		for(int i = 2; i<14;i++){
			check = 0;
			if(evalCard(sortedHand[0])== i && i != iD1){check++;}
			if(evalCard(sortedHand[1])== i && i != iD1){check++;}
			if(evalCard(sortedHand[2])== i && i != iD1){check++;}
			if(evalCard(sortedHand[3])== i && i != iD1){check++;}
			if(evalCard(sortedHand[4])== i && i != iD1){check++;}

			if(check == 2){
				type = 7;
				iD2 = i;

			}

		}
		if(type > 0){break;}// loop scope break

		//flush hand rank check
		if(flush){
			type = 6;
			iD1 = evalCard(sortedHand[0]);
			iD2 = evalCard(sortedHand[1]);
			iD3 = evalCard(sortedHand[2]);
			iD4 = evalCard(sortedHand[3]);
			iD5 = evalCard(sortedHand[4]);

		}

		if(type >0) {break;}// loop scope break

		//straight check
		if(straight){
			type = 5;
			if(!(evalCard(sortedHand[0]) == 14 && evalCard(sortedHand[4]) == 2))
				iD1 = evalCard(sortedHand[0]);
			else
				iD1 = 5;
		}
		if(type >0) {break;}// loop scope break

		// three of a kind check

		for(int i = 2; i<14;i++){
			check = 0;
			if(evalCard(sortedHand[0])== i){check++;}
			if(evalCard(sortedHand[1])== i){check++;}
			if(evalCard(sortedHand[2])== i){check++;}
			if(evalCard(sortedHand[3])== i){check++;}
			if(evalCard(sortedHand[4])== i){check++;}

			if(check == 3){
				type = 4;
				iD1 = i;
			}
		}

		for(int i = 0; i<4; i++){
			if(type == 4 && evalCard(sortedHand[i]) != iD1){
				iD2 = evalCard(sortedHand[i]);
			}
		}

		for(int i=0;i<4;i++){
			if(type== 4 && evalCard(sortedHand[i])!= iD1 && evalCard(sortedHand[i]) != iD2){
				iD3 = evalCard(sortedHand[i]);

			}
		}

		if(type > 0){break;} // loop scope break

		//two pair check/ Pair Check

		for(int i = 14; i>2;i--){
			check = 0;
			if(evalCard(sortedHand[0])== i){check++;}
			if(evalCard(sortedHand[1])== i){check++;}
			if(evalCard(sortedHand[2])== i){check++;}
			if(evalCard(sortedHand[3])== i){check++;}
			if(evalCard(sortedHand[4])== i){check++;}

			if(check == 2){
				iD1 = i;

			}
		}

		for(int i = 14; i>2; i--){
			check = 0;
			if(evalCard(sortedHand[0])== i && i != iD1){check++;}
			if(evalCard(sortedHand[1])== i && i != iD1){check++;}
			if(evalCard(sortedHand[2])== i && i != iD1){check++;}
			if(evalCard(sortedHand[3])== i && i != iD1){check++;}
			if(evalCard(sortedHand[4])== i && i != iD1){check++;}

			if(check == 2){ // case of two pair
				iD2 = i;
				type = 3;
				for(int i = 0; i<4; i++){ // non pair card id
					if(evalCard(sortedHand[i]) != (iD1 || iD2)){
						iD3 = evalCard(sortedHand[i]);

					}
				}
			}

			else{			// case of one pair
				type = 2;
				for(int i = 0; i< 4; i++){
					if(evalCard(sortedHand[i]) != iD1){
						iD2 = evalCard(sortedHand[i]);
						break;
					}
				}

				for(int i = 0; i<4; i++){ // highest non-pair card 
					if(evalCard(sortedHand[i]) != iD1){
						iD2 = evalCard(sortedHand[i]);
						break;
					}
				}

				for(int i = 0; i<4; i++){ // second Highest non-pair card
					if(evalCard(sortedHand[i]) != (iD1 || iD2)){
						iD3 = evalCard(sortedHand[i]);
						break;
					}
				}

				for(int i = 0; i<4; i++){ // last card ID
					if(evalCard(sortedHand[i]) != (iD1||iD2||iD3)){
						iD4 = evalCard(sortedHand[i]);
						break;
					}
				}
			}
		}

		if(type >0){break;} // loop scope break

		// high card eval

		type = 1;
		iD1 = evalCard(sortedHand[0]);
		iD2 = evalCard(sortedHand[1]);
		iD3 = evalCard(sortedHand[2]);
		iD4 = evalCard(sortedHand[3]);
		iD5 = evalCard(sortedHand[4]);



	}while(type = 0);


	handVal = (type*1000000) + (iD1*10000) + (iD2*100) + iD3 + (iD4*.01) + (iD5 * .0001);
	return handVal;
}

double Dealer::getVal(Card up[], int size){
	double value = 0;
	int type = 0, iD1 = 0, iD2 = 0, iD3 = 0, iD4 = 0;
	int check = 0;
	Card sortedHand[4];
	Card bubbleBuffer;


	//hand construction/ sort via bubblesort
	for (int i = 0; i<size;i++){

		sortedHand[i] = up[i];

	}


	do{
		check = 0;
		for(int i = 0; i<size-1; i++){

			if(evalCard(sortedHand[i]) < evalCard(sortedHand[i+1])){
				bubbleBuffer = sortedHand[i];
				sortedHand[i] = sortedHand[i+1];
				sortedHand[i+1] = bubbleBuffer;
				check++;
			}
		}
	}while(check != 0);

	switch(size){

	case 4:

		do{
			// four of a kind check
			for(int i = 2; i<14;i++){
				check = 0;
				if(evalCard(sortedHand[0])== i){check++;}
				if(evalCard(sortedHand[1])== i){check++;}
				if(evalCard(sortedHand[2])== i){check++;}
				if(evalCard(sortedHand[3])== i){check++;}

				if(check == 4){
					type = 8;
					iD1 = i;

				}

			}

			if(type > 0){ break;}//loop scope break

			// three of a kind check

			for(int i = 2; i<14;i++){
				check = 0;
				if(evalCard(sortedHand[0])== i){check++;}
				if(evalCard(sortedHand[1])== i){check++;}
				if(evalCard(sortedHand[2])== i){check++;}
				if(evalCard(sortedHand[3])== i){check++;}

				if(check == 3){
					type = 4;
					iD1 = i;
				}
			}

			for(int i = 0; i<4; i++){
				if(type == 4 && evalCard(sortedHand[i]) != iD1){
					iD2 = evalCard(sortedHand[i]);
				}
			}


			if(type > 0){break;} // loop scope break

			//two pair check/ Pair Check

			for(int i = 14; i>2;i--){
				check = 0;
				if(evalCard(sortedHand[0])== i){check++;}
				if(evalCard(sortedHand[1])== i){check++;}
				if(evalCard(sortedHand[2])== i){check++;}
				if(evalCard(sortedHand[3])== i){check++;}


				if(check == 2){
					iD1 = i;

				}
			}

			for(int i = 14; i>2; i--){
				check = 0;
				if(evalCard(sortedHand[0])== i && i != iD1){check++;}
				if(evalCard(sortedHand[1])== i && i != iD1){check++;}
				if(evalCard(sortedHand[2])== i && i != iD1){check++;}
				if(evalCard(sortedHand[3])== i && i != iD1){check++;}


				if(check == 2){ // case of two pair
					iD2 = i;
					type = 3;
					for(int i = 0; i<4; i++){ // non pair card id
						if(evalCard(sortedHand[i]) != (iD1 || iD2)){
							iD3 = evalCard(sortedHand[i]);

						}
					}
				}

				else{			// case of one pair
					type = 2;
					for(int i = 0; i< 4; i++){
						if(evalCard(sortedHand[i]) != iD1){
							iD2 = evalCard(sortedHand[i]);
							break;
						}
					}

					for(int i = 0; i<4; i++){ // highest non-pair card 
						if(evalCard(sortedHand[i]) != iD1){
							iD2 = evalCard(sortedHand[i]);
							break;
						}
					}

					for(int i = 0; i<4; i++){ // second Highest non-pair card
						if(evalCard(sortedHand[i]) != (iD1 || iD2)){
							iD3 = evalCard(sortedHand[i]);
							break;
						}
					}

				}
			}

			if(type >0){break;} // loop scope break

			// high card eval

			type = 1;
			iD1 = evalCard(sortedHand[0]);
			iD2 = evalCard(sortedHand[1]);
			iD3 = evalCard(sortedHand[2]);
			iD4 = evalCard(sortedHand[3]);

		}while(type = 0);

	case 3:
		do{

			// three of a kind check

			for(int i = 2; i<14;i++){
				check = 0;
				if(evalCard(sortedHand[0])== i){check++;}
				if(evalCard(sortedHand[1])== i){check++;}
				if(evalCard(sortedHand[2])== i){check++;}

				if(check == 3){
					type = 4;
					iD1 = i;
				}
			}


			if(type > 0){break;} // loop scope break

			// Pair Check

			for(int i = 14; i>2;i--){
				check = 0;
				if(evalCard(sortedHand[0])== i){check++;}
				if(evalCard(sortedHand[1])== i){check++;}
				if(evalCard(sortedHand[2])== i){check++;}


				if(check == 2){
					iD1 = i;
					type = 2;
					for(int i = 0; i< 4; i++){
						if(evalCard(sortedHand[i]) != iD1){
							iD2 = evalCard(sortedHand[i]);
							break;
						}
					}
				}
			}


			if(type >0){break;} // loop scope break

			// high card eval

			type = 1;
			iD1 = evalCard(sortedHand[0]);
			iD2 = evalCard(sortedHand[1]);
			iD3 = evalCard(sortedHand[2]);

		}while(type = 0);

	case 2:
		do{


			// Pair Check

			for(int i = 14; i>2;i--){
				check = 0;
				if(evalCard(sortedHand[0])== i){check++;}
				if(evalCard(sortedHand[1])== i){check++;}



				if(check == 2){
					iD1 = i;
					type = 2;

				}
			}



			if(type >0){break;} // loop scope break

			// high card eval

			type = 1;
			iD1 = evalCard(sortedHand[0]);
			iD2 = evalCard(sortedHand[1]);

		}while(type = 0);
	case 1:

		// high card eval

		type = 1;
		iD1 = evalCard(sortedHand[0]);
		iD2 = evalCard(sortedHand[1]);

		

	}

	value = (type*1000000) + (iD1*10000) + (iD2*100) + iD3 + (iD4*.01);
	return value;


}

int Dealer:: evalCard(Card input){ // returns the integer value of the card sent it based upon face value.

	switch(input.getValue()){
	case deuce:
		return 2;
	case trey:
		return 3;
	case four:
		return 4;
	case five:
		return 5;
	case six:
		return 6;
	case seven:
		return 7;
	case eight:
		return 8;
	case nine:
		return 9;
	case ten:
		return 10;
	case jack:
		return 11;
	case queen:
		return 12;
	case king:
		return 13;
	case ace:
		return 14;
	default:
		return -1;

	}


}

