#include "ArtificialIntelligence.hpp"
#include "Board.hpp"
#include "Game.hpp"

#include <QDebug>

#include <algorithm>
#include <memory>
#include <limits>

namespace Game
{
namespace FourInALine
{

/**
 * Create a new artificial intelligence using the given search depth.
 *
 * @param searchDepth The search depth to use.
 */
ArtificialIntelligence::ArtificialIntelligence(unsigned int searchDepth)
	: searchDepth(searchDepth)
{

}

/**
 * Frees all used resources.
 */
ArtificialIntelligence::~ArtificialIntelligence()
{

}

/**
 * Sets the search depth to the given search depth.
 *
 * @param searchDepth The new search depth.
 */
void ArtificialIntelligence::setSearchDepth(unsigned int searchDepth)
{
	this->searchDepth = searchDepth;
}

/**
 * Returns the search depth.
 *
 * @return Search depth.
 */
unsigned int ArtificialIntelligence::getSearchDepth() const
{
	return this->searchDepth;
}

/**
 * Computes the next best move for the given game.
 *
 * @param game The game to evaluate.
 * @return Column index.
 */
unsigned int ArtificialIntelligence::computeNextMove(const Game& game) const
{
	ScoredMovesType scoredMoves;
	ScoredMoveType bestMove;
	std::shared_ptr<const Board> board = game.getBoard();
	Board myBoard(*board);
	unsigned int player = game.getCurrentPlayer();

	scoredMoves = this->minimax(Node::MAX_NODE, myBoard, player, this->searchDepth,
								std::numeric_limits<ScoreType>::min(),
								std::numeric_limits<ScoreType>::max());

	bestMove = this->findBestMove(Node::MAX_NODE, scoredMoves);

	return bestMove.first;
}

/**
 * Returns the other player.
 *
 * @param player The player.
 * @return The other player.
 */
ArtificialIntelligence::PlayerType
ArtificialIntelligence::getOtherPlayer(ArtificialIntelligence::PlayerType player) const
{
	return (player == Game::PLAYER_ONE) ? Game::PLAYER_TWO : Game::PLAYER_ONE;
}

/**
 * Finds and returns the best move in the given set of moves.
 *
 * For minimizing nodes this method returns the move with the lowest score, for maximizing nodes
 * the move with the highest score is returned.
 *
 * @param node Whether to look for the move with the minimum score (Node::MIN_NODE) or the maximum
 *        score (Node::MAX_NODE).
 * @param scoredMoves List of moves.
 * @return The scored move with the maximum/minimum (see node) score.
 */
ArtificialIntelligence::ScoredMoveType
ArtificialIntelligence::findBestMove(ArtificialIntelligence::Node node,
									 const ArtificialIntelligence::ScoredMovesType& scoredMoves) const
{
	ScoredMoveType result;

	auto compareMoves = [](const ScoredMoveType& move1, const ScoredMoveType& move2)
	{
		return move1.second < move2.second;
	};

	if (scoredMoves.empty())
	{
		throw std::runtime_error("Tried to find the best move in an empty list of moves.");
	}

	if (node == Node::MIN_NODE)
	{
		result = *std::min_element(scoredMoves.cbegin(), scoredMoves.cend(), compareMoves);
	}
	else
	{
		result = *std::max_element(scoredMoves.cbegin(), scoredMoves.cend(), compareMoves);
	}

	return result;
}

/**
 * Returns a list of scored moves.
 *
 * This method is implementing the minimax-algorithm.
 *
 * First it will create a list of possible moves on the given board. If the remaining search depth
 * is greater than 0 and there are possible moves, it will iterate over the moves and execute and
 * score them using computeScore(). The result is saved in a list which is returned at the end.
 *
 * Each time a move is scored, it is checked whether the branch can be pruned using
 * alpha-beta-pruning.
 *
 * @param node Whether this node is minimizing or maximizing.
 * @param board The board to evaluate.
 * @param player The current player (who made the last move on the board).
 * @param depth Remaining search depth.
 * @param alpha Maximum score the maximizing player is assured of.
 * @param beta Minimum score the minimizing player is assured of.
 * @return List of scored moves.
 * @see ArtificialIntelligence::canPruneBranch() Alpha-beta-pruning.
 */
ArtificialIntelligence::ScoredMovesType
ArtificialIntelligence::minimax(ArtificialIntelligence::Node node, const Board& board,
								ArtificialIntelligence::PlayerType player, unsigned int depth,
								ScoreType alpha, ScoreType beta) const
{
	ArtificialIntelligence::ScoredMovesType result;
	std::vector<unsigned int> possibleMoves = board.getAvailableColumns();

	// Return an empty set of results when:
	//
	// - The search depth has been exceeded.
	// - No more moves are possible (board full).
	// - There is a winner.

	if (depth > 0 && possibleMoves.size() > 0 && board.findWinningCells().isEmpty())
	{
		for(auto it = possibleMoves.begin(); it != possibleMoves.end(); ++it)
		{
			Board boardAfterMove(board);

			boardAfterMove.dropToken(*it, player);

			ScoreType score = this->computeScore(node, boardAfterMove, player, depth, alpha, beta);
			result[*it] = score;

			if (this->canPruneBranch(node, score, alpha, beta))
			{
				break;
			}
		}
	}

	return result;
}

/**
 * Computes and returns the score of the given board.
 *
 * This method is part of the minimax-algorithm. It will reduce the given depth by one and
 * it will call the minimax algorithm again with the opposite node type and player.
 * Thereby the minimax-algorithm is always alternately called with the minimizing and maximizing
 * player and in minimizing and maximizing mode.
 *
 * When the minimax algorithm returns no results that means that either the search depth has been
 * exceeded or no more moves were possible. In that case the given board is evaluated and the
 * score is returned.
 *
 * When the minimax algorithm returns a list of scored moves, the best move is selected and
 * returned. If the given node type is minimizing, the move with the lowest score is returned, if
 * the given node type is maximizing, the move with the highest score is returned.
 *
 * @param node Whether this node is minimizing or maximizing.
 * @param board The board to evaluate.
 * @param player The current player (who made the last move on the board).
 * @param depth Remaining search depth.
 * @param alpha Maximum score the maximizing player is assured of.
 * @param beta Minimum score the minimizing player is assured of.
 * @return The computed score.
 */
ArtificialIntelligence::ScoreType
ArtificialIntelligence::computeScore(ArtificialIntelligence::Node node, const Board& board,
									 ArtificialIntelligence::PlayerType player, unsigned int depth,
									 ScoreType alpha, ScoreType beta) const
{
	ScoreType score;
	ScoredMovesType scoredMoves;
	Node childNode = (node == Node::MAX_NODE) ? Node::MIN_NODE : Node::MAX_NODE;
	PlayerType aiPlayer = (node == Node::MAX_NODE) ? player : this->getOtherPlayer(player);

	scoredMoves = this->minimax(childNode, board, this->getOtherPlayer(player), depth - 1, alpha, beta);
	if (scoredMoves.empty())
	{
		// No more moves were possible or depth exceeded.

		score = this->evaluateBoard(board, aiPlayer);
	}
	else
	{
		score = this->findBestMove(childNode, scoredMoves).second;
	}

	return score;
}

/**
 * Evaluates the given board and returns a score for the given player.
 *
 * When the given player won the game the maximum score is returned, when the other player won
 * the minimum possible score is returned. Otherwise, the result is the score of the player
 * subtracted by the score of the other player.
 *
 * @param board The board to evaluate.
 * @param player The player for which the score should be computed.
 * @return The computed score.
 */
ArtificialIntelligence::ScoreType
ArtificialIntelligence::evaluateBoard(const Board& board, ArtificialIntelligence::PlayerType player) const
{
	ScoreType result;
	PlayerType otherPlayer = this->getOtherPlayer(player);

	int playerScore = this->computePlayerScore(board, player);
	int otherPlayerScore = this->computePlayerScore(board, otherPlayer);

	// If one of the players won, return the score of the winner, otherwise, subtract the score
	// of the other player from the score of the player.

	if (playerScore == std::numeric_limits<ScoreType>::max())
	{
		result = std::numeric_limits<ScoreType>::max();
	}
	else if (otherPlayerScore == std::numeric_limits<ScoreType>::max())
	{
		result = std::numeric_limits<ScoreType>::min();
	}
	else
	{
		result = playerScore - otherPlayerScore;
	}

	return result;
}

/**
 * Iterates over all cells of the given board and computes a score for the given player.
 *
 * The higher the returned score, the higher is the probability that the given player wins the game.
 *
 * The algorithm iterates over all horizontal/vertical/diagonal rows in the board and then checks
 * how many consecutive cells are owned by the player or empty (but not owned by the other player).
 * Whenever the algorithm finds 4 consecutive cells containing the player's token or an empty token,
 * it will increase the score depending on the amount of tokens in the 4 cells that belong to the
 * player.
 *
 * If in 4 consecutive tokens, 1 is owned by the player, the score is increased by 1, when 2 tokens
 * are owned by the player it is increased by 10. When the player owns 3 of the 4 tokens, the score
 * is increased by 100 and if the player owns all 4 tokens the score is set to the maximum score
 * (player wins).
 *
 * @param board The board to evaluate.
 * @param player The player for which the score is calculated.
 * @return Score for the given board/player.
 */
ArtificialIntelligence::ScoreType
ArtificialIntelligence::computePlayerScore(const Board& board, unsigned int player) const
{
	ScoreType score = 0;
	std::vector<CellSet> sets = board.getAllRows();
	std::vector<CellSet>::const_iterator i;
	CellSetIterator j;
	unsigned int nConsecutive;

	for (i = sets.begin(); i != sets.end() && score != std::numeric_limits<ScoreType>::max(); i++)
	{
		nConsecutive = 0;
		for(j = i->begin(); j != i->end() && score != std::numeric_limits<ScoreType>::max(); j++)
		{
			if (Board::CELL_EMPTY == *j || player == *j)
			{
				nConsecutive++;
			}
			else
			{
				nConsecutive = 0;
			}

			if (nConsecutive >= 4)
			{
				int value = 0;

				value += (i->getContent(j.getIndex() - 3) == player) ? 1 : 0;
				value += (i->getContent(j.getIndex() - 2) == player) ? 1 : 0;
				value += (i->getContent(j.getIndex() - 1) == player) ? 1 : 0;
				value += (*j == player) ? 1 : 0;

				switch(value)
				{
					case 1: score += 1; break;
					case 2: score += 10; break;
					case 3: score += 100; break;
					case 4: score = std::numeric_limits<ScoreType>::max();
				}
			}
		}
	}

	return score;
}

/**
 * Adjusts given alpha/beta values if neccessary and returns whether the current branch can be
 * pruned.
 *
 * This method implements alpha-beta-pruning to reduce the amount of game situations that have to
 * be evaluated.
 *
 * The algorithm maintains two values, alpha and beta. Alpha is the maximum score that the maximizing
 * player is assured of and beta is the minimum score that the minimizing player is assured of.
 *
 * If a move is scored and it's score is below beta on a minimizing node, then the score becomes the
 * new beta. If a move on a maximizing node is scored and the score is higher than alpha, the score
 * becomes the new alpha value.
 *
 * The beta value therefore is the worst-case scenario for the maximizing player and the alpha value
 * is the worst-case scenario for the minimum player.
 *
 * When beta is lower than alpha on a minimizing node, that means that the score of the node is
 * lower than the maximum score that the maximizing player is assured of through another already
 * evaluated move. The maximizing player would not offer this move to the minimizing player, because
 * there is a better alternative. Therefore the branch does not have to be evaluated anymore, as it
 * has no influence on the final result.
 *
 * The same applies to an alpha value higher or equal the beta value on a maximizing node. The
 * minimizing player would not allow the maximizing player to make that move anyway, because it is
 * worse than another previously evaluated move.
 *
 * @param node Type of the current node (minimizing or maximizing).
 * @param score The score of the node.
 * @param alpha Maximum score the maximizing player is assured of.
 * @param beta Minimum score the minimizing player is assured of.
 * @return When the branch can be pruned true, otherwise false.
 */
bool ArtificialIntelligence::canPruneBranch(ArtificialIntelligence::Node node,
											ArtificialIntelligence::ScoreType score,
											ArtificialIntelligence::ScoreType& alpha,
											ArtificialIntelligence::ScoreType& beta) const
{
	bool result = false;

	if (Node::MIN_NODE == node)
	{
		// Minimizing node.

		if (score < beta)
		{
			// The score of this node is lower than the minimum score the minimizing player is
			// assured of.
			//
			// Adjust the minimum assured score for the minimizing player.

			beta = score;
		}

		if (beta <= alpha)
		{
			// The score of this node is lower than the maximum score that the maximizing player is
			// assured of. The maximizing player would not allow the minimizing player to make this
			// move, because there is a better alternative.
			//
			// Therefore this branch can be pruned, as it has no influence on the final result
			// (alpha cutoff).

			result = true;
		}
	}
	else
	{
		// Maximizing node.

		if (score > alpha)
		{
			// The score of this node is higher than the maximum score the maximizing player is
			// currently assured of.
			//
			// Adjust the maximum assured score for the maximizing player.

			alpha = score;
		}

		if (alpha >= beta)
		{
			// The score of this node is higher than the minimum score that the minimizing player is
			// assured of. The minimizing player would not allow the maximizing player to make this
			// move, because there is a better alternative.
			//
			// Therefore this branch can be pruned, as it has not influence on the final result
			// (beta cutoff).

			result = true;
		}
	}

	return result;
}

}
}
