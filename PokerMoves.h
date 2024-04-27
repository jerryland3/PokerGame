#pragma once
#include "Player.h"
#include "Pot.h"

class PokerMoves {
public:
	void makeBet(Player* player, Pot* pot) {
		// ask player how much they want to bet
		std::cout << "How much would you like to bet? (max bet is " << pot->getMaxBet() << "): ";
		std::cout << "Your current chips: " << player->getChips() << std::endl;
		int bet;
		std::cin >> bet;

		// make sure bet is valid
		while (bet < 0 || bet > pot->getMaxBet() || bet > player->getChips()) {
			int canBet = player->getChips() > pot->getMaxBet() ? pot->getMaxBet() : player->getChips();
			std::cout << "Invalid bet. Please enter a bet between 0 and " << canBet << ": ";
			std::cin >> bet;
		}

		// subtract bet from player's chips
		player->setChips(player->getChips() - bet);
		// add bet to pot
		pot->increasePot(bet);
		lastBet = bet;

		// show the pot and player chips
		std::cout << "The pot is now: " << pot->getPotAmount() << std::endl;
		std::cout << "Your chips: " << player->getChips() << std::endl;

		betMade = true;
	}

	void makeRaise(Player* player, Pot* pot) {
		// ask player how much they want to raise
		std::cout << "How much would you like to raise? (max raise is " << pot->getMaxRaise() << "): ";
		std::cout << "Your current chips: " << player->getChips() << std::endl;
		int raise;
		std::cin >> raise;

		// make sure raise is valid
		while (raise < 0 || raise > pot->getMaxRaise() || raise > player->getChips()) {
			int canBet = player->getChips() > pot->getMaxRaise() ? pot->getMaxRaise() : player->getChips();
			std::cout << "Invalid raise. Please enter a raise between 0 and " << canBet << ": ";
			std::cin >> raise;
		}
		// subtract raise from player's chips
		player->setChips(player->getChips() - raise);
		// add raise to pot
		pot->increasePot(raise);
		lastBet = raise;

		// show the pot and player chips
		std::cout << "The pot is now: " << pot->getPotAmount() << std::endl;
		std::cout << "Your chips: " << player->getChips() << std::endl;
	}

	void makeCall(Player* player, Pot* pot) {
		// subtract the difference between the current bet and the player's current bet from the player's chips
		int newAmount = player->getChips() - lastBet;
		// check if player has enough chips to call
		if (newAmount < 0) {
			std::cout << "You do not have enough chips to call. You are all in." << std::endl;
			newAmount = 0;
			pot->increasePot(player->getChips());
		}
		else {
			pot->increasePot(lastBet);
		}
		player->setChips(newAmount);

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
};
