#pragma once
#include "PokerHand.h"
#include "Player.h"
#include "DeckDealer.h"
#include <vector>
using namespace std;

class PokerGame {
public:
	PokerGame() {
		// set the initial game state
		// ask user enter how many players total
		cout << "Enter the number of total players you would like for this game: ";
		int numPlayers;
		cin >> numPlayers;
		// make sure num of players is between 2 and 7
		while (numPlayers < 2 || numPlayers > 7) {
			cout << "Invalid number of players. Please enter a number between 2 and 7: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> numPlayers;
		}

		// ask user how many of those players are human
		cout << "Enter the number of human players you would like for this game: ";
		int numHumanPlayers;
		cin >> numHumanPlayers;
		// make sure num of human players is between 1 and numPlayers
		while (numHumanPlayers < 1 || numHumanPlayers > numPlayers) {
			cout << "Invalid number of human players. Please enter a number between 1 and " << numPlayers << ": ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> numHumanPlayers;
		}

		// set each player
		for (int i = 0; i < numPlayers; i++) {
			string name;
			cout << "Enter the name of player " << i + 1 << ": ";
			cin >> name;
			int chips = 300;

			// if player is human
			if (i < numHumanPlayers) {
				Player player(name, chips);
				players.push_back(player);
			}
			// if player is computer, do this later
		}
	}

	void playGame() {
		int round = 1;
		while (keepPlaying) {
			std::cout << "\n\n\nRound " << round << std::endl;
			// deal hands to each player
			dealHands();
			// get ante from each player
			gatherAnte();

			// round 1
			for (int i = 0; i < players.size(); i++) {
				// if player is human
				humanRound(i);

				// if player is computer, do this later
			}
			round++;
			betMade = false;

			// replace cards round. Computer player dont replace cards
			for (int i = 0; i < players.size(); i++) {
				// if player is human
				replaceCards(i);
			}

			std::cout << "\nRound " << round << std::endl;
			std::cout << "The pot is now: " << pot << std::endl;
			// round 2
			for (int i = 0; i < players.size(); i++) {
				// if player is human
				humanRound(i);

				// if player is computer, do this later
			}

			// determine winner
			determineWinner();
			round = 1;
		}
	}
private:

	DeckDealer dealer;
	std::vector<Player> players;
	std::vector<int> winners;
	int pot = 0;
	int lastBet = 0;
	int winnerIndex = -1;
	int const MAX_BET = 100;
	int const MAX_RAISE = 100;
	int const ANTE = 10;
	bool betMade = false;
	bool keepPlaying = true;

	void dealHands() {
		// deal 5 cards to each player
		for (int j = 0; j < players.size(); j++) {
			std::array<Card, 5> hand = dealer.dealHand();
			players[j].setHand(hand);
		}
		cout << "Hands have been dealt." << endl;
	}

	void gatherAnte() {
		// subtract ante from each player's chips
		for (int i = 0; i < players.size(); i++) {
			players[i].setChips(players[i].getChips() - ANTE);
			pot += ANTE;
		}
		cout << "Ante of " << ANTE << " has been taken from each player." << endl;
		cout << "The pot is now: " << pot << endl;
	}

