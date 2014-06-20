#include "BoardConfiguration.hpp"

#include <QSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <QEvent>
#include <QHBoxLayout>

namespace GUI
{
namespace Widgets
{

/**
 * Creates a new board configuration widget.
 *
 * @param parent Parent widget.
 */
BoardConfiguration::BoardConfiguration(QWidget *parent) :
	QGroupBox(parent)
{
	this->layout = new QHBoxLayout;
	this->setLayout(this->layout);

	this->rowsLayout = new QFormLayout;
	this->layout->addLayout(this->rowsLayout);

	this->rowsLabel = new QLabel(this);
	this->rowsSpinBox = new QSpinBox(this);
	this->rowsLayout->addRow(this->rowsLabel, this->rowsSpinBox);

	this->columnsLayout = new QFormLayout;
	this->layout->addLayout(this->columnsLayout);

	this->columnsLabel = new QLabel(this);
	this->columnsSpinBox = new QSpinBox(this);
	this->columnsLayout->addRow(this->columnsLabel, this->columnsSpinBox);

	this->retranslateUI();

	this->setMinimumNumberOfColumns(0);
	this->setMinimumNumberOfRows(0);
}

/**
 * Frees all used resources.
 */
BoardConfiguration::~BoardConfiguration()
{

}

/**
 * Sets the number of rows on the board to the given value.
 *
 * @param nRows Number of rows.
 */
void BoardConfiguration::setNumberOfRows(unsigned int nRows)
{
	this->rowsSpinBox->setValue(nRows);
}

/**
 * Returns the number of rows.
 *
 * @return Number of rows.
 */
unsigned int BoardConfiguration::getNumberOfRows() const
{
	return this->rowsSpinBox->value();
}

/**
 * Sets the minimum number of rows.
 *
 * @param nMinimumRows Minimum number of rows.
 */
void BoardConfiguration::setMinimumNumberOfRows(unsigned int nMinimumRows)
{
	this->rowsSpinBox->setMinimum(nMinimumRows);
}

/**
 * Returns the minimum number of rows.
 *
 * @return Minimum number of rows.
 */
unsigned int BoardConfiguration::getMinimumNumberOfRows() const
{
	return this->rowsSpinBox->minimum();
}

/**
 * Sets the maximum number of rows.
 *
 * @param nMaximumRows Maximum number of rows.
 */
void BoardConfiguration::setMaximumNumberOfRows(unsigned int nMaximumRows)
{
	this->rowsSpinBox->setMaximum(nMaximumRows);
}

/**
 * Returns the maximum number of rows.
 *
 * @return Maximum number of rows.
 */
unsigned int BoardConfiguration::getMaximumNumberOfRows() const
{
	return this->rowsSpinBox->maximum();
}

/**
 * Sets the number of columns.
 *
 * @param nColumns Number of columns.
 */
void BoardConfiguration::setNumberOfColumns(unsigned int nColumns)
{
	this->columnsSpinBox->setValue(nColumns);
}

/**
 * Returns the number of columns.
 *
 * @return Number of columns.
 */
unsigned int BoardConfiguration::getNumberOfColumns() const
{
	return this->columnsSpinBox->value();
}

/**
 * Sets the minimum number of columns.
 *
 * @param nMinimumColumns Minimum number of columns.
 */
void BoardConfiguration::setMinimumNumberOfColumns(unsigned int nMinimumColumns)
{
	this->columnsSpinBox->setMinimum(nMinimumColumns);
}

/**
 * Returns the minimum amount of columns.
 *
 * @return Minimum amount of columns.
 */
unsigned int BoardConfiguration::getMinimumNumberOfColumns() const
{
	return this->columnsSpinBox->minimum();
}

/**
 * Sets the maximum amount of columns to the given value.
 *
 * @param nMaximumColumns Maximum amount of columns.
 */
void BoardConfiguration::setMaximumNumberOfColumns(unsigned int nMaximumColumns)
{
	this->columnsSpinBox->setMaximum(nMaximumColumns);
}

/**
 * Returns the maximum amount of columns that can be entered.
 *
 * @return Maximum amount of columns.
 */
unsigned int BoardConfiguration::getMaximumNumberOfColumns() const
{
	return this->columnsSpinBox->maximum();
}

/**
 * Retranslates all strings.
 */
void BoardConfiguration::retranslateUI()
{
	this->setTitle(this->tr("Board"));
	this->rowsLabel->setText(this->tr("Number of rows"));
	this->columnsLabel->setText(this->tr("Number of columns"));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
bool BoardConfiguration::event(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	return QGroupBox::event(event);
}

}
}
