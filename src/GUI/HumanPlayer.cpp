#include "HumanPlayer.hpp"
#include "Widgets/Board.hpp"
#include "Game.hpp"

namespace GUI
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
HumanPlayer::HumanPlayer(::Game::FourInALine::Game::PlayerType player,
						 HumanPlayer::Controls controls, Widgets::Board* board,
						 QString name, QObject* parent)
	: AbstractPlayer(player, name, parent), controls(controls), board(board)
{

}

/**
 * Frees all used resources.
 */
HumanPlayer::~HumanPlayer()
{

}

/**
 * Notifies the board widget that it should allow the player to drop a token on the board.
 *
 * @param game Current game state.
 */
void HumanPlayer::requestMove(const QSharedPointer<const ::GUI::Game>& game)
{
	auto availableColumns = game->getRawGame()->getBoard()->getAvailableColumns();

	this->board->requestMove(availableColumns, this->controls);
}

/**
 * Informs the board widget that it should not allow the player to drop a token on the board
 * anymore.
 */
void HumanPlayer::abortMove()
{
	this->board->abortRequestMove();
}

/**
 * Returns the controls used by this player.
 *
 * @return Controls used by this player.
 */
HumanPlayer::Controls HumanPlayer::getControls() const
{
	return this->controls;
}

}
