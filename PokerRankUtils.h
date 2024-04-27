/**
 * @class PokerRankUtils
 * @brief Utility class for converting PokerRanks enum values to string representations.
 *
 * This class provides a static method for converting PokerRanks enum values to their corresponding string representations.
 *
 * @date 2/18/2024
 * @version New
 * @author Jerry Wang
 */

#pragma once
#include "PokerRanks.h"

class PokerRankUtils {
public:
	/**
	 * @brief Converts a PokerRanks enum value to its string representation.
	 *
	 * This static method takes a PokerRanks enum value as input and returns its string representation.
	 *
	 * @param rank The PokerRanks enum value to convert.
	 * @return The string representation of the given PokerRanks enum value.
	 */
	static std::string rankToString(PokerRanks rank) {
		switch (rank) {
		case PokerRanks::HIGH_CARD:
			return "High Card";
		case PokerRanks::PAIR:
			return "Pair";
		case PokerRanks::TWO_PAIR:
			return "Two Pair";
		case PokerRanks::THREE_OF_A_KIND:
			return "Three of a Kind";
		case PokerRanks::STRAIGHT:
			return "Straight";
		case PokerRanks::FLUSH:
			return "Flush";
		case PokerRanks::FULL_HOUSE:
			return "Full House";
		case PokerRanks::FOUR_OF_A_KIND:
			return "Four of a Kind";
		case PokerRanks::STRAIGHT_FLUSH:
			return "Straight Flush";
		default:
			return "Default Rank";
		}
	}
};