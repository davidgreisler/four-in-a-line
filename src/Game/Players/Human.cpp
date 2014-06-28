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

	this->board->requestMove(availableColumns, this->controls);
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

}
}
