#include<stdio.h>;
#include<string.h>;

// function declarations
void initPlayers(struct Player players[], int numPlayers);
void displayPlayerDeck(struct Player player, int playerNum);

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


// used to translate card indexes to the face of the card easily
const char *  FACE_NAMES[] = {
	// note cards 0 and 1 do not exist
	"",
	"",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"10",
	"Jack",
	"Queen",
	"King",
	"Ace"
};

// used to translate suit numberes to names easily
const char * SUIT_NAMES[] = {
	"Clubs",
	"Diamonds",
	"Hearts",
	"Spades"
};

void main() {
	// variables
	int numPlayers;
	int roundNum;
	int playerTurn;
	int cardChoice;
	//The cards chosen by the players to be played for a round.
	struct Card chosenCards[10];
	int i;
	// The array of players. Only indexes up to (numPlayers - 1 ) to be used.
	struct Player players[10];

	printf("\nWar - By Ronan Hanley\n\n");
	printf("Enter number of players playing (2-10): ");
	scanf("%d", &numPlayers);
	printf("\n");

	initPlayers(players, numPlayers);

	for (roundNum = 1; roundNum <= 13; ++roundNum) {
		printf("-- Round %d --\n\n", roundNum);

		for (playerTurn = 0; playerTurn < numPlayers; ++playerTurn) {
			printf("Player %d's turn to choose a card.\n\n");
			displayPlayerDeck(players[playerTurn], playerTurn);

			printf("Pick a card to play. Enter it's index (from above): ");
			scanf("%d", &cardChoice);

			// print many newlines to hide the cards of this player from the other players
			for (i = 0; i < 0; ++i) printf("\n");

			
		}
	}
}

void initPlayers(struct Player players[], int numPlayers) {
	int i, j;

	for (i = 0; i < numPlayers; ++i) {
		// initialize the cards (2 -> 13)
		for (j = 0; j < 13; ++j) {
			players[i].deck[j].value = j + 2;

			// initialize the suit
			// no random suit for now; to be updated later
			players[i].deck[j].suit = 0;
		}
	}
}

void displayPlayerDeck(struct Player player, int playerNum) {
	int i;

	printf("Your cards, player %d:\n", playerNum + 1);
	for (i = 0; i < 13; ++i) {
		printf("- Card [%d]: %s of %s\n", (i + 1), FACE_NAMES[player.deck[i].value], SUIT_NAMES[player.deck[i].suit]);
	}

	printf("\n");
}
