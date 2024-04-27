/**
 * @class Card
 * @brief Defines the Card class for representing a playing card.
 *
 * This file contains the definition of the Card class, which represents a playing card.
 * Each card has a suit and a value, which are represented by a character and an integer, respectively.
 * The class provides functionality to create a card from a string, get the suit and value of a card,
 * and compare cards for sorting purposes.
 *
 * @date 2/18/2024
 * @version New
 * @author Jerry Wang
 */

#pragma once

#include <string>
#include <stdexcept>
#include <iostream>

class Card {
public:

	Card() = default;

	Card(char suit, char value) {
		setSuit(suit);
		setValue(value);
	}

	/**
	 * @brief Returns the suit of the card.
	 *
	 * Returns the suit character of the card ('S' for spades, 'H' for hearts,
	 * 'D' for diamonds, 'C' for clubs).
	 *
	 * @return The suit of the card.
	 */
	char getSuit() const {
		return suit;
	}

	/**
	 * @brief Returns the value of the card.
	 *
	 * Returns the value of the card as an integer.
	 * For numeric cards, the value is the numeric value itself.
	 * For face cards, the value is as follows: Jack - 11, Queen - 12, King - 13, Ace - 14.
	 *
	 * @return The value of the card.
	 */
	int getValue() const {
		return value;
	}

	void setSuit(char suit) {
		// check the suit of the card
		if (suit != 'S' && suit != 'H' && suit != 'D' && suit != 'C') {
			throw std::invalid_argument("Invalid card suit");
		}
		this->suit = suit;
	}

	void setValue(char value) {
		// check the value of the card
		if (value != 'A' && value != 'K' && value != 'Q' && value != 'J' && value != 'T' && (value < '2' || value > '9')) {
			throw std::invalid_argument("Invalid card value");
		}

		if (value == 'A') {
			this->value = 14;
		}
		else if (value == 'K') {
			this->value = 13;
		}
		else if (value == 'Q') {
			this->value = 12;
		}
		else if (value == 'J') {
			this->value = 11;
		}
		else if (value == 'T') {
			this->value = 10;
		}
		else {
			this->value = value - '0';
		}
	}

	/**
	 * @brief Comparison function for sorting cards.
	 *
	 * This static method is used for comparing two cards for sorting purposes.
	 * It compares the values of two cards.
	 *
	 * @param a The first card to compare.
	 * @param b The second card to compare.
	 * @return true if the value of card a is less than the value of card b, false otherwise.
	 */
	static bool compareCards(const Card& a, const Card& b) {
		return a.value < b.value;
	}

	void printCard() {
		std::string valueStr;
		std::string suitStr;

		if (value == 14) {
			valueStr = "Ace";
		}
		else if (value == 13) {
			valueStr = "King";
		}
		else if (value == 12) {
			valueStr = "Queen";
		}
		else if (value == 11) {
			valueStr = "Jack";
		}
		else if (value == 10) {
			valueStr = "10";
		}
		else {
			valueStr = std::to_string(value);
		}

		switch (suit) {
		case 'S':
			suitStr = "Spades";
			break;
		case 'H':
			suitStr = "Hearts";
			break;
		case 'D':
			suitStr = "Diamonds";
			break;
		case 'C':
			suitStr = "Clubs";
			break;
		}

		std::cout << valueStr << " of " << suitStr << " " << std::endl;
	}

private:
	char suit{ '\0' }; /**< The suit of the card. */
	int value{ -1 };   /**< The value of the card. */
};