	void humanRound(int playerIndex) {
		// print player's hand
		cout << "\n" << players[playerIndex].getName() << ", Your hand is:" << endl;
		players[playerIndex].getHand().printHand();
		// print player's chips
		cout << "Your chips: " << players[playerIndex].getChips() << endl;

		// check if bet has been made
		if (!betMade) {
			// ask player if they want to bet or check or fold
			cout << "Do you want to bet, check, or fold? (b/c/f): ";
			char choice;
			cin >> choice;
			// make sure choice is valid
			while (choice != 'b' && choice != 'c' && choice != 'f') {
				cout << "Invalid choice. Please enter b, c, or f: ";
				cin >> choice;
			}
			// make move based on choice
			if (choice == 'b') {
				betMove(playerIndex);
				betMade = true;
			}
			else if (choice == 'f') {
				foldMove(playerIndex);
			}
		}
		// else bet has been made or we are in round 2
		else {
			// show last bet
			cout << "The last bet was: " << lastBet << endl;
			// ask player if they want to raise or call or fold
			cout << "Do you want to raise, call, or fold? (r/c/f): ";
			char choice;
			cin >> choice;
			// make sure choice is valid
			while (choice != 'r' && choice != 'c' && choice != 'f') {
				cout << "Invalid choice. Please enter r, c, or f: ";
				cin >> choice;
			}
			// make move based on choice
			if (choice == 'r') {
				raiseMove(playerIndex);
			}
			else if (choice == 'f') {
				foldMove(playerIndex);
			}
			else {
				callMove(playerIndex);
			}
		}
	}

	void betMove(int playerIndex) {
		// ask player how much they want to bet
		cout << "How much would you like to bet? (max bet is " << MAX_BET << "): ";
		cout << "Your current chips: " << players[playerIndex].getChips() << endl;
		int bet;
		cin >> bet;
		// make sure bet is valid
		while (bet < 0 || bet > MAX_BET || bet > players[playerIndex].getChips()) {
			int canBet = players[playerIndex].getChips() > MAX_BET ? MAX_BET : players[playerIndex].getChips();
			cout << "Invalid bet. Please enter a bet between 0 and " << canBet << ": ";
			cin >> bet;
		}
		// subtract bet from player's chips
		players[playerIndex].setChips(players[playerIndex].getChips() - bet);
		// add bet to pot
		pot += bet;
		lastBet = bet;

		// show the pot and player chips
		cout << "The pot is now: " << pot << endl;
		cout << "Your chips: " << players[playerIndex].getChips() << endl;
	}

	void foldMove(int playerIndex) {
		// fold player's hand
		players[playerIndex].fold();
	}

	void raiseMove(int playerIndex) {
		// ask player how much they want to raise
		cout << "How much would you like to raise? (max raise is " << MAX_RAISE << "): ";
		cout << "Your current chips: " << players[playerIndex].getChips() << endl;
		int raise;
		cin >> raise;
		// make sure raise is valid
		while (raise < 0 || raise > MAX_RAISE || raise > players[playerIndex].getChips()) {
			int canBet = players[playerIndex].getChips() > MAX_RAISE ? MAX_RAISE : players[playerIndex].getChips();
			cout << "Invalid raise. Please enter a raise between 0 and " << canBet << ": ";
			cin >> raise;
		}
		// subtract raise from player's chips
		players[playerIndex].setChips(players[playerIndex].getChips() - raise);
		// add raise to pot
		pot += raise;
		lastBet = raise;

		// show the pot and player chips
		cout << "The pot is now: " << pot << endl;
		cout << "Your chips: " << players[playerIndex].getChips() << endl;
	}

	void callMove(int playerIndex) {
		// subtract the difference between the current bet and the player's current bet from the player's chips
		int newAmount = players[playerIndex].getChips() - lastBet;
		// check if player has enough chips to call
		if (newAmount < 0) {
			cout << "You do not have enough chips to call. You are all in." << endl;
			newAmount = 0;
			pot += players[playerIndex].getChips();
		}
		else {
			pot += lastBet;
		}
		players[playerIndex].setChips(newAmount);

		// show the pot and player chips
		cout << "The pot is now: " << pot << endl;
		cout << "Your chips: " << players[playerIndex].getChips() << endl;
	}

