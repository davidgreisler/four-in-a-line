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
	AbstractSettings(FourInALine::CreateSettings(), parent)
{
	this->applicationSettings = new Settings::Application(this->getSettings(), this);
	this->viewSettings = new Settings::View(this->getSettings(), this);

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
 * Creates an instance of QSettings for the application.
 *
 * @return Shared pointer to QSettings object.
 */
QSharedPointer<QSettings> FourInALine::CreateSettings()
{
	auto organization = QApplication::organizationName();
	auto applicationName = QApplication::applicationName();
	auto settings = QSharedPointer<QSettings>::create(organization, applicationName);

	return settings;
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
