#include "AsynchronousArtificialIntelligence.hpp"
#include "Game.hpp"

#include <limits>
#include <chrono>
#include <stdexcept>

namespace GameLogic
{
namespace FourInALine
{

const unsigned int AsynchronousArtificialIntelligence::INVALID_RESULT = std::numeric_limits<unsigned int>::max();

/**
 * Thrown when the computation is cancelled.
 */
class InterruptedException : public std::runtime_error
{
	public:
		/**
		 * Creates a new interrupted exception with the given message.
		 *
		 * @param message Message.
		 */
		InterruptedException(const std::string& message)
		    : std::runtime_error(message)
		{
		}
};

/**
 * Creates a new asynchronous artificial intelligence with the given search depth.
 *
 * @param searchDepth Search depth.
 */
AsynchronousArtificialIntelligence::AsynchronousArtificialIntelligence(unsigned int searchDepth)
    : ArtificialIntelligence(searchDepth), cancel(false), running(false),
      lastResult(AsynchronousArtificialIntelligence::INVALID_RESULT)
{

}

/**
 * Frees all used resources.
 */
AsynchronousArtificialIntelligence::~AsynchronousArtificialIntelligence()
{
	if (this->isComputing())
	{
		this->cancelComputation();
	}
}

/**
 * Starts computation of the next move in a separate thread.
 *
 * @param game The current game state.
 */
void AsynchronousArtificialIntelligence::computeNextMoveAsynchronously(const Game& game)
{
	if (this->isComputing())
	{
		this->cancelComputation();
	}

	this->lastResult = AsynchronousArtificialIntelligence::INVALID_RESULT;
	this->running = true;
	this->cancel = false;
	this->nextMoveTask = std::async(std::launch::async,
	                                &AsynchronousArtificialIntelligence::computeNextMove,
	                                this, game);
}

/**
 * Returns whether the result/next move is ready.
 *
 * The next move is ready when the computation is finished and the result is valid.
 *
 * @return When it is ready true, otherwise false.
 */
bool AsynchronousArtificialIntelligence::isNextMoveReady()
{
	return !this->isComputing() && this->isNextMoveValid();
}

/**
 * Returns whether the result/next move is valid.
 *
 * The next move will be invalid when the computation was cancelled using cancelComputation() or
 * when it is not yet ready.
 *
 * @return When it is valid true, otherwise false.
 */
bool AsynchronousArtificialIntelligence::isNextMoveValid()
{
	return this->getNextMove() != AsynchronousArtificialIntelligence::INVALID_RESULT;
}

/**
 * Returns whether the artificial intelligence is computing a move at the moment.
 *
 * @return When it is computing true, otherwise false.
 */
bool AsynchronousArtificialIntelligence::isComputing() const
{
	return this->running;
}

/**
 * Returns the result of the computation.
 *
 * @return Result of the computation or INVALID_RESULT when the result isn't ready yet or the
 *         computation was cancelled.
 * @see AsynchronousArtificialIntelligence::isNextMoveReady() To check whether the next move is
 *      ready.
 */
unsigned int AsynchronousArtificialIntelligence::getNextMove(std::chrono::milliseconds timeout)
{
	if (this->running)
	{
		this->nextMoveTask.wait_for(timeout);
	}

	bool taskValidAndReady = this->nextMoveTask.valid() &&
	                         this->nextMoveTask.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
	if (!this->running && taskValidAndReady)
	{
		try
		{
			// Computation finished, get the result.

			this->lastResult = this->nextMoveTask.get();
		}
		catch (InterruptedException)
		{
			// The computation was interrupted, the result is "ready" but invalid.

			this->lastResult = AsynchronousArtificialIntelligence::INVALID_RESULT;
		}
		catch (...)
		{
			// An exception was thrown by the artificial intelligence. The result is invalid.

			this->lastResult = AsynchronousArtificialIntelligence::INVALID_RESULT;
		}
	}

	return this->lastResult;
}

/**
 * Cancels the computation, the result will be invalid.
 */
void AsynchronousArtificialIntelligence::cancelComputation()
{
	this->cancel = true;
}

/**
 * Computes the next move and sets the running attribute to false.
 *
 * This method just calls ArtificialIntelligence::computeNextMove() and returns it's result. But
 * before returning the result it sets the running attribute to false so that it is possible to know
 * that the result is ready.
 *
 * @param game The game for which the next move should be computed.
 * @return The next move.
 * @see ArtificialIntelligence::computeNextMove() Called by this method.
 */
unsigned int AsynchronousArtificialIntelligence::computeNextMove(const Game& game) const
{
	unsigned int result = ArtificialIntelligence::computeNextMove(game);

	this->running = false;
	return result;
}

/**
 * Checks whether the computation should be cancelled and if not calls
 * ArtificialIntelligence::minimax.
 *
 * @param node Whether this node is minimizing or maximizing.
 * @param board The board to evaluate.
 * @param player The current player (who made the last move on the board).
 * @param depth Remaining search depth.
 * @param alpha Maximum score the maximizing player is assured of.
 * @param beta Minimum score the minimizing player is assured of.
 * @return List of scored moves.
 * @see ArtificialIntelligence::minimax() Called by this method.
 */
ArtificialIntelligence::ScoredMovesType
AsynchronousArtificialIntelligence::minimax(ArtificialIntelligence::Node node, const Board& board,
                                            ArtificialIntelligence::PlayerType player,
                                            unsigned int depth,
                                            ArtificialIntelligence::ScoreType alpha,
                                            ArtificialIntelligence::ScoreType beta) const
{
	if (this->cancel)
	{
		// This ends the computation. ;-)

		this->running = false;
		throw InterruptedException("Computation cancelled.");
	}

	return ArtificialIntelligence::minimax(node, board, player, depth, alpha, beta);
}

}
}