	void replaceCards(int playerIndex) {
		// print player's hand
		cout << "\n" << players[playerIndex].getName() << ", Your hand is:" << endl;
		players[playerIndex].getHand().printHand();

		// ask player if they would like to replace any cards
		cout << "\nWould you like to replace any cards? (y/n): ";
		char choice;
		cin >> choice;
		// make sure choice is valid
		while (choice != 'y' && choice != 'n') {
			cout << "Invalid choice. Please enter y or n: ";
			cin >> choice;
		}
		cin.ignore();
		// if player wants to replace cards
		if (choice == 'y') {
			// determin how many cards can the player replace
			int playerCount = players.size();
			int cardLeft = dealer.cardsLeft();
			int maxReplace = cardLeft / playerCount;

			maxReplace = maxReplace > 3 ? 3 : maxReplace;

			// let the player know how many cards they can replace
			cout << "You can replace up to " << maxReplace << " cards." << endl;
			// ask player which cards they would like to replace
			cout << "Enter the index of the cards you would like to replace (0-4). Seperate them by space, i.e. (0 3 5): ";

			string indexes;
			getline(cin, indexes);

			// make sure index is valid
			while (!validReplacementIndex(indexes, maxReplace)) {
				cout << "Invalid index. Please enter the index of the cards you would like to replace (0-4). Seperate them by space, i.e. (0 3 5): ";
				getline(cin, indexes);
			}
			// replace the cards
			for (int i = 0; i < indexes.length(); i++) {
				if (indexes[i] != ' ') {
					int cardIndex = indexes[i] - '0';
					players[playerIndex].replaceCard(cardIndex, dealer.dealCard());
				}
			}

			// print player's new hand
			cout << "\nYour new hand is:" << endl;
			players[playerIndex].getHand().printHand();
		}
	}

	bool validReplacementIndex(string indexes, int maxReplace) {
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

	void determineWinner() {
		// determine the winner
		for (int i = 0; i < players.size(); i++) {
			// if player have not folded
			if (!players[i].getFold()) {
				if (winnerIndex == -1) {
					// set the first player as the winner
					winnerIndex = i;
				}
				else {
					if (players[i].compareHand(players[winnerIndex].getHand()) == 1) {
						winnerIndex = i;
					}
					else if (players[i].compareHand(players[winnerIndex].getHand()) == 0) {
						winners.push_back(i);
						winners.push_back(winnerIndex);
					}
				}
			}
		}
		announceWinner();

		// print new chips for each player
		for (int i = 0; i < players.size(); i++) {
			cout << players[i].getName() << " has " << players[i].getChips() << " chips." << endl;
		}

		// print rank for each player
		for (int i = 0; i < players.size(); i++) {
			cout << players[i].getName() << "'s hand rank is: ";
			players[i].getHand().printRank();
		}

		// reset the game state
		resetGame();

		// ask player if they would like to keep playing
		cout << "Would you like to keep playing? (y/n): ";
		char choice;
		cin >> choice;
		// make sure choice is valid
		while (choice != 'y' && choice != 'n') {
			cout << "Invalid choice. Please enter y or n: ";
			cin >> choice;
		}
		// if players dont want to keep playing
		if (choice == 'n') {
			keepPlaying = false;
		}
	}

	void announceWinner() {
		if (winners.size() > 1) {
			cout << "\nThere is a tie between: ";
			for (int i = 0; i < winners.size(); i++) {
				cout << players[winners[i]].getName() << " ";
			}
			cout << endl;
			// split the pot
			int splitPot = pot / winners.size();
			for (int i = 0; i < winners.size(); i++) {
				players[winners[i]].setChips(players[winners[i]].getChips() + splitPot);
			}

			cout << "The pot is now: " << splitPot << " for each of the winners." << endl;
		}
		else {
			// print the winner
			cout << "\nThe winner is: " << players[winnerIndex].getName() << endl;
			// add pot to winner's chips
			players[winnerIndex].setChips(players[winnerIndex].getChips() + pot);
		}
	}

	void resetGame() {
		// reset the game state
		pot = 0;
		lastBet = 0;
		winnerIndex = -1;
		winners.clear();
		betMade = false;
		dealer.resetDeck();

		// reset each player
		for (int i = 0; i < players.size(); i++) {
			players[i].unfold();
		}
	}
};
