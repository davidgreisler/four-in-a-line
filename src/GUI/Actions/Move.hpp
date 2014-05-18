#ifndef MOVE_HPP
#define MOVE_HPP

#include <QObject>

class QAction;

namespace GUI
{
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
		explicit Move(QWidget* parentWindow, QObject *parent = 0);
		virtual ~Move();

		QAction* getUndoAction() const;
		QAction* getHintAction() const;

	signals:

	public slots:
		void undoLastMove();
		void showHint();

	private:
		Q_DISABLE_COPY(Move)

		void createActions();
		void retranslateUI();
		bool event(QEvent* event);

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
};

}
}

#endif // MOVE_HPP
