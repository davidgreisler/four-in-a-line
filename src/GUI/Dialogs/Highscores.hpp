#ifndef GUI_DIALOGS_HIGHSCORES_HPP
#define GUI_DIALOGS_HIGHSCORES_HPP

#include <QDialog>

class QVBoxLayout;
class QDialogButtonBox;
class QPushButton;
class QTreeWidget;

namespace GUI
{
namespace Dialogs
{

/**
 * Dialog showing a list with all entries from the highscore database.
 *
 * It is also possible to print the highscore list.
 */
class Highscores : public QDialog
{
		Q_OBJECT
	public:
		explicit Highscores(QWidget *parent = 0);
		virtual ~Highscores();

	public slots:
		void printHighscores();

	private:
		Q_DISABLE_COPY(Highscores)

		void changeEvent(QEvent* event);
		void retranslateUI();

		void clearList();
		void loadList();

		/**
		 * Layout of the dialog.
		 */
		QVBoxLayout* layout;

		/**
		 * Tree widget containing the highscore entries.
		 */
		QTreeWidget* highscoreTreeWidget;

		/**
		 * Dialog button box containing the accept/print buttons.
		 */
		QDialogButtonBox* buttonBox;

		/**
		 * Button for closing the dialog.
		 */
		QPushButton* acceptButton;

		/**
		 * Button for printing the dialog.
		 */
		QPushButton* printButton;
};

}
}

#endif // GUI_DIALOGS_HIGHSCORES_HPP
