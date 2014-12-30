#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include "Card.h"

// READ LAST PAGE IN THE SPEC
// TO PROPERLY COUT "RANK of SUIT"
std::ostream& operator << (std::ostream& os, const Card& c) {
	os << c.get_rank() << " of " << c.get_suit(); 
	return os;
}

using namespace std; 

Card::Card() 
	: rank(TWO), suit(SPADES) {}

Card::Card(Rank rank_in, Suit suit_in)
	: rank(rank_in), suit(suit_in) {}

Card::Rank Card::get_rank() const {
	return rank; 
}

Card::Suit Card::get_suit() const {
	return suit; 
}