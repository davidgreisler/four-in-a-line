#ifndef GAME_PLAYERS_ARTIFICIALINTELLIGENCE_HPP
#define GAME_PLAYERS_ARTIFICIALINTELLIGENCE_HPP

#include "AbstractPlayer.hpp"
#include "../../GameLogic/FourInALine/Game.hpp"
#include "../../GameLogic/FourInALine/AsynchronousArtificialIntelligence.hpp"

class QTimer;

namespace Game
{

namespace Players
{

/**
 * A player controlled by the computer/an artificial intelligence.
 *
 * This player uses an artificial intelligence to compute it's next moves.
 */
class ArtificialIntelligence : public AbstractPlayer
{
		Q_OBJECT
	public:
		/**
		 * How difficult it is to beat the artificial intelligence.
		 */
		enum class LevelOfDifficulty : unsigned int {
			VERY_EASY = 1,
			EASY = 3,
			NORMAL = 4,
			DIFFICULT = 5,
			CHALLENGE = 6
		};

		explicit ArtificialIntelligence(::GameLogic::FourInALine::Game::PlayerType player,
		                                      LevelOfDifficulty difficulty,
		                                      QString name = QString(""), QObject *parent = 0);
		virtual ~ArtificialIntelligence();

		virtual void requestMove(const QSharedPointer<const ::Game::Game>& game);

		virtual void abortMove();

		LevelOfDifficulty getLevelOfDifficulty() const;

	private slots:
		void checkIfNextMoveIsReady();

	private:
		/**
		 * How difficult should the AI be?
		 */
		LevelOfDifficulty difficulty;

		/**
		 * The artificial intelligence used to compute the next move.
		 */
		::GameLogic::FourInALine::AsynchronousArtificialIntelligence artificialIntelligence;

		/**
		 * Timer used to query the artificial intelligence.
		 */
		QTimer* timer;
};

}
}

Q_DECLARE_METATYPE(Game::Players::ArtificialIntelligence::LevelOfDifficulty)

#endif // GAME_PLAYERS_ARTIFICIALINTELLIGENCE_HPP
