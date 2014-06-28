#ifndef GUI_WIDGETS_GAMECONFIGURATION_HPP
#define GUI_WIDGETS_GAMECONFIGURATION_HPP

#include "../../GameLogic/FourInALine/Game.hpp"

#include <QGroupBox>

class QFormLayout;
class QCheckBox;
class QLabel;
class QRadioButton;
class QEvent;

namespace GUI
{
namespace Widgets
{

/**
 * Widget for configuring general game settings.
 *
 * This widget provides a form to configure which player makes the first move, and whether the
 * game is saved to the highscore list, and whether hints/undo are allowed or not.
 *
 * Use setFirstMove() to set who makes the first move, getFirstMove() returns the player who makes
 * the first move.
 *
 * Whether the game result is saved in the highscore list can be queried with getSaveHighscore()
 * and set with setSaveHighscore(). The hint/undo functions can be enabled/disabled with
 * setAllowHint() and setAllowUndo(), retrieving the current values is possible with getAllowHint()
 * and getAllowUndo().
 *
 * There are methods for enabling/disabling the individual inputs in case they are not applicable.
 */
class GameConfiguration : public QGroupBox
{
		Q_OBJECT
	public:
		/**
		 * Type used for player ids.
		 */
		using PlayerIdType = ::GameLogic::FourInALine::Game::PlayerType;

		explicit GameConfiguration(QWidget* parent = 0);
		virtual ~GameConfiguration();

		void setFirstMove(PlayerIdType playerId);
		PlayerIdType getFirstMove() const;

		void setFirstMoveEnabled(bool enabled);
		bool isFirstMoveEnabled() const;

		void setSaveHighscore(bool saveHighscore);
		bool getSaveHighscore() const;

		void setSaveHighscoreEnabled(bool enabled);
		bool isSaveHighscoreEnabled() const;

		void setAllowHint(bool allowHint);
		bool getAllowHint() const;

		void setAllowHintEnabled(bool enabled);
		bool isAllowHintEnabled() const;

		void setAllowUndo(bool allowUndo);
		bool getAllowUndo() const;

		void setAllowUndoEnabled(bool enabled);
		bool isAllowUndoEnabled() const;

	private:
		Q_DISABLE_COPY(GameConfiguration)

		void retranslateUI();
		bool event(QEvent* event);

		/**
		 * The form layout.
		 */
		QFormLayout* formLayout;

		/**
		 * Label for the first move radio buttons.
		 */
		QLabel* firstMoveLabel;

		/**
		 * Radio button for the first player.
		 */
		QRadioButton* firstMovePlayerOneButton;

		/**
		 * Radio button for the second player.
		 */
		QRadioButton* firstMovePlayerTwoButton;

		/**
		 * Checkbox for saving the game to the highscore list.
		 */
		QCheckBox* saveHighscoreCheckBox;

		/**
		 * Checkbox for allowing use of the hint button.
		 */
		QCheckBox* allowHintCheckBox;

		/**
		 * Checkbox for allowing use of the undo button.
		 */
		QCheckBox* allowUndoCheckBox;
};

}
}

#endif // GUI_WIDGETS_GAMECONFIGURATION_HPP
