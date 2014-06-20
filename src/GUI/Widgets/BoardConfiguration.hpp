#ifndef GUI_WIDGETS_BOARDCONFIGURATION_HPP
#define GUI_WIDGETS_BOARDCONFIGURATION_HPP

#include <QGroupBox>

class QWidget;
class QFormLayout;
class QSpinBox;
class QLabel;
class QHBoxLayout;

namespace GUI
{
namespace Widgets
{

/**
 * Widget for configuring the game board (number of rows and columns).
 *
 * This widget provides a form to enter a number of rows and columns for a game board. It is possible
 * to specify minimum/maximum values for the number of rows and the number of columns.
 */
class BoardConfiguration : public QGroupBox
{
		Q_OBJECT
	public:
		explicit BoardConfiguration(QWidget* parent = 0);
		virtual ~BoardConfiguration();

		void setNumberOfRows(unsigned int nRows);
		unsigned int getNumberOfRows() const;

		void setMinimumNumberOfRows(unsigned int nMinimumRows);
		unsigned int getMinimumNumberOfRows() const;

		void setMaximumNumberOfRows(unsigned int nMaximumRows);
		unsigned int getMaximumNumberOfRows() const;

		void setNumberOfColumns(unsigned int nColumns);
		unsigned int getNumberOfColumns() const;

		void setMinimumNumberOfColumns(unsigned int nMinimumColumns);
		unsigned int getMinimumNumberOfColumns() const;

		void setMaximumNumberOfColumns(unsigned int nMaximumColumns);
		unsigned int getMaximumNumberOfColumns() const;

	private:
		Q_DISABLE_COPY(BoardConfiguration)

		void retranslateUI();
		bool event(QEvent* event);

		/**
		 * Main layout.
		 */
		QHBoxLayout* layout;

		/**
		 * Form layout for the rows input.
		 */
		QFormLayout* rowsLayout;

		/**
		 * Label for the number of rows input.
		 */
		QLabel* rowsLabel;

		/**
		 * Spin box for the number of rows.
		 */
		QSpinBox* rowsSpinBox;

		/**
		 * Form layout for the columns input.
		 */
		QFormLayout* columnsLayout;

		/**
		 * Label for the number of columns input.
		 */
		QLabel* columnsLabel;

		/**
		 * Spin box for the number of columns.
		 */
		QSpinBox* columnsSpinBox;
};

}
}

#endif // GUI_WIDGETS_BOARDCONFIGURATION_HPP
