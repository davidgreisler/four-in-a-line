#ifndef GAME_FOUR_IN_A_LINE_ASYNCHRONOUSARTIFICIALINTELLIGENCE_HPP
#define GAME_FOUR_IN_A_LINE_ASYNCHRONOUSARTIFICIALINTELLIGENCE_HPP

#include "ArtificialIntelligence.hpp"

#include <atomic>
#include <future>
#include <chrono>

namespace Game
{
namespace FourInALine
{

/**
 * Artificial intelligence which does the computing in a separate thread.
 *
 * This class extends the artificial intelligence and modifies it so that the computation of the
 * next move is done in a separate thread.
 *
 * The next move can be computed with computeNextMoveAsynchronously(). Use isNextMoveRead() to check
 * whether the result is ready and valid. The resulting move can then be retrieved with
 * getNextMove(), which also accepts an optional timeout parameter to block until the timeout
 * duration has elapsed or the result is ready. Default is a timeout of 0, which means no blocking.
 * When the timeout duration has elapsed and the result is not yet ready, it returns an
 * INVALID_RESULT.
 *
 * It is possible to check whether the AI is currently computing with isComputing() and the
 * computation can be cancelled with cancelComputation(). When the computation is cancelled, the
 * result will be INVALID_RESULT. Use isNextMoveValid() to check whether the next move is valid or
 * INVALID_RESULT.
 *
 * This class is reentrant but not thread-safe.
 */
class AsynchronousArtificialIntelligence : public ArtificialIntelligence
{
	public:
		AsynchronousArtificialIntelligence(unsigned int searchDepth);
		virtual ~AsynchronousArtificialIntelligence();

		void computeNextMoveAsynchronously(const Game& game);
		bool isNextMoveReady();
		bool isNextMoveValid();
		bool isComputing() const;
		unsigned int getNextMove(std::chrono::milliseconds timeout = std::chrono::milliseconds(0));

		void cancelComputation();

		/**
		 * Invalid result returned when the next move is not yet ready or the computation was
		 * cancelled.
		 */
		static const unsigned int INVALID_RESULT;

	private:
		virtual unsigned int computeNextMove(const Game& game);
		virtual ScoredMovesType minimax(Node node, const Board& board, PlayerType player,
		                                unsigned int depth, ScoreType alpha, ScoreType beta) const;

		/**
		 * Whether the computation should be cancelled or not.
		 */
		std::atomic<bool> cancel;

		/**
		 * Whether a computation is running or not.
		 *
		 * Mutable so that the minimax() method can stay const.
		 */
		mutable std::atomic<bool> running;

		/**
		 * Future used to compute the next task.
		 */
		std::future<unsigned int> nextMoveTask;

		/**
		 * The result of the last computation.
		 *
		 * Either a valid move or INVALID_RESULT.
		 */
		unsigned int lastResult;
};

}
}

#endif // GAME_FOUR_IN_A_LINE_ASYNCHRONOUSARTIFICIALINTELLIGENCE_HPP
