#ifndef GUI_ARTIFICIALINTELLIGENCEPLAYER_HPP
#define GUI_ARTIFICIALINTELLIGENCEPLAYER_HPP

#include "AbstractPlayer.hpp"
#include "../Game/FourInALine/Game.hpp"
#include "../Game/FourInALine/AsynchronousArtificialIntelligence.hpp"

class QTimer;

namespace GUI
{

/**
 * A player controlled by the computer/an artificial intelligence.
 *
 * This player uses an artificial intelligence to compute it's next moves.
 */
class ArtificialIntelligencePlayer : public AbstractPlayer
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

		explicit ArtificialIntelligencePlayer(::Game::FourInALine::Game::PlayerType player,
											  LevelOfDifficulty difficulty,
											  QString name = QString(""), QObject *parent = 0);
		virtual ~ArtificialIntelligencePlayer();

		virtual void requestMove(const QSharedPointer<const ::GUI::Game>& game);

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
		::Game::FourInALine::AsynchronousArtificialIntelligence artificialIntelligence;

		/**
		 * Timer used to query the artificial intelligence.
		 */
		QTimer* timer;
};

}

Q_DECLARE_METATYPE(GUI::ArtificialIntelligencePlayer::LevelOfDifficulty)

#endif // GUI_ARTIFICIALINTELLIGENCEPLAYER_HPP
