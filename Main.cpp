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

int main() {
	PokerGame game;
	game.playGame();
}