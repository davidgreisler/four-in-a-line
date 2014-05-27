#ifndef GAME_FOUR_IN_A_LINE_ARTIFICIALINTELLIGENCE_HPP
#define GAME_FOUR_IN_A_LINE_ARTIFICIALINTELLIGENCE_HPP

#include "Game.hpp"
#include "Board.hpp"

#include <utility>
#include <map>

namespace Game
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
		typedef unsigned int PlayerType;
		typedef unsigned int ColumnType;
		typedef int ScoreType;
		typedef std::pair<ColumnType, ScoreType> ScoredMoveType;
		typedef std::map<ColumnType, ScoreType> ScoredMovesType;

		ArtificialIntelligence(unsigned int searchDepth);
		virtual ~ArtificialIntelligence();

		void setSearchDepth(unsigned int searchDepth);
		unsigned int getSearchDepth() const;

		unsigned int computeNextMove(const Game& game) const;

	private:
		enum class Node
		{
			MIN_NODE = 1, ///< Minimizing node.
			MAX_NODE = 2  ///< Maximizing node.
		};

		PlayerType getOtherPlayer(PlayerType player) const;
		ScoredMoveType findBestMove(Node node, const ScoredMovesType& scoredMoves) const;
		ScoredMovesType minimax(Node node, const Board& board, PlayerType player, unsigned int depth,
								ScoreType alpha, ScoreType beta) const;

		ScoreType computeScore(Node node, const Board& board, PlayerType player, unsigned int depth,
							   ScoreType alpha, ScoreType beta) const;

		ScoreType evaluateBoard(const Board& board, PlayerType player) const;
		ScoreType computePlayerScore(const Board& board, unsigned int player) const;

		bool canPruneBranch(Node node, ScoreType score, ScoreType& alpha, ScoreType&beta) const;

		/**
		 * Maximum search depth (how many levels the search tree has).
		 */
		unsigned int searchDepth;
};

}
}

#endif // GAME_FOUR_IN_A_LINE_ARTIFICIALINTELLIGENCE_HPP
