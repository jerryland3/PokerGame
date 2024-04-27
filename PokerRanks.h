/**
 * @enum PokerRanks
 * @brief Defines the PokerRanks enum class for representing all
 * the ranks of a poker.
 *
 * @date 2/18/2024
 * @version New
 * @author Jerry Wang
 */
#pragma once

enum class PokerRanks {
	DEFAULT_RANK, /**< Default rank */
	HIGH_CARD,    /**< High card */
	PAIR,         /**< Pair */
	TWO_PAIR,     /**< Two pair */
	THREE_OF_A_KIND, /**< Three of a kind */
	STRAIGHT,     /**< Straight */
	FLUSH,        /**< Flush */
	FULL_HOUSE,   /**< Full house */
	FOUR_OF_A_KIND, /**< Four of a kind */
	STRAIGHT_FLUSH /**< Straight flush */
};
