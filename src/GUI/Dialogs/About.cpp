#include "About.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QEvent>
#include <QPixmap>

namespace GUI
{
namespace Dialogs
{

/**
 * Creates a new about dialog.
 *
 * @param parent Parent widget, the dialog will be centered above this widget if parent is
 *        not null.
 */
About::About(QWidget *parent) :
    QDialog(parent)
{
	this->verticalLayout = new QVBoxLayout(this);

	this->horizontalLayout = new QHBoxLayout;
	this->horizontalLayout->setSpacing(20);
	this->verticalLayout->addLayout(this->horizontalLayout);

	this->iconLabel = new QLabel(this);
	this->iconLabel->setPixmap(QPixmap(":/icons/fourinaline/128x128/application_icon.png"));
	this->horizontalLayout->addWidget(this->iconLabel);

	this->textLabel = new QLabel(this);
	this->textLabel->setWordWrap(true);
	this->textLabel->setOpenExternalLinks(true);

	this->horizontalLayout->addWidget(this->textLabel);

	this->buttonBox = new QDialogButtonBox(this);
	this->buttonBox->setOrientation(Qt::Horizontal);
	this->buttonBox->setStandardButtons(QDialogButtonBox::Close);
	this->verticalLayout->addWidget(this->buttonBox);

	this->connect(this->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

	this->retranslateUI();
}

/**
 * Frees all used resources.
 */
About::~About()
{

}

/**
 * Retranslates all strings.
 */
void About::retranslateUI()
{
	this->setWindowTitle(tr("About four in a line"));

	this->textLabel->setText(tr(
	    "<h1>Four in a line</h1>"
	    "<b>Copyright (c) 2014 David Greisler und Simon Mühlichen.</b>"
	    "<p>Four in a line is a two-player game in which two players first select a color and then "
	    "take turns dropping a token of their color from the top into a grid. "
	    "The token falls straight down, occupying the lowest free cell in the grid. "
	    "The first player who has four tokens in a row, either horizontally/vertically or "
	    "diagonally, wins the game.</p>"

	    "<p>It is possible to play the game with two human players, either locally or over the "
	    "network, or with  one human player playing against a computer player. When playing over "
	    "the network, the players can communicate using an in-game chat. The number of "
	    "won/lost/drawn games of each player are stored in a highscore list.</p>"

	    "<p>The program was created within the scope of an assignment for the course MM-EMS.</p>"

	    "<hr />"

	    "<p>Four in a line is free software and is distributed under the terms of the <a"
	    "href=\"http://opensource.org/licenses/MIT\">MIT License</a>.</p>"

	    "<p>This program uses some of the <a href=\"http://www.fatcow.com/free-icons\">"
	    "Farm-Fresh Web Icons</a> from FatCow. They are licensed under a <a "
	    "href=\"http://creativecommons.org/licenses/by/3.0/us/\"> "
	    "Creative Commons Attribution 3.0 License</a>. Some icons were modified.</p>"

	    "<p>For more information see the README.md file.</p>"
	));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
void About::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	QDialog::changeEvent(event);
}

}
}
