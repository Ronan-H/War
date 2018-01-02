#include<stdio.h>;
#include<string.h>;

struct Card {
	/*
		Value: 2-10 -> 2-10 (face value)
		J, Q, K, A -> 11-14 respectively
	*/
	int value;
	/*
		Suit: Clubs, Diamonds, Hearts, Spades -> 0-3
		(actually has no significance in the game)
	*/
	int suit;
};

struct Player {
	struct Card deck[13];
	int numRoundsWon;
};

// used to translate suit numberes to names easily
const char *  SUIT_NAMES[] = {
	"Clubs",
	"Diamonds",
	"Hearts",
	"Spades"
};

void main() {
	// variables
	int numPlayers;
	int roundNum;

	

	printf("War - By Ronan Hanley\n\n");
	printf("How many players? (2-10):");
	scanf("%d", numPlayers);
}
