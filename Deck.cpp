#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include "Card.h"
#include "Deck.h"

using namespace std; 

// You can call members functions in constructors, but
// YOU CANNOT CALL CONSTRUCTORS IN MEMBERS FUNCTIONS
Deck::Deck() {
	reset();
}

void Deck::reset() {
	int x = 0;
	while (x < DECK_SIZE) {
		for (int suit = 0; suit < 4; ++suit) {
			for (int rank = 0; rank < 13; ++rank) {
				cards[x] = Card(static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit));  
				x++; 
			}
		}
	}
	next = &cards[0]; 
}

void Deck::shuffle(int n) {
	if(n < 0 || n > 52){
		cout << "Invalid place to cut the deck" << endl;
		return;
	}
	// Array to fill left split deck of n cards
	Card cards_array[52];
	int card_counter = 0;
	int left_in = 0;
	int right_in = n;

	// Making left split deck of n cards
	for(int x = 0; x < n; ++x) {
		cards_array[x] = cards[x]; 
	}

	// Rearrange the deck to be the first card of the right, 
    // then the first card of the left, the 2nd 
    // of right, the 2nd of left, and so on.
	while(left_in < n && right_in < 52) {
		cards[card_counter] = cards[right_in];
		card_counter++;
		right_in++;
		cards[card_counter] = cards_array[left_in];
		card_counter++;
		left_in++;
	}

	// When the right side is exhausted
	if(n > 26) {
		for(int x = card_counter; x < 52; ++x) {
			cards[x] = cards_array[left_in];
			left_in++; 
		}
	}
	next = &cards[0]; 
}

Card Deck::deal() {
	return *next++; 
}

int Deck::cards_remaining() const {
	return 52 - (next - cards); 
}






