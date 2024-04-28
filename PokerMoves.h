#pragma once
#include "Player.h"
#include "Pot.h"
#include <iostream>
#include <limits>

class PokerMoves {
public:
	void makeBet(std::vector<Player>& players, Pot* pot, int playerIndex) {
		// ask player how much they want to bet
		std::cout << "How much would you like to bet? (max bet is " << pot->getMaxBet() << "): ";
		std::cout << "Your current chips: " << players.at(playerIndex).getChips() << std::endl;
		int bet;
		std::cin >> bet;

		// make sure bet is valid
		while (bet < 0 || bet > pot->getMaxBet() || bet > players.at(playerIndex).getChips()) {
			int canBet = players.at(playerIndex).getChips() > pot->getMaxBet() ? pot->getMaxBet() : players.at(playerIndex).getChips();
			std::cout << "Invalid bet. Please enter a bet between 0 and " << canBet << ": ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> bet;
		}

		// subtract bet from player's chips
		players.at(playerIndex).setChips(players.at(playerIndex).getChips() - bet);
		// add bet to pot
		pot->increasePot(bet);
		lastBet = bet;
		// set player 's bet amount
		players.at(playerIndex).setBetAmount(bet);

		// show the pot and player chips
		std::cout << "The pot is now: " << pot->getPotAmount() << std::endl;
		std::cout << "Your chips: " << players.at(playerIndex).getChips() << std::endl;

		betMade = true;

		// ask previous player if they want to call or fold
		if (playerIndex != 0) {
			askPreviousPlayerToCall(players, pot, playerIndex);
		}
	}

	void makeRaise(std::vector<Player>& players, Pot* pot, int playerIndex) {
		// ask player how much they want to raise
		std::cout << "How much would you like to raise? (max raise is " << pot->getMaxRaise() << "), last bet was " << lastBet;
		std::cout << "Your current chips: " << players.at(playerIndex).getChips() << std::endl;
		int raise;
		std::cin >> raise;

		// make sure raise is valid
		while (raise < 0 || raise > pot->getMaxRaise() || raise > players.at(playerIndex).getChips() || raise <= lastBet) {
			int canBet = players.at(playerIndex).getChips() > pot->getMaxRaise() ? pot->getMaxRaise() : players.at(playerIndex).getChips();
			std::cout << "Invalid raise. Please enter a raise between 0 and " << canBet << ": ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> raise;
		}
		// subtract raise from player's chips
		players.at(playerIndex).setChips(players.at(playerIndex).getChips() - raise);
		// add raise to pot
		pot->increasePot(raise);
		lastBet = raise;

		// set player 's bet amount
		players.at(playerIndex).setBetAmount(raise);

		// show the pot and player chips
		std::cout << "The pot is now: " << pot->getPotAmount() << std::endl;
		std::cout << "Your chips: " << players.at(playerIndex).getChips() << std::endl;

		// ask previous player if they want to call or fold
		askPreviousPlayerToCall(players, pot, playerIndex);
	}

	void makeCall(Player* player, Pot* pot) {
		// subtract the difference between the current bet and the player's current bet from the player's chips
		int newAmount = player->getChips() - (lastBet - player->getBetAmount());
		// check if player has enough chips to call
		if (newAmount < 0) {
			std::cout << "You do not have enough chips to call. You are all in." << std::endl;
			newAmount = 0;
			pot->increasePot(player->getChips());
		}
		else {
			pot->increasePot(lastBet - player->getBetAmount());
		}
		player->setChips(newAmount);

		// set player 's bet amount
		player->setBetAmount(lastBet);

		// show the pot and player chips
		std::cout << "The pot is now: " << pot->getPotAmount() << std::endl;
		std::cout << "Your chips: " << player->getChips() << std::endl;
	}

	void makeFold(Player* player) {
		player->fold();
	}

	void resetBet() {
		lastBet = 0;
		betMade = false;
	}

	void setBetMade(bool betMade) {
		this->betMade = betMade;
	}

	bool getBetMade() {
		return betMade;
	}

	int getLastBet() {
		return lastBet;
	}

private:
	int lastBet = 0;
	bool betMade = false;

	void askPreviousPlayerToCall(std::vector<Player>& players, Pot* pot, int playerIndex) {
		for (int i = 0; i < playerIndex; i++) {
			// if player has not folded
			bool folded = players.at(i).getFold();
			PlayerType type = players.at(i).getPlayerType();
			if (!folded && type == PlayerType::HUMAN_PLAYER) {
				// ask previous player if they want to call or fold
				std::cout << "\n";
				std::cout << players.at(playerIndex).getName() << " have raised to " << lastBet << std::endl;
				std::cout << players.at(i).getName() << ", Do you want to call to match the bet or fold? (c/f): " << std::endl;

				char choice;
				std::cin >> choice;
				// make sure choice is valid
				while (choice != 'c' && choice != 'f') {
					std::cout << "Invalid choice. Please enter c or f: ";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin >> choice;
				}

				if (choice == 'c') {
					makeCall(&players.at(i), pot);
				}
				else {
					makeFold(&players.at(i));
				}
			}
			else if (!folded && type == PlayerType::COMPUTER_PLAYER) {
				// AI player will always call
				makeCall(&players.at(i), pot);
			}
		}
	}
};
