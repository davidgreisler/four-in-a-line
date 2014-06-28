#ifndef GUI_ACTIONS_REPLAY_HPP
#define GUI_ACTIONS_REPLAY_HPP

#include <QObject>
#include <QScopedPointer>

class QMenu;
class QWidget;
class QAction;

namespace GUI
{

class GameView;
class ReplayView;

namespace Actions
{

/**
 * Contains replay actions, like next/previous move, load/save replay, etc.
 *
 * Provides actions for loading/saving replays, and for stepping to the next/previous move or
 * jumping back to start/end.
 */
class Replay : public QObject
{
		Q_OBJECT
	public:
		explicit Replay(::GUI::GameView* gameView,
						::GUI::ReplayView* replayView, QWidget* parentWindow,
						QObject *parent = 0);
		virtual ~Replay();

		QAction* getLoadReplayAction() const;
		QAction* getSaveReplayAction() const;

		QAction* getNextMoveAction() const;
		QAction* getPreviousMoveAction() const;

		QAction* getJumpToStartAction() const;
		QAction* getJumpToEndAction() const;

		QMenu* getMenu() const;

	signals:

	public slots:
		void updateActions();

	private:
		Q_DISABLE_COPY(Replay)

		void createActions();
		void createMenu();
		void retranslateUI();
		bool event(QEvent* event);

		/**
		 * Parent window, used for dialogs.
		 */
		QWidget* parentWindow;

		/**
		 * Game view, used to save a replay.
		 */
		::GUI::GameView* gameView;

		/**
		 * Replay view, used to load replays and navigate in the replays.
		 */
		::GUI::ReplayView* replayView;

		/**
		 * Loads a replay.
		 */
		QAction* loadReplayAction;

		/**
		 * Saves a replay of the current game.
		 */
		QAction* saveReplayAction;

		/**
		 * Steps to the next move.
		 */
		QAction* nextMoveAction;

		/**
		 * Steps to the previous move.
		 */
		QAction* previousMoveAction;

		/**
		 * Jumps to the start of the replay.
		 */
		QAction* jumpToStartAction;

		/**
		 * Jumps to the end of the replay.
		 */
		QAction* jumpToEndAction;

		/**
		 * Menu containing the replay actions.
		 */
		QScopedPointer<QMenu> menu;
};

}
}

#endif // GUI_ACTIONS_REPLAY_HPP
