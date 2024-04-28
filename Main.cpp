/**
 * @file PokerTest.cpp
 * @brief Contains the main() function for testing the poker hand class.
 *
 * This file defines the main() function which tests the poker hand class.
 *
 * @date 2/5/2024
 * @version New
 * @author Jerry Wang
 */
#pragma once
#include <iostream>
#include "PokerHand.h"
#include "PokerRanks.h"
#include "DeckDealer.h"
#include "PokerGame.h"

using namespace std;
void testPokerHand();

int main() {
	// ask the user to play a game or test the poker hand
	cout << "Would you like to play a game or test the poker hand? (game/test)" << endl;
	string input;
	cin >> input;
	if (input == "game") {
		PokerGame game;
		game.playGame();
	}
	else if (input == "test") {
		testPokerHand();
	}
	else {
		cout << "Invalid input. Please enter 'game' or 'test'." << endl;
	}
}

void testPokerHand() {
	// test the poker hand class
	PokerHand hand1;
	PokerHand hand2;

	cout << "Royal Flush Test" << endl;
	// Royal Flush
	hand1.setHand({ Card('S', 'A'), Card('S', 'K'), Card('S', 'Q'), Card('S', 'J'), Card('S', 'T') });
	hand2.setHand({ Card('H', '8'), Card('H', '7'), Card('H', '6'), Card('H', '5'), Card('H', '4') });
	std::cout << "AS KS QS JS TS vs. 8H 7H 6H 5H 4H: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	cout << "\nStraight Flush Test" << endl;
	// Straight Flush
	hand1.setHand({ Card('C', 'T'), Card('C', '9'), Card('C', '8'), Card('C', '7'), Card('C', '6') });
	hand2.setHand({ Card('H', '8'), Card('H', '7'), Card('H', '6'), Card('H', '5'), Card('H', '4') });
	std::cout << "TC 9C 8C 7C 6C vs. 8H 7H 6H 5H 4H: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('H', '8'), Card('H', '7'), Card('H', '6'), Card('H', '5'), Card('H', '4') });
	hand2.setHand({ Card('S', '6'), Card('S', '5'), Card('S', '4'), Card('S', '3'), Card('S', '2') });
	std::cout << "8H 7H 6H 5H 4H vs. 6S 5S 4S 3S 2S: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('D', '7'), Card('D', '6'), Card('D', '5'), Card('D', '4'), Card('D', '3') });
	hand2.setHand({ Card('S', '7'), Card('S', '6'), Card('S', '5'), Card('S', '4'), Card('S', '3') });
	std::cout << "7D 6D 5D 4D 3D vs. 7S 6S 5S 4S 3S: " << (hand1.compareHand(hand2) == 0 ? "Pass" : "Fail") << std::endl;

	cout << "\nFour of a Kind Test" << endl;
	// Four of a Kind
	hand1.setHand({ Card('S', 'K'), Card('H', 'K'), Card('C', 'K'), Card('D', 'K'), Card('H', '3') });
	hand2.setHand({ Card('H', '7'), Card('D', '7'), Card('S', '7'), Card('C', '7'), Card('H', 'Q') });
	std::cout << "KS KH KC KD 3H vs. 7H 7D 7S 7C QH: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('H', '7'), Card('D', '7'), Card('S', '7'), Card('C', '7'), Card('H', 'Q') });
	hand2.setHand({ Card('H', '7'), Card('D', '7'), Card('S', '7'), Card('C', '7'), Card('S', 'T') });
	std::cout << "7H 7D 7S 7C QH vs. 7H 7D 7S 7C TS: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('C', '4'), Card('S', '4'), Card('D', '4'), Card('H', '4'), Card('C', '9') });
	hand2.setHand({ Card('C', '4'), Card('S', '4'), Card('D', '4'), Card('H', '4'), Card('D', '9') });
	std::cout << "4C 4S 4D 4H 9C vs. 4C 4S 4D 4H 9D: " << (hand1.compareHand(hand2) == 0 ? "Pass" : "Fail") << std::endl;

	cout << "\nFull House Test" << endl;
	// Full House
	hand1.setHand({ Card('S', '8'), Card('D', '8'), Card('H', '8'), Card('D', '7'), Card('C', '7') });
	hand2.setHand({ Card('D', '4'), Card('S', '4'), Card('C', '4'), Card('D', '9'), Card('C', '9') });
	std::cout << "8S 8D 8H 7D 7C vs. 4D 4S 4C 9D 9C: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('D', '4'), Card('S', '4'), Card('C', '4'), Card('D', '9'), Card('C', '9') });
	hand2.setHand({ Card('D', '4'), Card('S', '4'), Card('C', '4'), Card('C', '5'), Card('D', '5') });
	std::cout << "4D 4S 4C 9D 9C vs. 4D 4S 4C 5C 5D: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('C', 'K'), Card('S', 'K'), Card('D', 'K'), Card('C', 'J'), Card('S', 'J') });
	hand2.setHand({ Card('C', 'K'), Card('H', 'K'), Card('D', 'K'), Card('C', 'J'), Card('H', 'J') });
	std::cout << "KC KS KD JC JS vs. KC KH KD JC JH: " << (hand1.compareHand(hand2) == 0 ? "Pass" : "Fail") << std::endl;

	cout << "\nFlush Test" << endl;
	// Flush
	hand1.setHand({ Card('D', 'K'), Card('D', 'J'), Card('D', '9'), Card('D', '6'), Card('D', '4') });
	hand2.setHand({ Card('C', 'Q'), Card('C', 'J'), Card('C', '7'), Card('C', '6'), Card('C', '5') });
	std::cout << "KD JD 9D 6D 4D vs. QC JC 7C 6C 5C: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('C', 'Q'), Card('C', 'J'), Card('C', '7'), Card('C', '6'), Card('C', '5') });
	hand2.setHand({ Card('H', 'J'), Card('H', 'T'), Card('H', '9'), Card('H', '4'), Card('H', '2') });
	std::cout << "QC JC 7C 6C 5C vs. JH TH 9H 4H 2H: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('H', 'J'), Card('H', 'T'), Card('H', '9'), Card('H', '4'), Card('H', '2') });
	hand2.setHand({ Card('S', 'J'), Card('S', 'T'), Card('S', '8'), Card('S', '6'), Card('S', '3') });
	std::cout << "JH TH 9H 4H 2H vs. JS TS 8S 6S 3S: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('S', 'J'), Card('S', 'T'), Card('S', '8'), Card('S', '6'), Card('S', '3') });
	hand2.setHand({ Card('H', 'J'), Card('H', 'T'), Card('H', '8'), Card('H', '4'), Card('H', '3') });
	std::cout << "JS TS 8S 6S 3S vs. JH TH 8H 4H 3H: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('H', 'J'), Card('H', 'T'), Card('H', '8'), Card('H', '4'), Card('H', '3') });
	hand2.setHand({ Card('C', 'J'), Card('C', 'T'), Card('C', '8'), Card('C', '4'), Card('C', '2') });
	std::cout << "JH TH 8H 4H 3H vs. JC TC 8C 4C 2C: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('D', 'T'), Card('D', '8'), Card('D', '7'), Card('D', '6'), Card('D', '5') });
	hand2.setHand({ Card('S', 'T'), Card('S', '8'), Card('S', '7'), Card('S', '6'), Card('S', '5') });
	std::cout << "TD 8D 7D 6D 5D vs. TS 8S 7S 6S 5S: " << (hand1.compareHand(hand2) == 0 ? "Pass" : "Fail") << std::endl;

	cout << "\nStraight Test" << endl;
	// Straight
	hand1.setHand({ Card('H', 'J'), Card('H', 'T'), Card('C', '9'), Card('S', '8'), Card('H', '7') });
	hand2.setHand({ Card('S', 'T'), Card('S', '9'), Card('C', '8'), Card('H', '7'), Card('S', '6') });
	std::cout << "JH TH 9C 8S 7H vs. TS 9S 8C 7H 6S: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('S', 'T'), Card('S', '9'), Card('C', '8'), Card('H', '7'), Card('S', '6') });
	hand2.setHand({ Card('C', '6'), Card('S', '5'), Card('H', '4'), Card('S', '3'), Card('D', '2') });
	std::cout << "TS 9S 8C 7H 6S vs. 6C 5S 4H 3S 2D: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('C', '9'), Card('C', '8'), Card('C', '7'), Card('D', '6'), Card('D', '5') });
	hand2.setHand({ Card('S', '9'), Card('S', '8'), Card('S', '7'), Card('H', '6'), Card('H', '5') });
	std::cout << "9C 8C 7C 6D 5D vs. 9S 8S 7S 6H 5H: " << (hand1.compareHand(hand2) == 0 ? "Pass" : "Fail") << std::endl;

	cout << "\nThree of a Kind Test" << endl;
	// Three of a Kind
	hand1.setHand({ Card('H', '6'), Card('D', '6'), Card('S', '6'), Card('C', 'Q'), Card('S', '4') });
	hand2.setHand({ Card('D', '3'), Card('S', '3'), Card('C', '3'), Card('S', 'K'), Card('S', '2') });
	std::cout << "6H 6D 6S QC 4S vs. 3D 3S 3C KS 2S: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('D', '3'), Card('S', '3'), Card('C', '3'), Card('S', 'K'), Card('S', '2') });
	hand2.setHand({ Card('D', '3'), Card('S', '3'), Card('C', '3'), Card('C', 'J'), Card('H', '7') });
	std::cout << "3D 3S 3C KS 2S vs. 3D 3S 3C JC 7H: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('D', '3'), Card('S', '3'), Card('C', '3'), Card('C', 'J'), Card('H', '7') });
	hand2.setHand({ Card('D', '3'), Card('S', '3'), Card('C', '3'), Card('S', 'J'), Card('D', '5') });
	std::cout << "3D 3S 3C JC 7H vs. 3D 3S 3C JS 5D: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('S', '9'), Card('H', '9'), Card('D', '9'), Card('D', 'T'), Card('H', '8') });
	hand2.setHand({ Card('C', '9'), Card('S', '9'), Card('H', '9'), Card('D', 'T'), Card('D', '8') });
	std::cout << "9S 9H 9D TD 8H vs. 9C 9S 9H TD 8D: " << (hand1.compareHand(hand2) == 0 ? "Pass" : "Fail") << std::endl;

	cout << "\nTwo Pair Test" << endl;
	// Two Pair
	hand1.setHand({ Card('D', 'T'), Card('S', 'T'), Card('S', '2'), Card('C', '2'), Card('C', 'K') });
	hand2.setHand({ Card('C', '5'), Card('S', '5'), Card('D', '4'), Card('H', '4'), Card('H', 'T') });
	std::cout << "TD TS 2S 2C KC vs. 5C 5S 4D 4H TH: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('C', '5'), Card('S', '5'), Card('D', '4'), Card('H', '4'), Card('H', 'T') });
	hand2.setHand({ Card('C', '5'), Card('S', '5'), Card('C', '3'), Card('D', '3'), Card('S', 'Q') });
	std::cout << "5C 5S 4D 4H TH vs. 5C 5S 3C 3D QS: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('C', '5'), Card('S', '5'), Card('C', '3'), Card('D', '3'), Card('S', 'Q') });
	hand2.setHand({ Card('C', '5'), Card('S', '5'), Card('C', '3'), Card('D', '3'), Card('S', 'J') });
	std::cout << "5C 5S 3C 3D QS vs. 5C 5S 3C 3D JS: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('D', 'K'), Card('S', 'K'), Card('D', '7'), Card('H', '7'), Card('H', '8') });
	hand2.setHand({ Card('C', 'K'), Card('S', 'K'), Card('C', '7'), Card('H', '7'), Card('C', '8') });
	std::cout << "KD KS 7D 7H 8H vs. KC KS 7C 7H 8C: " << (hand1.compareHand(hand2) == 0 ? "Pass" : "Fail") << std::endl;

	cout << "\nOne Pair Test" << endl;
	// One Pair
	hand1.setHand({ Card('C', '9'), Card('D', '9'), Card('S', 'Q'), Card('H', 'J'), Card('H', '5') });
	hand2.setHand({ Card('D', '6'), Card('H', '6'), Card('S', 'K'), Card('H', '7'), Card('C', '4') });
	std::cout << "9C 9D QS JH 5H vs. 6D 6H KS 7H 4C: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('D', '6'), Card('H', '6'), Card('S', 'K'), Card('H', '7'), Card('C', '4') });
	hand2.setHand({ Card('D', '6'), Card('H', '6'), Card('H', 'Q'), Card('S', 'J'), Card('C', '2') });
	std::cout << "6D 6H KS 7H 4C vs. 6D 6H QH JS 2C: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('D', '6'), Card('H', '6'), Card('S', 'K'), Card('H', '7'), Card('C', '4') });
	hand2.setHand({ Card('D', '6'), Card('H', '6'), Card('H', 'Q'), Card('S', 'J'), Card('C', '2') });
	std::cout << "6D 6H KS 7H 4C vs. 6D 6H QH JS 2C: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('D', '6'), Card('H', '6'), Card('H', 'Q'), Card('S', 'J'), Card('C', '2') });
	hand2.setHand({ Card('D', '6'), Card('H', '6'), Card('S', 'Q'), Card('C', '8'), Card('D', '7') });
	std::cout << "6D 6H QH JS 2C vs. 6D 6H QS 8C 7D: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('D', '6'), Card('H', '6'), Card('S', 'Q'), Card('C', '8'), Card('D', '7') });
	hand2.setHand({ Card('D', '6'), Card('H', '6'), Card('D', 'Q'), Card('H', '8'), Card('S', '3') });
	std::cout << "6D 6H QS 8C 7D vs. 6D 6H QD 8H 3S: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('S', '8'), Card('D', '8'), Card('H', 'T'), Card('C', '6'), Card('S', '5') });
	hand2.setHand({ Card('H', '8'), Card('C', '8'), Card('C', 'T'), Card('S', '6'), Card('C', '5') });
	std::cout << "8S 8D TH 6C 5S vs. 8H 8C TC 6S 5C: " << (hand1.compareHand(hand2) == 0 ? "Pass" : "Fail") << std::endl;

	cout << "\nHigh Card Test" << endl;
	// High Card
	hand1.setHand({ Card('S', 'K'), Card('C', '6'), Card('H', '5'), Card('D', '3'), Card('C', '2') });
	hand2.setHand({ Card('S', 'Q'), Card('D', 'J'), Card('C', '6'), Card('H', '5'), Card('C', '3') });
	std::cout << "KS 6C 5H 3D 2C vs. QS JD 6C 5H 3C: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('S', 'Q'), Card('D', 'J'), Card('C', '6'), Card('H', '5'), Card('C', '3') });
	hand2.setHand({ Card('S', 'Q'), Card('D', 'T'), Card('C', '8'), Card('D', '7'), Card('S', '4') });
	std::cout << "QS JD 6C 5H 3C vs. QS TD 8C 7D 4S: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('S', 'Q'), Card('D', 'T'), Card('C', '8'), Card('D', '7'), Card('S', '4') });
	hand2.setHand({ Card('H', 'Q'), Card('H', 'T'), Card('C', '7'), Card('H', '6'), Card('S', '4') });
	std::cout << "QS TD 8C 7D 4S vs. QH TH 7C 6H 4S: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('H', 'Q'), Card('H', 'T'), Card('C', '7'), Card('H', '6'), Card('S', '4') });
	hand2.setHand({ Card('C', 'Q'), Card('C', 'T'), Card('D', '7'), Card('C', '5'), Card('D', '4') });
	std::cout << "QH TH 7C 6H 4S vs. QC TC 7D 5C 4D: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('C', 'Q'), Card('C', 'T'), Card('D', '7'), Card('C', '5'), Card('D', '4') });
	hand2.setHand({ Card('H', 'Q'), Card('D', 'T'), Card('S', '7'), Card('S', '5'), Card('H', '2') });
	std::cout << "QC TC 7D 5C 4D vs. QH TD 7S 5S 2H: " << (hand1.compareHand(hand2) == 1 ? "Pass" : "Fail") << std::endl;

	hand1.setHand({ Card('C', 'T'), Card('S', '8'), Card('S', '7'), Card('H', '6'), Card('D', '4') });
	hand2.setHand({ Card('D', 'T'), Card('D', '8'), Card('S', '7'), Card('C', '6'), Card('C', '4') });
	std::cout << "TC 8S 7S 6H 4D vs. TD 8D 7S 6C 4C: " << (hand1.compareHand(hand2) == 0 ? "Pass" : "Fail") << std::endl;
}