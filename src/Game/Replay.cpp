#include "Replay.hpp"
#include "Game.hpp"
#include "../GameLogic/FourInALine/Game.hpp"

namespace Game
{

/**
 * Creates a new replay with the given moves and players.
 *
 * @param moves Vector containing game moves.
 * @param nColumns Number of columns.
 * @param nRows Number of rows.
 * @param firstPlayer Placeholder player for the first player.
 * @param secondPlayer Placeholder player for the second player.
 */
Replay::Replay(Replay::MovesVector moves, unsigned int nColumns, unsigned int nRows,
               Replay::PlayerPointer firstPlayer, Replay::PlayerPointer secondPlayer)
    : moves(moves), nColumns(nColumns), nRows(nRows),
      firstPlayer(firstPlayer), secondPlayer(secondPlayer)
{

}

/**
 * Frees all used resources.
 */
Replay::~Replay()
{

}

/**
 * Returns the move with the given move number.
 *
 * @param moveNo Move number.
 * @return The move as pair of player and column.
 */
std::pair<unsigned int, unsigned int> Replay::getMove(unsigned int moveNo) const
{
	return this->moves.at(moveNo);
}

/**
 * Computes the position of the token dropped in the move with the given number.
 *
 * @param moveNo Move number.
 * @return Token position as pair of X/Y coordinates.
 */
std::pair<unsigned int, unsigned int> Replay::computeMovePosition(unsigned int moveNo) const
{
	unsigned int x = this->getMove(moveNo).second;
	unsigned int y = this->nRows - 1;

	for (unsigned int i = 0; i < moveNo; ++i)
	{
		if (this->getMove(i).second == x)
		{
			y--;
		}
	}

	return std::make_pair(x, y);
}

/**
 * Creates a board containing all moves up to (including) the move with the given number.
 *
 * @param moveNo Move number.
 * @return Board containing all moves up to (including) the given move.
 */
GameLogic::FourInALine::Board Replay::computeBoard(unsigned int moveNo) const
{
	GameLogic::FourInALine::Board board(this->nColumns, this->nRows);

	for (unsigned int i = 0; i <= moveNo; ++i)
	{
		board.dropToken(this->getMove(i).second, this->getMove(i).first);
	}

	return board;
}

/**
 * Returns the number of moves.
 *
 * @return Number of moves.
 */
unsigned int Replay::getNumberOfMoves() const
{
	return this->moves.size();
}

/**
 * Converts the replay into a string.
 *
 * @return String for storing the replay.
 */
QString Replay::toString()
{
	QString result;

	// @todo Implement.

	return result;
}

/**
 * Creates a replay from the given string and returns it.
 *
 * @param string String created with Replay::toString().
 * @param playerFactory Player factory used to create placeholder players.
 * @return Replay with the state saved in the given string.
 * @throws ParseError When parsing the string fails.
 */
QSharedPointer<Replay> Replay::CreateFromString(const QString& string, Players::Factory& playerFactory)
{
	QSharedPointer<Replay> result;

	Q_UNUSED(string);

	// @todo Implement.

	auto firstPlayer = playerFactory.createPlaceholder(1u, "Player 1");
	auto secondPlayer = playerFactory.createPlaceholder(2u, "Player 2");

	std::vector<std::pair<unsigned int, unsigned int> > replay;
	replay.push_back(std::make_pair<unsigned int, unsigned int>(1u, 0u));
	replay.push_back(std::make_pair<unsigned int, unsigned int>(2u, 0u));
	replay.push_back(std::make_pair<unsigned int, unsigned int>(1u, 1u));
	replay.push_back(std::make_pair<unsigned int, unsigned int>(2u, 1u));
	replay.push_back(std::make_pair<unsigned int, unsigned int>(1u, 2u));
	replay.push_back(std::make_pair<unsigned int, unsigned int>(2u, 2u));

	result = QSharedPointer<Replay>::create(replay, 5u, 5u, firstPlayer, secondPlayer);

	return result;
}

/**
 * Creates and returns a replay from the given game.
 *
 * @param game Game to create a replay for.
 * @param playerFactory Player factory used to create placeholder players.
 * @return Replay of the game.
 */
QSharedPointer<Replay> Replay::CreateFromGame(QSharedPointer<const Game> game, Players::Factory& playerFactory)
{
	QSharedPointer<Replay> result;

	auto firstPlayer = playerFactory.createPlaceholder(game->getFirstPlayer());
	auto secondPlayer = playerFactory.createPlaceholder(game->getSecondPlayer());

	result = QSharedPointer<Replay>::create(game->getGameLogic()->getReplay(),
	                                        game->getGameLogic()->getBoard()->getNumberOfColumns(),
	                                        game->getGameLogic()->getBoard()->getNumberOfRows(),
	                                        firstPlayer, secondPlayer);

	return result;
}

/**
 * Returns the first player of the replay game.
 *
 * @return Placeholder player for the first player.
 */
Replay::PlayerPointer Replay::getFirstPlayer() const
{
	return this->firstPlayer;
}

/**
 * Returns the second player of the replay game.
 *
 * @return Placeholder player for the second player.
 */
Replay::PlayerPointer Replay::getSecondPlayer() const
{
	return this->secondPlayer;
}

/**
 * Returns the number of rows in the game board.
 *
 * @return Number of rows.
 */
unsigned int Replay::getNumberOfRows() const
{
	return this->nRows;
}

/**
 * Returns the number of columns in the game board.
 *
 * @return Number of columns.
 */
unsigned int Replay::getNumberOfColumns() const
{
	return this->nColumns;
}

}
