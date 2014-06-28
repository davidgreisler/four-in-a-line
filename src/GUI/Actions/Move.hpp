#ifndef GUI_ACTIONS_MOVE_HPP
#define GUI_ACTIONS_MOVE_HPP

#include <QObject>
#include <QScopedPointer>

class QWidget;
class QMenu;
class QAction;

namespace GUI
{

class GameView;

namespace Actions
{

/**
 * Contains actions regarding game moves, like undo/show hint, etc.
 *
 * Provides an action for undoing the last move, and an action for showing a hint for the next move.
 */
class Move : public QObject
{
		Q_OBJECT
	public:
		explicit Move(::GUI::GameView* gameView, QWidget* parentWindow,
					  QObject *parent = 0);
		virtual ~Move();

		QAction* getUndoAction() const;
		QAction* getHintAction() const;

		QMenu* getMenu() const;

	signals:

	public slots:
		void updateActions();

	private:
		Q_DISABLE_COPY(Move)

		void createActions();
		void createMenu();
		void retranslateUI();
		bool event(QEvent* event);

		/**
		 * Game view, used to invoke undo/show hint actions.
		 */
		::GUI::GameView* gameView;

		/**
		 * Parent window, used for dialogs.
		 */
		QWidget* parentWindow;

		/**
		 * Undos the last move made by the player.
		 */
		QAction* undoAction;

		/**
		 * Displays a hint for the player.
		 */
		QAction* hintAction;

		/**
		 * Menu containing the move actions.
		 */
		QScopedPointer<QMenu> menu;
};

}
}

#endif // GUI_ACTIONS_MOVE_HPP
