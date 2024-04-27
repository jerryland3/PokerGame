#pragma once
#include "card.h"
#include <string>
#include <array>
#include <cstdlib>
#include <ctime>

class DeckDealer {
public:
	static const int DECK_SIZE = 52;
	static const int faces = 13;
	static const int suits = 4;

	DeckDealer() : topCardIndex{ 0 } {
		static char suit[suits] = { 'S', 'H', 'D', 'C' };
		static char face[faces] = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };

		// set the deck
		for (int i = 0; i < DECK_SIZE; i++) {
			deck[i].setSuit(suit[i / faces]);
			deck[i].setValue(face[i % faces]);
		}

		srand(static_cast<size_t>(time(nullptr)));
		shuffle();
	}

	void shuffle() {
		for (int i = 0; i < DECK_SIZE; i++) {
			int j = rand() % DECK_SIZE;
			Card temp = deck[i];
			deck[i] = deck[j];
			deck[j] = temp;
		}
	}

	Card dealCard() {
		return deck[topCardIndex++];
	}

	std::array<Card, 5> dealHand() {
		std::array<Card, 5> hand;
		for (int i = 0; i < 5; i++) {
			hand[i] = dealCard();
		}
		return hand;
	}

	void resetDeck() {
		topCardIndex = 0;
		shuffle();
	}

	int cardsLeft() {
		return DECK_SIZE - topCardIndex;
	}

	void printDeck() {
		for (int i = 0; i < DECK_SIZE; i++) {
			deck.at(i).printCard();
			std::cout << "\n";
		}
	}
private:
	std::array<Card, 52> deck;
	int topCardIndex;
};
