#ifndef HELP_HPP
#define HELP_HPP

#include <QObject>
#include <QScopedPointer>

class QAction;
class QMenu;
class QAction;
class QWidget;

namespace GUI
{
namespace Actions
{

/**
 * Contains actions with information about the program/usage information.
 *
 * Provides actions to show a dialog about the program and a dialog about Qt.
 */
class Help : public QObject
{
		Q_OBJECT
	public:
		explicit Help(QWidget* parentWindow, QObject *parent = 0);
		virtual ~Help();

		QAction* getAboutAction() const;
		QAction* getAboutQtAction() const;

		QMenu* getMenu() const;

	signals:

	public slots:
		void showAboutDialog() const;
		void showAboutQtDialog() const;

	private:
		Q_DISABLE_COPY(Help)

		void createActions();
		void createMenu();
		void retranslateUI();
		bool event(QEvent* event);

		/**
		 * Parent window, used for dialogs.
		 */
		QWidget* parentWindow;

		/**
		 * Displays a dialog with information about the game.
		 */
		QAction* aboutAction;

		/**
		 * Displays a dialog with information about qt.
		 */
		QAction* aboutQtAction;

		/**
		 * Menu containing the help actions.
		 */
		QScopedPointer<QMenu> menu;
};

}
}

#endif // HELP_HPP
