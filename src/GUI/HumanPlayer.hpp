#ifndef GUI_HUMANPLAYER_HPP
#define GUI_HUMANPLAYER_HPP

#include "AbstractPlayer.hpp"

namespace GUI
{

namespace Widgets
{
class Board;
}

/**
 * A human player.
 *
 * This player uses the game board widget to get the next move from the user using the controls
 * given during construction.
 *
 * It is possible to configure which controls the user can use to drop tokens on the board, so that
 * one player can play with the mouse and the other with the keyboard if they want that.
 */
class HumanPlayer : public AbstractPlayer
{
		Q_OBJECT
	public:
		/**
		 * Which controls the user can use to play the game.
		 */
		enum class Controls : int {
			KEYBOARD,           ///< Keyboard controls.
			MOUSE,              ///< Mouse controls.
			MOUSE_AND_KEYBOARD  ///< Keyboard and mouse controls.
		};

		explicit HumanPlayer(::Game::FourInALine::Game::PlayerType player, Controls controls,
							 Widgets::Board* board, QString name = QString(""), QObject *parent = 0);
		virtual ~HumanPlayer();

		virtual void requestMove(const QSharedPointer<const ::GUI::Game>& game);

		virtual void abortMove();

		Controls getControls() const;

	private:
		/**
		 * What controls does this player use?
		 */
		Controls controls;

		/**
		 * Game board, used to request a move.
		 */
		Widgets::Board* board;
};

}

Q_DECLARE_METATYPE(GUI::HumanPlayer::Controls)

#endif // GUI_HUMANPLAYER_HPP
