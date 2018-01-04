#include<stdio.h>;
#include<string.h>;

// function declarations
const char * getCardName(struct Card card);
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

// Converts a card value and suit to it's full name
// e.g. 11, 3 -> Jack of Spades
const char * getCardName(struct Card card) {
	char *cardName = (char*)malloc(18 * sizeof(char));
	sprintf(cardName, "%s of %s", FACE_NAMES[card.value], SUIT_NAMES[card.suit]);
	return cardName;
}

void main() {
	// variables
	int numPlayers;
	int roundNum;
	int playerTurn;
	int chosenCard;
	//The cards chosen by the players to be played for a round.
	struct Card chosenCards[10];
	int i, j;
	// The array of players. Only indexes up to (numPlayers - 1 ) to be used.
	struct Player players[10];
	int cardNum;
	int numPlayersWithCard;
	int cardValue;
	int highestCard;
	int roundWinner;
	int roundWinnings;
	// points carried over to the next round (because of a tie)
	int carryPoints = 0;

	printf("\nWar - By Ronan Hanley\n\n");
	printf("Enter number of players playing (2-10): ");
	scanf("%d", &numPlayers);
	printf("\n");

	initPlayers(players, numPlayers);

	for (roundNum = 1; roundNum <= 13; ++roundNum) {
		printf("-- Round %d --\n\n", roundNum);

		for (playerTurn = 0; playerTurn < numPlayers; ++playerTurn) {
			printf("Player %d, it's your turn to choose a card.\n\n", (playerTurn + 1));
			displayPlayerDeck(players[playerTurn], playerTurn);

			printf("Pick a card to play. Enter it's index (from above): ");
			scanf("%d", &chosenCard);

			// print many newlines to hide the cards of this player from the other players
			for (i = 0; i < 50; ++i) printf("\n");

			// add the player's card to the competing cards for this round
			chosenCards[playerTurn] = players[playerTurn].deck[chosenCard];

			// remove that card from the player's hand
			players[playerTurn].deck[chosenCard].suit = -1;
			players[playerTurn].deck[chosenCard].value = -1;
		}

		// show the cards the players chose
		printf("\n");
		for (i = 0; i < numPlayers; ++i) {
			printf("Player %d chose %s.\n", (i + 1), getCardName(chosenCards[i]));
		}
		printf("\n");

		// find the player with the highest unique card
		roundWinner = -1;
		highestCard = -1;
		for (i = 14; i >= 0; i--) {
			numPlayersWithCard = 0;

			for (int j = 0; j < numPlayers; ++j) {
				int cardValue = chosenCards[j].value;

				if (cardValue == i) {
					++numPlayersWithCard;
					highestCard = cardValue;

					if (numPlayersWithCard > 1) {
						// skip to the next lowest card
						break;
					}
				}
			}

			if (numPlayersWithCard == 1) {
				roundWinner = i;
				break;
			}
		}

		// calculate the winnings for this round
		roundWinnings = 0;
		for (i = 0; i < numPlayers; ++i) {
			roundWinnings += chosenCards[i].value;
		}

		if (roundWinner == -1) {
			// tie
			printf("It's a tie! No winners this round.\n");

			if (carryPoints == -1) {
				printf("This round's winnings of %d points will be carried over to the next round.\n", roundWinnings);
			}
			else {
				printf("This is the second tie in a row!\n");
				printf("%d points from last round plus %d points from this round (a total of %d points are lost on the battlefield!\n",
					roundWinnings, carryPoints, (roundWinnings + carryPoints));
				carryPoints = 0;
			}
		}
		else {
			// winner found
			printf("Player %d wins the round!\n", (roundWinner + 1));
			printf("Card value won with: %d\n", highestCard);
			printf("Points awarded (all chosen card values added together): %d", roundWinnings);

			if (carryPoints != 0) {
				printf(" + %d points carried over from the last round.", carryPoints);
			}

			printf("\n\n");

			printf("Press enter to continue to the next round.");
			getch();
			printf("\n");
		}

		printf("\n");
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
		if (player.deck[i].value == -1) {
			printf("<card already used>\n");
		}
		else {
			printf("- Card [%d]: %s\n", (i + 1), getCardName(player.deck[i]));
		}
	}

	printf("\n");
}
