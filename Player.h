#pragma once
#include "PokerHand.h"

class Player {
public:
	Player(std::string name, int chips) : name{ name }, chips{ chips }, folded{ false } {}

	//Player() = default;

	std::string getName() const {
		return name;
	}

	int getChips() const {
		return chips;
	}

	void setChips(int chips) {
		this->chips = chips;
	}

	bool getFold() const {
		return folded;
	}

	void fold() {
		folded = true;
	}

	void unfold() {
		folded = false;
	}

	PokerHand getHand() const {
		return hand;
	}

	void setHand(PokerHand hand) {
		this->hand = hand;
	}

	void setName(std::string name) {
		this->name = name;
	}

	void replaceCard(int index, Card card) {
		hand.replaceCard(index, card);
	}

	int compareHand(PokerHand otherHand) {
		return hand.compareHand(otherHand);
	}

	void setBetAmount(int betAmount) {
		this->betAmount = betAmount;
	}

	int getBetAmount() const {
		return betAmount;
	}

	void resetBetAmount() {
		betAmount = 0;
	}

private:
	std::string name;
	PokerHand hand;
	int chips;
	int betAmount = 0;
	bool folded = false;
};
