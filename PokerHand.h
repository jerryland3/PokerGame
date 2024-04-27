/**
 * @class PokerHand
 * @brief This class is used to represent a poker hand. It contains an array of 5 cards.
 *
 * This class is used to represent a poker hand. It contains an array of 5 cards.
 * It also contains methods to check for the rank of the hand, and to compare the
 * rank of the hand with another hand. It can also print the hand to the console.
 *
 * @date 2/18/2024
 * @version New
 * @author Jerry Wang
 */
#include "Card.h"
#include "PokerRankUtils.h"
#include <array>
#include <string>
#include <iostream>
#include <algorithm>
#pragma once

class PokerHand {
public:

	PokerHand() : rank{ PokerRanks::DEFAULT_RANK } {}

	PokerHand(std::array<Card, 5> hand) : hand{ hand }, rank{ PokerRanks::DEFAULT_RANK } {}

	/**
	* @brief Set the hand.
	*/
	void setHand(std::array<Card, 5> hand) {
		this->hand = hand;
	}

	/**
	 * @brief Prints the hand to the console.
	 */
	void printHand() {
		int i = 0;
		for (Card& card : hand) {
			std::cout << "[" << i++ << "] ";
			card.printCard();
		}
	}

	/**
	 * @brief Gets the rank of the poker hand.
	 *
	 * @return The rank of the poker hand.
	 */
	PokerRanks getRank() const {
		return rank;
	}

	void replaceCard(int index, Card card) {
		hand[index] = card;
	}

	/**
	 * @brief Prints the rank of the poker hand to the console.
	 */
	void printRank() {
		sortHand();
		determineRank();
		std::cout << "Rank: " << PokerRankUtils::rankToString(rank) << std::endl;
	}

	/**
	 * @brief Compares this poker hand with another poker hand.
	 *
	 * @param hand2 The other poker hand to compare with.
	 * @return A string indicating which hand is higher.
	 */
	int compareHand(PokerHand hand2) {
		// Sort the hands.
		sortHand();
		hand2.sortHand();
		// Determine the rank of the hands.
		determineRank();
		hand2.determineRank();

		// Return the result of the comparison.
		if (rank > hand2.rank) {
			//std::cout << "First hand is higher\n" << std::endl;
			return 1;
		}
		else if (rank < hand2.rank) {
			//std::cout << "Second hand is higher\n" << std::endl;
			return 2;
		}
		else {
			compareSameRank(hand2); // If the ranks are the same, compare the hands.
		}
	}

private:

	std::array<Card, 5> hand; /**< Array of 5 cards representing the poker hand. */
	PokerRanks rank{ PokerRanks::DEFAULT_RANK }; /**< The rank of the poker hand. */

	/**
	 * @brief Sorts the cards in the hand.
	 */
	void sortHand() {
		std::sort(hand.begin(), hand.end(), Card::compareCards);
	}

	/**
	 * @brief Compares the rank of this poker hand with another poker hand of the same rank.
	 *
	 * @param hand2 The other poker hand to compare with.
	 * @return A string indicating which hand is higher.
	 */
	int compareSameRank(PokerHand hand2) {
		// loop through the hand and compare the value of the cards
		for (int i = 4; i >= 0; i--) {
			if (hand[i].getValue() > hand2.hand[i].getValue()) {
				return 1;
			}
			else if (hand[i].getValue() < hand2.hand[i].getValue()) {
				return 2;
			}
		}
		// both hand have the same rank and the same value of cards
		return 0;
	}

