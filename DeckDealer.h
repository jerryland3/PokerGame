#pragma once
#include "card.h"
#include "Player.h"
#include <string>
#include <array>
#include <cstdlib>
#include <ctime>
#include <vector>

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

	void dealHands(std::vector<Player>& players) {
		for (Player& player : players) {
			std::array<Card, 5> hand;
			for (int i = 0; i < 5; i++) {
				hand[i] = dealCard();
			}
			player.setHand(hand);
		}
	}

	void replaceCards(Player* player, int playerCount) {
		// print player's hand
		std::cout << "\n" << player->getName() << ", Your hand is:" << std::endl;
		player->getHand().printHand();

		// ask player if they would like to replace any cards
		std::cout << "\nWould you like to replace any cards? (y/n): ";
		char choice;
		std::cin >> choice;
		// make sure choice is valid
		while (choice != 'y' && choice != 'n') {
			std::cout << "Invalid choice. Please enter y or n: ";
			std::cin >> choice;
		}
		std::cin.ignore();
		// if player wants to replace cards
		if (choice == 'y') {
			// determin how many cards can the player replace
			int maxReplace = cardsLeft() / playerCount;

			maxReplace = maxReplace > 3 ? 3 : maxReplace;

			// let the player know how many cards they can replace
			std::cout << "You can replace up to " << maxReplace << " cards." << std::endl;
			// ask player which cards they would like to replace
			std::cout << "Enter the index of the cards you would like to replace (0-4). Seperate them by space, i.e. (0 3 5): ";

			std::string indexes;
			std::getline(std::cin, indexes);

			// make sure index is valid
			while (!validReplacementIndex(indexes, maxReplace)) {
				std::cout << "Invalid index. Please enter the index of the cards you would like to replace (0-4). Seperate them by space, i.e. (0 3 5): ";
				std::getline(std::cin, indexes);
			}
			// replace the cards
			for (int i = 0; i < indexes.length(); i++) {
				if (indexes[i] != ' ') {
					int cardIndex = indexes[i] - '0';
					player->replaceCard(cardIndex, dealCard());
				}
			}

			// print player's new hand
			std::cout << "\nYour new hand is:" << std::endl;
			player->getHand().printHand();
		}
	}

	void resetDeck() {
		topCardIndex = 0;
		shuffle();
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

	bool validReplacementIndex(std::string indexes, int maxReplace) {
		// check if index is empty
		if (indexes.empty()) {
			return false;
		}
		// check if index is in the correct range
		for (int i = 0; i < indexes.length(); i++) {
			if (indexes[i] != ' ' && (indexes[i] < '0' || indexes[i] > '4')) {
				return false;
			}
		}
		// check if index is within the maxReplace
		int count = 0;
		for (int i = 0; i < indexes.length(); i++) {
			if (indexes[i] != ' ') {
				count++;
			}
		}
		return count <= maxReplace;
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

	int cardsLeft() {
		return DECK_SIZE - topCardIndex;
	}
};
