#include "Card.h"
#include "Hand.h"
#include "Player.h"
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <cstring>

using namespace std;

class Simple:  public Player {
//Overview: A subclass of Player that will use a simple playing strategy

//implementation of simple player
	public:
		int bet(unsigned int bankroll, unsigned int minimum){
			if(bankroll >= minimum){
				return minimum;
			}
			return 0;
		}

		bool draw(Card dealer, const Hand &player){

			int i = 0;
			int Rank_values[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

			while(dealer.get_rank() != static_cast<Card::Rank>(i)){
				++i;
			}

			if(player.hand_is_soft() == false) {
				if(player.hand_value() <= 11){
					return true;
				}

				else if(player.hand_value() < 13 && Rank_values[i] >= 4 && Rank_values[i] <= 6){
					return false;
				}
	
				else if(player.hand_value() < 17 && Rank_values[i] >= 2 && Rank_values[i] <= 6){
					return false;
				}

				else if(player.hand_value() >=17){
					return false;
				}	
			}

			else{
				if(player.hand_value() <= 17){
					return true;
				}

				else if(player.hand_value() < 19 && Rank_values[i] >= 2 && Rank_values[i] <= 8){
					return false;
				}

				else{
					return false;
				}
			}
			// control reaches end of non-void function fix:
			return false;
		}

		void expose(Card c) {
			return;
		}

		void shuffled() {
			return;
		}
};

class Counting: public Simple{
//Overview: A subclass of simple that keeps track of a card counting playing strategy
private:
	int count;
	
//implementation of counting player
public:
	Counting() {
		count = 0;
	}

	int bet(unsigned int bankroll, unsigned int minimum){
		if(count >= 2){
				if(bankroll >= 2*minimum){
				return 2*minimum;
			}
			else{
				return bankroll;
			}
		}
		else{
			return minimum;
		}
	}

	void expose(Card c){
		int i = 0;
		int Rank_Counts[13] = {1,1,1,1,1,0,0,0,-1,-1,-1,-1,-1};

		while(c.get_rank() != static_cast<Card::Rank>(i)){
			++i;
		}

		count = count + Rank_Counts[i];

		return;
	}

	void shuffled(){
		count = 0;
		return;
	}
};

class Competitor: public Counting{
//Overview: a subclass of Counting that implements a more advanced counting technique
private:
	int count_competitor;

//implementation of competing player
public:
	Competitor() {
		count_competitor = 0;
	}

	int bet(unsigned int bankroll, unsigned int minimum){
		if(count_competitor >= 4){
			if(bankroll >= 3*minimum){
				return 3*minimum;
			}
			else{
				return bankroll;
			}
		}

		else if(count_competitor >= 1){
			if(bankroll >= 2*minimum){
				return 2*minimum;
			}
			else{
				return bankroll;
			}
		}
		else{
			return minimum;
		}
	}
};

static Simple Simple_player;
static Counting Counting_player;
static Competitor Competing_player;

Player * player_factory(const char * s){
	if(strcmp(s, "simple") == 0){
		return &Simple_player;
	}
	else if(strcmp(s, "counting") == 0){
		return &Counting_player;
	}

	//else if(strcmp(s, "competitor")){
	return &Competing_player;
	//}
}