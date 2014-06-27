#include "FourInALine.hpp"

#include <QApplication>

namespace Settings
{

/**
 * Creates a new settings container and reads all settings.
 *
 * @param parent Parent object.
 */
FourInALine::FourInALine(QObject *parent) :
	QObject(parent)
{
	QString organization = QApplication::organizationName();
	QString applicationName = QApplication::applicationName();
	this->settings = QSharedPointer<QSettings>(new QSettings(organization, applicationName));

	this->applicationSettings = new Settings::Application(this->settings, this);
	this->viewSettings = new Settings::View(this->settings, this);

	this->read();
}

/**
 * Frees all used resources.
 */
FourInALine::~FourInALine()
{

}

/**
 * Returns application settings.
 *
 * @return Application settings.
 */
Application* FourInALine::getApplicationSettings() const
{
	return this->applicationSettings;
}

/**
 * Returns view settings.
 *
 * @return View settings.
 */
View* FourInALine::getViewSettings() const
{
	return this->viewSettings;
}

/**
 * Reads all settings and emits changed().
 */
void FourInALine::read()
{
	this->applicationSettings->read();
	this->viewSettings->read();

	emit this->changed();
}

/**
 * Emits changed().
 */
void FourInALine::apply()
{
	emit this->changed();
}

/**
 * Saves all settings and emits saved().
 */
void FourInALine::save()
{
	this->applicationSettings->save();
	this->viewSettings->save();

	emit this->saved();
}

}
