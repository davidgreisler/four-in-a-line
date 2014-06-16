#include "Help.hpp"
#include "../Dialogs/About.hpp"

#include <QMessageBox>
#include <QAction>
#include <QEvent>
#include <QWidget>
#include <QMenu>
#include <QIcon>

namespace GUI
{
namespace Actions
{

/**
 * Creates a new help action container.
 *
 * @param parentWindow Parent window, used for dialogs.
 * @param parent Parent object.
 */
Help::Help(QWidget* parentWindow, QObject* parent) :
	QObject(parent), parentWindow(parentWindow)
{
	this->createActions();
	this->createMenu();
	this->retranslateUI();
}

/**
 * Frees all used resources.
 */
Help::~Help()
{

}

/**
 * Returns the about the game action.
 *
 * @return Action for displaying the about dialog.
 */
QAction* Help::getAboutAction() const
{
	return this->aboutAction;
}

/**
 * Returns the about Qt action.
 *
 * @return Action for showing a dialog about Qt.
 */
QAction* Help::getAboutQtAction() const
{
	return this->aboutQtAction;
}

/**
 * Returns the help menu.
 *
 * The help menu contains all help actions.
 *
 * @return The help menu.
 */
QMenu* Help::getMenu() const
{
	return this->menu.data();
}

/**
 * Shows a dialog with information about this game.
 */
void Help::showAboutDialog() const
{
	Dialogs::About aboutDialog(this->parentWindow);

	aboutDialog.exec();
}

/**
 * Shows a dialog with information about Qt.
 */
void Help::showAboutQtDialog() const
{
	QMessageBox::aboutQt(this->parentWindow);
}

/**
 * Create all actions and connect them.
 */
void Help::createActions()
{
	QIcon aboutIcon;
	aboutIcon.addFile(":/icons/fatcow/16x16/information.png", QSize(16, 16));
	aboutIcon.addFile(":/icons/fatcow/32x32/information.png", QSize(32, 32));
	this->aboutAction = new QAction(aboutIcon, "", this);
	this->connect(this->aboutAction, &QAction::triggered, this, &Help::showAboutDialog);

	this->aboutQtAction = new QAction("", this);
	this->connect(this->aboutQtAction, &QAction::triggered, this, &Help::showAboutQtDialog);
}

/**
 * Creates the help menu.
 */
void Help::createMenu()
{
	this->menu.reset(new QMenu(0));
	this->menu->addAction(this->aboutAction);
	this->menu->addAction(this->aboutQtAction);
}

/**
 * Retranslates all strings.
 */
void Help::retranslateUI()
{
	this->aboutAction->setText(tr("&About"));
	this->aboutAction->setStatusTip(tr("Shows information about this game."));

	this->aboutQtAction->setText(tr("&About Qt ..."));
	this->aboutQtAction->setStatusTip(tr("Shows information about Qt."));

	this->menu->setTitle(tr("&Help"));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
bool Help::event(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	return QObject::event(event);
}

}
}