	/**
	 * @brief Determines the rank of the poker hand.
	 */
	void determineRank() {
		if (isItStraightFlush()) {
			rank = PokerRanks::STRAIGHT_FLUSH;
		}
		else if (isItFourOfAKind()) {
			rank = PokerRanks::FOUR_OF_A_KIND;
		}
		else if (isItFullHouse()) {
			rank = PokerRanks::FULL_HOUSE;
		}
		else if (isItFlush()) {
			rank = PokerRanks::FLUSH;
		}
		else if (isItStraight()) {
			rank = PokerRanks::STRAIGHT;
		}
		else if (isItThreeOfAKind()) {
			rank = PokerRanks::THREE_OF_A_KIND;
		}
		else if (isItTwoPair()) {
			rank = PokerRanks::TWO_PAIR;
		}
		else if (isItPair()) {
			rank = PokerRanks::PAIR;
		}
		else {
			rank = PokerRanks::HIGH_CARD;
		}
	}

	/**
	 * @brief Checks if the hand contains a pair of cards with the same value.
	 *
	 * @return true if the hand contains a pair, false otherwise.
	 */
	bool isItPair() const {
		for (size_t i = 0; i < 4; i++) {
			if (hand[i].getValue() == hand[i + 1].getValue()) {
				return true;
			}
		}
		return false;
	}

	/**
	 * @brief Checks if the hand contains two pairs of cards with the same value.
	 *
	 * @return true if the hand contains two pairs, false otherwise.
	 */
	bool isItTwoPair() const {
		int pairCount = 0;
		for (size_t i = 0; i < 4; i++) {
			if (hand[i].getValue() == hand[i + 1].getValue()) {
				pairCount++;
				i++; // Skip the next card.
			}
		}

		if (pairCount == 2) {
			return true;
		}
		return false;
	}

	/**
	 * @brief Checks if the hand contains three cards with the same value.
	 *
	 * @return true if the hand contains three of a kind, false otherwise.
	 */
	bool isItThreeOfAKind() const {
		for (size_t i = 0; i < 3; i++) {
			if (hand[i].getValue() == hand[i + 1].getValue() && hand[i + 1].getValue() == hand[i + 2].getValue()) {
				return true;
			}
		}
		return false;
	}

	/**
	 * @brief Checks if the hand contains cards with consecutive values.
	 *
	 * @return true if the hand is a straight, false otherwise.
	 */
	bool isItStraight() const {
		for (size_t i = 0; i < 4; i++) {
			if (hand[i].getValue() != hand[i + 1].getValue() - 1) {
				return false;
			}
		}
		return true;
	}

	/**
	 * @brief Checks if the hand contains cards with the same suit.
	 *
	 * @return true if the hand is a flush, false otherwise.
	 */
	bool isItFlush() const {
		for (size_t i = 0; i < 4; i++) {
			if (hand[i].getSuit() != hand[i + 1].getSuit()) {
				return false;
			}
		}
		return true;
	}

	/**
	 * @brief Checks if the hand contains three of a kind and a pair.
	 *
	 * @return true if the hand is a full house, false otherwise.
	 */
	bool isItFullHouse() const {
		if (hand[0].getValue() == hand[1].getValue() && hand[1].getValue() == hand[2].getValue() && hand[3].getValue() == hand[4].getValue()) {
			return true;
		}
		if (hand[0].getValue() == hand[1].getValue() && hand[2].getValue() == hand[3].getValue() && hand[3].getValue() == hand[4].getValue()) {
			return true;
		}
		return false;
	}

	/**
	 * @brief Checks if the hand contains four cards with the same value.
	 *
	 * @return true if the hand is four of a kind, false otherwise.
	 */
	bool isItFourOfAKind() const {
		for (size_t i = 0; i < 2; i++) {
			if (hand[i].getValue() == hand[i + 1].getValue() && hand[i + 1].getValue() == hand[i + 2].getValue() && hand[i + 2].getValue() == hand[i + 3].getValue()) {
				return true;
			}
		}
		return false;
	}

	/**
	 * @brief Checks if the hand is both a straight and a flush.
	 *
	 * @return true if the hand is a straight flush, false otherwise.
	 */
	bool isItStraightFlush() const {
		return isItStraight() && isItFlush();
	}
};
