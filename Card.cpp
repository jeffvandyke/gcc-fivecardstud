#include "Card.h" 
#include <stdexcept> 
#include <iostream>


string Card::suitName(Suit s) { 
	switch(s) { 
	case clubs: return "Clubs"; 
	case diamonds: return "Diamonds"; 
	case hearts: return "Hearts"; 
	case spades: return "Spades"; 
	default: throw std::out_of_range("Suit value out of range"); 
	} 
} 

string Card::valueName(Value v) { 
	switch(v) { 
	case ace: return "A"; 
	case deuce: return "2"; 
	case trey: return "3"; 
	case four: return "4"; 
	case five: return "5"; 
	case six: return "6"; 
	case seven: return "7"; 
	case eight: return "8"; 
	case nine: return "9"; 
	case ten: return "10"; 
	case jack: return "J";
	case queen: return "Q"; 
	case king: return "K"; 
	default: throw std::out_of_range("Face value out of range"); 
	} 
}

void Card::ui_renderCard(){
	std::cout << valueName(getValue());
	char suit;
	suit = suitName(getSuit()).at(0);
	switch (suit) {
		case 'H':
			std::cout << char(3);
			break;
		case 'D':
			std::cout << char(4);
			break;
		case 'C':
			std::cout << char(5);
			break;
		case 'S':
			std::cout << char(6);
			break;
		default:
			std::cout << "Something's wrong. Ending program\n";
				exit(1);
	}
					

}