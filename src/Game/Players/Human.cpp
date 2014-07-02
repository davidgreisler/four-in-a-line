#include "Human.hpp"
#include "../../GUI/Widgets/Board.hpp"
#include "../Game.hpp"

namespace Game
{

namespace Players
{

/**
 * Creates a new human player.
 *
 * @param player Player id used by the game engine.
 * @param controls Which controls can this player use.
 * @param board The board widget, used to request moves from the player.
 * @param name Name of the player.
 * @param parent Parent object.
 */
Human::Human(::GameLogic::FourInALine::Game::PlayerType player,
                         Human::Controls controls, ::GUI::Widgets::Board* board,
                         QString name, QObject* parent)
    : AbstractPlayer(player, name, parent), controls(controls), board(board)
{
	this->connect(this->board, &::GUI::Widgets::Board::moveReady, this, &Human::userMadeMove);
}

/**
 * Frees all used resources.
 */
Human::~Human()
{

}

/**
 * Notifies the board widget that it should allow the player to drop a token on the board.
 *
 * @param game Current game state.
 */
void Human::requestMove(const QSharedPointer<const ::Game::Game>& game)
{
	auto availableColumns = game->getGameLogic()->getBoard()->getAvailableColumns();

	this->board->requestMove(availableColumns, this);
}

/**
 * Informs the board widget that it should not allow the player to drop a token on the board
 * anymore.
 */
void Human::abortMove()
{
	this->board->abortRequestMove();
}

/**
 * Returns the controls used by this player.
 *
 * @return Controls used by this player.
 */
Human::Controls Human::getControls() const
{
	return this->controls;
}

/**
 * Invoked by the board when the user made a move, emits moveReady().
 *
 * @param columnNo The column number where the user dropped the token.
 */
void Human::userMadeMove(unsigned int columnNo)
{
	emit this->moveReady(columnNo);
}

}
}
