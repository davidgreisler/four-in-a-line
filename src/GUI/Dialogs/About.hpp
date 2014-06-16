#ifndef GUI_DIALOGS_ABOUT_HPP
#define GUI_DIALOGS_ABOUT_HPP

#include <QDialog>

class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QDialogButtonBox;
class QEvent;

namespace GUI
{
namespace Dialogs
{

/**
 * Shows information about the program and the authors.
 */
class About : public QDialog
{
		Q_OBJECT
	public:
		explicit About(QWidget *parent = 0);
		virtual ~About();

	private:
		Q_DISABLE_COPY(About)

		void changeEvent(QEvent* event);
		void retranslateUI();

		/**
		 * Main layout.
		 */
		QVBoxLayout* verticalLayout;

		/**
		 * Horizontal layout for the icon and about text.
		 */
		QHBoxLayout* horizontalLayout;

		/**
		 * Displays the program icon.
		 */
		QLabel* iconLabel;

		/**
		 * A text about the program.
		 */
		QLabel* textLabel;

		/**
		 * Contains a button to close the dialog.
		 */
		QDialogButtonBox* buttonBox;
};

}
}

#endif // GUI_DIALOGS_ABOUT_HPP
