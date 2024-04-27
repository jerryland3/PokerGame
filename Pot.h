#pragma once

class Pot {
public:
	void increasePot(int amount) {
		potAmount += amount;
	}

	void resetPot() {
		potAmount = 0;
	}

	int getPotAmount() {
		return potAmount;
	}

	int getMaxBet() {
		return MAX_BET;
	}

	int getMaxRaise() {
		return MAX_RAISE;
	}

	int getAnteAmount() {
		return ANTE_AMOUNT;
	}

	void gatherAntes(Player* players, int numPlayers) {
		for (int i = 0; i < numPlayers; i++) {
			players[i].setChips(players[i].getChips() - ANTE_AMOUNT);
			increasePot(ANTE_AMOUNT);
		}

		std::cout << "Ante of " << ANTE_AMOUNT << " has been taken from each player." << std::endl;
		std::cout << "The pot is now: " << potAmount << std::endl;
	}

private:
	int potAmount;
	int MAX_BET = 100;
	int MAX_RAISE = 100;
	int ANTE_AMOUNT = 10;
};
