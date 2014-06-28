#ifndef GAMELOGIC_FOUR_IN_A_LINE_ARTIFICIALINTELLIGENCE_HPP
#define GAMELOGIC_FOUR_IN_A_LINE_ARTIFICIALINTELLIGENCE_HPP

#include "Game.hpp"
#include "Board.hpp"

#include <utility>
#include <map>

namespace GameLogic
{
namespace FourInALine
{

/**
 * Artificial intelligence for a four in a line game.
 *
 * This class implements an artificial intelligence for a four in a line game. It uses the minimax
 * algorithm to find the next best move. The amount of game boards to evaluate is reduced with
 * alpha-beta-pruning.
 *
 * It is possible to specify the maximum search depth using setSearchDepth() or during construction.
 *
 * Use computeNextMove(game) to find the next best move.
 *
 * This class is reentrant but not thread-safe.
 */
class ArtificialIntelligence
{
	public:
		/**
		 * Type used for a player id.
		 */
		using PlayerType = unsigned int;

		/**
		 * Type used for specifying columns of the board.
		 */
		using ColumnType = unsigned int;

		/**
		 * Type used for a score of a move.
		 */
		using ScoreType = int;

		/**
		 * Pair of a column index and a score.
		 */
		using ScoredMoveType = std::pair<ColumnType, ScoreType>;

		/**
		 * Map of column indexes to scores.
		 */
		using ScoredMovesType = std::map<ColumnType, ScoreType>;

		ArtificialIntelligence(unsigned int searchDepth);
		virtual ~ArtificialIntelligence();

		void setSearchDepth(unsigned int searchDepth);
		unsigned int getSearchDepth() const;

		virtual unsigned int computeNextMove(const Game& game) const;

	protected:
		/**
		 * Whether a node is maximizing or minimizing.
		 */
		enum class Node
		{
			MIN_NODE = 1, ///< Minimizing node.
			MAX_NODE = 2  ///< Maximizing node.
		};

		PlayerType getOtherPlayer(PlayerType player) const;
		ScoredMoveType findBestMove(Node node, const ScoredMovesType& scoredMoves) const;
		virtual ScoredMovesType minimax(Node node, const Board& board, PlayerType player,
		                                unsigned int depth, ScoreType alpha, ScoreType beta) const;

		ScoreType computeScore(Node node, const Board& board, PlayerType player, unsigned int depth,
		                       ScoreType alpha, ScoreType beta) const;

		ScoreType evaluateBoard(const Board& board, PlayerType player) const;
		ScoreType computePlayerScore(const Board& board, unsigned int player) const;

		bool canPruneBranch(Node node, ScoreType score, ScoreType& alpha, ScoreType& beta) const;

		/**
		 * Maximum search depth (how many levels the search tree has).
		 */
		unsigned int searchDepth;
};

}
}

#endif // GAMELOGIC_FOUR_IN_A_LINE_ARTIFICIALINTELLIGENCE_HPP
