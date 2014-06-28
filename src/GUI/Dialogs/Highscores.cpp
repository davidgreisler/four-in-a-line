#include "Highscores.hpp"

#include <QTreeWidgetItemIterator>
#include <QEvent>
#include <QDialogButtonBox>
#include <QTreeWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>
#include <QTextStream>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>

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
	QString htmlString;
	QTextDocument document;
	QPrinter printer;
	QTextStream htmlStream(&htmlString);

	htmlStream << "<html>\n"
	           << "  <head>\n"
	           << "    <title>" << this->tr("Highscore list") << "</title>\n"
	           << "  </head>\n"
	           << "  <body>\n"
	           << "    <table border=\"1\">\n"
	           << "      <thead>\n"
	           << "        <tr>\n"
	           << "          <td>" << this->tr("Rank") << "</td>\n"
	           << "          <td>" << this->tr("Player name") << "</td>\n"
	           << "          <td>" << this->tr("Total games") << "</td>\n"
	           << "          <td>" << this->tr("Won games") << "</td>\n"
	           << "          <td>" << this->tr("Lost games") << "</td>\n"
	           << "          <td>" << this->tr("Draw games") << "</td>\n"
	           << "        </tr>\n"
	           << "      </thead>\n"
	           << "      <tbody>\n";

	for (QTreeWidgetItemIterator i(this->highscoreTreeWidget); *i; i++)
	{
		htmlStream << "        <tr>\n"
		           << "          <td>" << (*i)->text(0) << "</td>\n"
		           << "          <td>" << (*i)->text(1) << "</td>\n"
		           << "          <td>" << (*i)->text(2) << "</td>\n"
		           << "          <td>" << (*i)->text(3) << "</td>\n"
		           << "          <td>" << (*i)->text(4) << "</td>\n"
		           << "          <td>" << (*i)->text(5) << "</td>\n"
		           << "        </tr>\n";
	}

	htmlStream << "      </tbody>\n"
	           << "    </table>\n"
	           << "  </body>\n"
	           << "</html>\n";

	document.setHtml(htmlString);

	QPrintDialog dialog(&printer, this);
	dialog.setWindowTitle(this->tr("Print highscore list"));
	if (dialog.exec() == QDialog::Accepted)
	{
		document.print(&printer);
	}
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
