// DONE

#include <iostream>
#include <string>
#include <vector>
#include "Card.h"
#include "FiveCardStud.h"

using namespace std;


int main() {
	

	FiveCardStud game;
	
	char playAgain = 'n';
	short numberOfPlayers;
	do {
		cout << "Enter number of players!" << endl;
		cin >> numberOfPlayers;
		
		// to work with getline

		game.setup(numberOfPlayers);
		game.printInstructions();
		game.play();
		game.packUp();

		cout << "Play Again? (y/n)" << endl;
		cin >> playAgain;
		
		} while(playAgain == 'y'|| playAgain == 'Y');
		

	return 0;
}