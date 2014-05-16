#ifndef MAINMENUBAR_HPP
#define MAINMENUBAR_HPP

#include "Actions/Game.hpp"

#include <QMenuBar>

namespace GUI
{

/**
 * Menu bar for the main window.
 */
class MainMenuBar : public QMenuBar
{
		Q_OBJECT
	public:
		explicit MainMenuBar(Actions::Game* gameActions, QWidget *parent = 0);
		virtual ~MainMenuBar();

	signals:

	public slots:

	private:
		Q_DISABLE_COPY(MainMenuBar)

		void retranslateUI();

		/**
		 * Game menu containing start new game, load/save game, exit, etc.
		 */
		QMenu* gameMenu;

		/**
		 * Contains game actions.
		 */
		Actions::Game* gameActions;
};

}

#endif // MAINMENUBAR_HPP
