#pragma once
#include "PokerHand.h"
#include "Player.h"
#include "DeckDealer.h"
#include "Pot.h"
#include "PokerMoves.h"
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
			int chips = 300;
			// if player is human
			string name;
			cout << "Enter the name of player " << i + 1 << ": ";
			cin >> name;
			Player player(name, chips);
			players.push_back(player);
		}
	}

	void playGame() {
		int round = 1;
		while (keepPlaying) {
			std::cout << "\n\n\nRound " << round << std::endl;
			// deal hands to each player
			dealer.dealHands(players);
			// get ante from each player
			pot.gatherAntes(players.data(), players.size());

			// round 1
			for (int i = 0; i < players.size(); i++) {
				// if player is human. add computer round later
				humanRound(i);
			}
			round++;
			pokerMoves.resetBet();

			// if all players except one have folded
			if (playersLeft() == 1) {
				determineWinner();
				announceWinner();
				playAgain();
				round = 1; // reset round
				resetGame();
				continue;
			}

			// reset players bet amount
			for (int i = 0; i < players.size(); i++) {
				players[i].resetBetAmount();
			}

			// replace cards round. Computer player dont replace cards
			for (int i = 0; i < players.size(); i++) {
				// if player is human and have not folded
				if (!players.at(i).getFold()) {
					dealer.replaceCards(&players[i], players.size());
				}
			}

			// round 2
			std::cout << "\nRound " << round << std::endl;
			std::cout << "The pot is now: " << pot.getPotAmount() << std::endl;
			for (int i = 0; i < players.size(); i++) {
				// if player is human. add computer round later
				if (!players.at(i).getFold()) {
					humanRound(i);
				}
			}

			determineWinner();
			announceWinner();
			playAgain();
			round = 1; // reset round
			resetGame();
		}
	}
private:

	DeckDealer dealer;
	std::vector<Player> players;
	std::vector<int> winners;
	Pot pot;
	PokerMoves pokerMoves;
	int winnerIndex = -1;
	bool keepPlaying = true;
	bool noWinner = false;

	void humanRound(int playerIndex) {
		// print player's hand
		cout << "\n" << players[playerIndex].getName() << ", Your hand is:" << endl;
		players[playerIndex].getHand().printHand();
		// print player's chips
		cout << "Your chips: " << players[playerIndex].getChips() << endl;

		// check if bet has been made
		if (!pokerMoves.getBetMade()) {
			// ask player if they want to bet or check or fold
			cout << "Do you want to bet, check, or fold? (b/c/f): ";
			char choice;
			cin >> choice;
			// make sure choice is valid
			while (choice != 'b' && choice != 'c' && choice != 'f') {
				cout << "Invalid choice. Please enter b, c, or f: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> choice;
			}
			// make move based on choice
			if (choice == 'b') {
				pokerMoves.makeBet(players, &pot, playerIndex);
			}
			else if (choice == 'f') {
				pokerMoves.makeFold(&players.at(playerIndex));
			}
		}
		// else bet has been made
		else {
			// show last bet
			cout << "The last bet was: " << pokerMoves.getLastBet() << endl;
			// ask player if they want to raise or call or fold
			cout << "Do you want to raise, call, or fold? (r/c/f): ";
			char choice;
			cin >> choice;
			// make sure choice is valid
			while (choice != 'r' && choice != 'c' && choice != 'f') {
				cout << "Invalid choice. Please enter r, c, or f: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> choice;
			}
			// make move based on choice
			if (choice == 'r') {
				pokerMoves.makeRaise(players, &pot, playerIndex);
			}
			else if (choice == 'f') {
				pokerMoves.makeFold(&players.at(playerIndex));
			}
			else {
				pokerMoves.makeCall(&players.at(playerIndex), &pot);
			}
		}
	}

	void determineWinner() {
		// determine index of players that have not folded
		std::vector<int> stillInGamePlayers;
		for (auto& player : players) {
			if (!player.getFold()) {
				stillInGamePlayers.push_back(&player - &players[0]);
			}
		}

		// if only one player left
		if (stillInGamePlayers.size() == 1) {
			winnerIndex = stillInGamePlayers.at(0);
			return;
		}
		else if (stillInGamePlayers.size() == 0) {
			noWinner = true;
			return;
		}

		winnerIndex = stillInGamePlayers.at(0); // set first player to be winner
		for (int i = 1; i < stillInGamePlayers.size(); i++) {
			if (players[i].compareHand(players[winnerIndex].getHand()) == 1) {
				winnerIndex = i;
			}
			else if (players[i].compareHand(players[winnerIndex].getHand()) == 0) {
				winners.push_back(i);
				winners.push_back(winnerIndex);
			}
		}
	}

	void playAgain() {
		// print new chips for each player
		for (int i = 0; i < players.size(); i++) {
			cout << players[i].getName() << " has " << players[i].getChips() << " chips." << endl;
		}

		// print rank for each player
		for (int i = 0; i < players.size(); i++) {
			cout << players[i].getName() << "'s hand rank is: ";
			players[i].getHand().printRank();
		}

		// ask player if they would like to keep playing
		cout << "Would you like to keep playing? (y/n): ";
		char choice;
		cin >> choice;
		// make sure choice is valid
		while (choice != 'y' && choice != 'n') {
			cout << "Invalid choice. Please enter y or n: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
			int splitPot = pot.getPotAmount() / winners.size();
			for (int i = 0; i < winners.size(); i++) {
				players[winners[i]].setChips(players[winners[i]].getChips() + splitPot);
			}

			cout << "The pot is now: " << splitPot << " for each of the winners." << endl;
		}
		else if (noWinner) {
			cout << "\nNo winner. All players folded." << endl;
		}
		else {
			// print the winner
			cout << "\nThe winner is: " << players[winnerIndex].getName() << endl;
			// add pot to winner's chips
			players[winnerIndex].setChips(players[winnerIndex].getChips() + pot.getPotAmount());
		}
	}

	void resetGame() {
		// reset the game state
		winnerIndex = -1;
		winners.clear();
		dealer.resetDeck();
		pot.resetPot();
		pokerMoves.resetBet();
		noWinner = false;

		// reset each player
		for (int i = 0; i < players.size(); i++) {
			players[i].unfold();
		}
	}

	int playersLeft() {
		int count = 0;
		for (int i = 0; i < players.size(); i++) {
			if (!players[i].getFold()) {
				count++;
			}
		}
		return count;
	}
};