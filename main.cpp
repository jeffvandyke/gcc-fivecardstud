// DONE

#include <iostream>
#include <string>
#include <vector>

#include "FiveCardStud.h"

using namespace std;


int main() {

	FiveCardStud game;
	
	char playAgain = 'n';
	short numberOfPlayers;
	do {
		cout << "Enter number of players!" << endl;
		cin >> numberOfPlayers;

		game.setup(numberOfPlayers);
		game.play();
		game.packUp();

		cout << "Play Again? (y/n)" << endl;
		cin >> playAgain;
	} while(playAgain == 'y');

	return 0;
}