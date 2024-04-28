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
		// use different method to compare the hands based on the rank
		if (rank == PokerRanks::FOUR_OF_A_KIND) {
			return sameRankFourOfAKind(hand2);
		}
		else if (rank == PokerRanks::FULL_HOUSE) {
			return sameRankFullHouse(hand2);
		}
		else if (rank == PokerRanks::THREE_OF_A_KIND) {
			return sameRankTreeOfAKind(hand2);
		}
		else if (rank == PokerRanks::TWO_PAIR) {
			return sameRankTwoPair(hand2);
		}
		else if (rank == PokerRanks::PAIR) {
			return sameRankPair(hand2);
		}
		// all other ranks covered by this
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

	int sameRankFourOfAKind(PokerHand hand2) {
		// Find the value of the four of a kind.
		int quadCardValue1 = 0;
		int quadCardValue2 = 0;

		int singleCardValue1 = 0;
		int singleCardValue2 = 0;

		for (int i = 0; i < 2; i++) {
			if (hand[i].getValue() == hand[i + 1].getValue() && hand[i + 1].getValue() == hand[i + 2].getValue() && hand[i + 2].getValue() == hand[i + 3].getValue()) {
				quadCardValue1 = hand[i].getValue();
			}
			else if (i == 0 && quadCardValue1 == 0)
			{
				singleCardValue1 = hand[i].getValue();
			}
			else {
				singleCardValue1 = hand[4].getValue();
			}

			if (hand2.hand[i].getValue() == hand2.hand[i + 1].getValue() && hand2.hand[i + 1].getValue() == hand2.hand[i + 2].getValue() && hand2.hand[i + 2].getValue() == hand2.hand[i + 3].getValue()) {
				quadCardValue2 = hand2.hand[i].getValue();
			}
			else if (i == 0 && quadCardValue2 == 0)
			{
				singleCardValue2 = hand2.hand[i].getValue();
			}
			else {
				singleCardValue2 = hand2.hand[4].getValue();
			}
		}

		// Compare the value of the four of a kind.
		if (quadCardValue1 > quadCardValue2) {
			return 1;
		}
		else if (quadCardValue1 < quadCardValue2) {
			return 2;
		}
		else {
			// Compare the value of the remaining card.
			if (singleCardValue1 > singleCardValue2) {
				return 1;
			}
			else if (singleCardValue1 < singleCardValue2) {
				return 2;
			}
			else {
				return 0;
			}
		}
	}

	int sameRankFullHouse(PokerHand hand2) {
		int tripleCardValue1 = 0;
		int tripleCardValue2 = 0;

		int doubleCardValue1 = 0;
		int doubleCardValue2 = 0;

		// Find the value of the triple card.
		for (int i = 0; i < 3; i++) {
			if (hand[i].getValue() == hand[i + 1].getValue() && hand[i + 1].getValue() == hand[i + 2].getValue()) {
				tripleCardValue1 = hand[i].getValue();
			}

			if (hand2.hand[i].getValue() == hand2.hand[i + 1].getValue() && hand2.hand[i + 1].getValue() == hand2.hand[i + 2].getValue()) {
				tripleCardValue2 = hand2.hand[i].getValue();
			}
		}

		// Find the value of the pair.
		for (int i = 0; i < 5; i++) {
			if (hand[i].getValue() != tripleCardValue1) {
				doubleCardValue1 = hand[i].getValue();
			}
			if (hand2.hand[i].getValue() != tripleCardValue2) {
				doubleCardValue2 = hand2.hand[i].getValue();
			}
		}

		// Compare the value of the three of a kind.
		if (tripleCardValue1 > tripleCardValue2) {
			return 1;
		}
		else if (tripleCardValue1 < tripleCardValue2) {
			return 2;
		}
		else {
			// Compare the value of the pair.
			if (doubleCardValue1 > doubleCardValue2) {
				return 1;
			}
			else if (doubleCardValue1 < doubleCardValue2) {
				return 2;
			}
			else {
				return 0;
			}
		}
	}

	int sameRankTreeOfAKind(PokerHand hand2) {
		int tripleCardValue1 = 0;
		int tripleCardValue2 = 0;

		int singleCardValues1[] = { 0, 0 };
		int singleCardValues2[] = { 0, 0 };

		// Find the value of the triple card.
		for (int i = 0; i < 3; i++) {
			if (hand[i].getValue() == hand[i + 1].getValue() && hand[i + 1].getValue() == hand[i + 2].getValue()) {
				tripleCardValue1 = hand[i].getValue();
			}
			else if (i == 0) {
				singleCardValues1[0] = hand[0].getValue();
				singleCardValues1[1] = hand[1].getValue();
			}
			else if (i == 2) {
				singleCardValues1[0] = hand[3].getValue();
				singleCardValues1[1] = hand[4].getValue();
			}

			if (hand2.hand[i].getValue() == hand2.hand[i + 1].getValue() && hand2.hand[i + 1].getValue() == hand2.hand[i + 2].getValue()) {
				tripleCardValue2 = hand2.hand[i].getValue();
			}
			else if (i == 0) {
				singleCardValues2[0] = hand2.hand[0].getValue();
				singleCardValues2[1] = hand2.hand[1].getValue();
			}
			else if (i == 2) {
				singleCardValues2[0] = hand2.hand[3].getValue();
				singleCardValues2[1] = hand2.hand[4].getValue();
			}
		}

		// sort the array of single card values
		std::sort(singleCardValues1, singleCardValues1 + 2);
		std::sort(singleCardValues2, singleCardValues2 + 2);

		// Compare the value of the three of a kind.
		if (tripleCardValue1 > tripleCardValue2) {
			return 1;
		}
		else if (tripleCardValue1 < tripleCardValue2) {
			return 2;
		}

		for (int i = 1; i >= 0; i--) {
			if (singleCardValues1[i] > singleCardValues2[i]) {
				return 1;
			}
			else if (singleCardValues1[i] < singleCardValues2[i]) {
				return 2;
			}
		}
		return 0;
	}

	int sameRankTwoPair(PokerHand hand2) {
		int pairCardValues1[] = { 0, 0 };
		int pairCardValues2[] = { 0, 0 };

		int singleCardValue1 = 0;
		int singleCardValue2 = 0;

		// Find the value of the pairs.
		int pairCount1 = 0;
		int pairCount2 = 0;
		for (int i = 0; i < 4; i++) {
			if (hand[i].getValue() == hand[i + 1].getValue()) {
				pairCardValues1[pairCount1++] = hand[i].getValue();
			}

			if (hand2.hand[i].getValue() == hand2.hand[i + 1].getValue()) {
				pairCardValues2[pairCount2++] = hand2.hand[i].getValue();
			}
		}

		// Find the value of the single card.
		for (int i = 0; i < 5; i++) {
			if (hand[i].getValue() != pairCardValues1[0] && hand[i].getValue() != pairCardValues1[1]) {
				singleCardValue1 = hand[i].getValue();
			}
			if (hand2.hand[i].getValue() != pairCardValues2[0] && hand2.hand[i].getValue() != pairCardValues2[1]) {
				singleCardValue2 = hand2.hand[i].getValue();
			}
		}

		// sort the array of pair card values
		std::sort(pairCardValues1, pairCardValues1 + 2);
		std::sort(pairCardValues2, pairCardValues2 + 2);

		// Compare the value of the pairs.
		for (int i = 1; i >= 0; i--) {
			if (pairCardValues1[i] > pairCardValues2[i]) {
				return 1;
			}
			else if (pairCardValues1[i] < pairCardValues2[i]) {
				return 2;
			}
		}

		// Compare the value of the single card.
		if (singleCardValue1 > singleCardValue2) {
			return 1;
		}
		else if (singleCardValue1 < singleCardValue2) {
			return 2;
		}
		else {
			return 0;
		}
	}

	int sameRankPair(PokerHand hand2) {
		int pairCardValue1 = 0;
		int pairCardValue2 = 0;

		int singleCardValues1[] = { 0, 0, 0 };
		int singleCardValues2[] = { 0, 0, 0 };

		// Find the value of the pair.
		for (int i = 0; i < 4; i++) {
			if (hand[i].getValue() == hand[i + 1].getValue()) {
				pairCardValue1 = hand[i].getValue();
			}
			else if (i == 0) {
				singleCardValues1[0] = hand[0].getValue();
				singleCardValues1[1] = hand[1].getValue();
				singleCardValues1[2] = hand[2].getValue();
			}
			else if (i == 3) {
				singleCardValues1[0] = hand[2].getValue();
				singleCardValues1[1] = hand[3].getValue();
				singleCardValues1[2] = hand[4].getValue();
			}

			if (hand2.hand[i].getValue() == hand2.hand[i + 1].getValue()) {
				pairCardValue2 = hand2.hand[i].getValue();
			}
			else if (i == 0) {
				singleCardValues2[0] = hand2.hand[0].getValue();
				singleCardValues2[1] = hand2.hand[1].getValue();
				singleCardValues2[2] = hand2.hand[2].getValue();
			}
			else if (i == 3) {
				singleCardValues2[0] = hand2.hand[2].getValue();
				singleCardValues2[1] = hand2.hand[3].getValue();
				singleCardValues2[2] = hand2.hand[4].getValue();
			}
		}

		// sort the array of single card values
		std::sort(singleCardValues1, singleCardValues1 + 3);
		std::sort(singleCardValues2, singleCardValues2 + 3);

		// Compare the value of the pair.
		if (pairCardValue1 > pairCardValue2) {
			return 1;
		}
		else if (pairCardValue1 < pairCardValue2) {
			return 2;
		}

		for (int i = 2; i >= 0; i--) {
			if (singleCardValues1[i] > singleCardValues2[i]) {
				return 1;
			}
			else if (singleCardValues1[i] < singleCardValues2[i]) {
				return 2;
			}
		}
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
