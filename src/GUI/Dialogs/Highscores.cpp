#include "Highscores.hpp"

#include <QEvent>
#include <QDialogButtonBox>
#include <QTreeWidget>
#include <QPushButton>
#include <QVBoxLayout>

namespace GUI
{
namespace Dialogs
{

/**
 * Creates a new highscores dialog.
 *
 * @param parent Parent widget.
 */
Highscores::Highscores(QWidget *parent) :
    QDialog(parent)
{
	this->layout = new QVBoxLayout;
	this->setLayout(this->layout);

	this->highscoreTreeWidget = new QTreeWidget(this);
	this->highscoreTreeWidget->setSortingEnabled(true);
	this->highscoreTreeWidget->sortByColumn(0, Qt::AscendingOrder);
	this->highscoreTreeWidget->setSelectionMode(QAbstractItemView::NoSelection);
	this->layout->addWidget(this->highscoreTreeWidget);

	this->buttonBox = new QDialogButtonBox(this);
	this->layout->addWidget(this->buttonBox);

	this->acceptButton = new QPushButton(this);
	this->buttonBox->addButton(this->acceptButton, QDialogButtonBox::AcceptRole);
	this->connect(this->acceptButton, &QPushButton::clicked, this, &Highscores::accept);

	this->printButton = new QPushButton(this);
	this->buttonBox->addButton(this->printButton, QDialogButtonBox::ActionRole);
	this->connect(this->printButton, &QPushButton::clicked, this, &Highscores::printHighscores);

	this->loadList();
	this->retranslateUI();
}

/**
 * Frees all used resources.
 */
Highscores::~Highscores()
{

}

/**
 * Shows a print dialog allowing the user to print the highscore list.
 */
void Highscores::printHighscores()
{
	// @todo Implement.
}

/**
 * Retranslates all strings.
 */
void Highscores::retranslateUI()
{
	this->setWindowTitle(this->tr("Highscores"));
	this->acceptButton->setText(this->tr("OK"));
	this->printButton->setText(this->tr("Print"));

	// Setup tree view.

	QTreeWidgetItem* headerItem = this->highscoreTreeWidget->headerItem();
	headerItem->setText(0, this->tr("#"));
	headerItem->setText(1, this->tr("Player name"));
	headerItem->setText(2, this->tr("Total"));
	headerItem->setText(3, this->tr("Won"));
	headerItem->setText(4, this->tr("Lost"));
	headerItem->setText(5, this->tr("Draw"));
}

/**
 * Clears the highscore list/removes all items.
 */
void Highscores::clearList()
{
	this->highscoreTreeWidget->clear();
}

/**
 * Populates the list of highscores with entries from the highscore database.
 */
void Highscores::loadList()
{
	this->clearList();

	// @todo Implement this.

	QTreeWidgetItem* item = new QTreeWidgetItem(this->highscoreTreeWidget);
	item->setText(0, "1");
	item->setText(1, "Player 1");
	item->setText(2, "10");
	item->setText(3, "5");
	item->setText(4, "4");
	item->setText(5, "1");

	this->highscoreTreeWidget->addTopLevelItem(item);

	item = new QTreeWidgetItem(this->highscoreTreeWidget);
	item->setText(0, "2");
	item->setText(1, "Player 2");
	item->setText(2, "10");
	item->setText(3, "4");
	item->setText(4, "6");
	item->setText(5, "1");

	this->highscoreTreeWidget->addTopLevelItem(item);
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
void Highscores::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	QDialog::changeEvent(event);
}

}
}
