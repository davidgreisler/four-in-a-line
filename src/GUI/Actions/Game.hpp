#ifndef GUI_ACTIONS_GAME_HPP
#define GUI_ACTIONS_GAME_HPP

#include <QObject>
#include <QScopedPointer>

class QAction;
class QMenu;
class QWidget;

namespace GUI
{
namespace Actions
{

/**
 * Actions concerning the game, e.g. start new game, save/load game, exit.
 *
 * Provides actions for starting a new game, ending the current game, loading/saving the game,
 * showing the highscore table and exiting the program.
 */
class Game : public QObject
{
		Q_OBJECT
	public:
		explicit Game(QWidget* parentWindow, QObject *parent = 0);
		virtual ~Game();

		QAction* getNewGameAction() const;
		QAction* getEndGameAction() const;

		QAction* getSaveGameAction() const;
		QAction* getSaveGameAsAction() const;
		QAction* getLoadGameAction() const;

		QAction* getShowHighscoresAction() const;

		QAction* getExitAction() const;

		QMenu* getMenu() const;

	signals:

	public slots:
		void exit();

	private:
		Q_DISABLE_COPY(Game)

		void createActions();
		void createMenu();
		void retranslateUI();
		bool event(QEvent* event);

		/**
		 * Parent window, used for dialogs.
		 */
		QWidget* parentWindow;

		/**
		 * Starts a new game.
		 */
		QAction* newGameAction;

		/**
		 * Ends the current game.
		 */
		QAction* endGameAction;

		/**
		 * Loads a game.
		 */
		QAction* loadGameAction;

		/**
		 * Saves the current game.
		 */
		QAction* saveGameAction;

		/**
		 * Saves the current game under a new path.
		 */
		QAction* saveGameAsAction;

		/**
		 * Shows highscores dialog.
		 */
		QAction* showHighscoresAction;

		/**
		 * Ends program execution.
		 */
		QAction* exitAction;

		/**
		 * Menu containing the game actions.
		 */
		QScopedPointer<QMenu> menu;
};

}
}

#endif // GUI_ACTIONS_GAME_HPP
