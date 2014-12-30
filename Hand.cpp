#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include "Card.h"
#include "Deck.h"
#include "Hand.h"

using namespace std;

// You don't need to store the actual card values in a hand
// object.
// The only thing that matters is what the value of all the 
// cards in the hand is and whether or not the hand is hard 
// or soft. This is why there is no array member variable 

Hand::Hand() {
	discard_all(); 
}

void Hand::discard_all() {
	value = 0;
	soft = false;

}

void Hand::add_card(Card c) {
	int RANK_VALUES_SOFT[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10,
		10, 10, 10, 11};
	int RANK_VALUES_HARD[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10,
		10, 10, 10, 1};
	for(int rank = 0; rank < 13; ++rank) {
		if (static_cast<Card::Rank>(rank) == c.get_rank()) {
			if(rank == 12) {
				if (value + 11 > 21) {
					if(soft) {
						value = value - 10; 
						value = value + RANK_VALUES_SOFT[rank];
						if(value > 21) {
							cout << value << endl;
							value = value - 11; 
							value = value + RANK_VALUES_HARD[rank];
							soft = false;
						}
						else {
							soft = true; 
						}
					}
					else {
						value = value + RANK_VALUES_HARD[rank];
						soft = false;
					}
				}

				else {
						value = value + RANK_VALUES_SOFT[rank];
						soft = true; 
					}
			}
			else if (value + RANK_VALUES_HARD[rank] > 21 && soft == true) { 
				value = value - 10;
				soft = false;
				value = value + RANK_VALUES_HARD[rank];
			}
			else {
				value = value + RANK_VALUES_HARD[rank];
			}
		}
	}
}

int Hand::hand_value() const {
	// if(value > 21){
		// return value + some high number (100);
	//}
	return value; 
}

// NOT SURE ABOUT THIS
bool Hand::hand_is_soft() const{
	if (soft) {
		return true; 
	}
	return false;
}

