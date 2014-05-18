#ifndef HELP_HPP
#define HELP_HPP

#include <QObject>

class QAction;

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

	signals:

	public slots:
		void showAboutDialog() const;
		void showAboutQtDialog() const;

	private:
		Q_DISABLE_COPY(Help)

		void createActions();
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
};

}
}

#endif // HELP_HPP
