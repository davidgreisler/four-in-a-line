#include "ArtificialIntelligence.hpp"
#include "../Game.hpp"

#include <QTimer>
#include <QDebug>

namespace Game
{

namespace Players
{

/**
 * Creates a new artificial intelligence player.
 *
 * The difficulty is used to set the search depth of the artificial intelligence.
 *
 * @param player Player id used by the game engine.
 * @param difficulty How difficult should it be to beat the artificial intelligence?
 * @param name Name of the player.
 * @param parent Parent object.
 */
ArtificialIntelligence::ArtificialIntelligence(::GameLogic::FourInALine::Game::PlayerType player,
                                                           LevelOfDifficulty difficulty,
                                                           QString name, QObject *parent) :
    AbstractPlayer(player, name, parent), difficulty(difficulty),
    artificialIntelligence(static_cast<unsigned int>(difficulty))
{
	this->timer = new QTimer(this);
	this->timer->setInterval(100);

	this->connect(this->timer, &QTimer::timeout,
	              this, &ArtificialIntelligence::checkIfNextMoveIsReady);
}

/**
 * Frees all used resources.
 */
ArtificialIntelligence::~ArtificialIntelligence()
{
	this->abortMove();
}

/**
 * Computes the next move.
 *
 * @param game The current game.
 */
void ArtificialIntelligence::requestMove(const QSharedPointer<const ::Game::Game>& game)
{
	qDebug() << "[" << this << "::requestMove ] Move requested.";

	::GameLogic::FourInALine::Game gameEngine(*(game->getGameLogic().data()));

	this->artificialIntelligence.computeNextMoveAsynchronously(gameEngine);
	this->timer->start();
}

/**
 * Aborts the computation of the next move.
 */
void ArtificialIntelligence::abortMove()
{
	this->timer->stop();
	this->artificialIntelligence.cancelComputation();
}

/**
 * Returns the level of difficulty of the artificial intelligence.
 *
 * @return Level of difficulty.
 */
ArtificialIntelligence::LevelOfDifficulty ArtificialIntelligence::getLevelOfDifficulty() const
{
	return this->difficulty;
}

/**
 * Checks whether the next move is ready and if yes, stops the timer and emits the result.
 */
void ArtificialIntelligence::checkIfNextMoveIsReady()
{
	if (this->artificialIntelligence.isNextMoveReady())
	{
		qDebug() << "[" << this << "::checkIfNextMoveIsReady ] Move ready!";

		unsigned int move = this->artificialIntelligence.getNextMove();
		this->timer->stop();

		emit this->moveReady(move);
	}
}

}
}
