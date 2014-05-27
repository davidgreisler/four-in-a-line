#include "FourInALineSettings.hpp"

#include <QApplication>

/**
 * Creates a new settings container and reads all settings.
 *
 * @param parent Parent object.
 */
FourInALineSettings::FourInALineSettings(QObject *parent) :
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
FourInALineSettings::~FourInALineSettings()
{

}

/**
 * Returns application settings.
 *
 * @return Application settings.
 */
Settings::Application* FourInALineSettings::getApplicationSettings() const
{
	return this->applicationSettings;
}

/**
 * Returns view settings.
 *
 * @return View settings.
 */
Settings::View* FourInALineSettings::getViewSettings() const
{
	return this->viewSettings;
}

/**
 * Reads all settings and emits changed().
 */
void FourInALineSettings::read()
{
	this->applicationSettings->read();
	this->viewSettings->read();

	emit this->changed();
}

/**
 * Emits changed().
 */
void FourInALineSettings::apply()
{
	emit this->changed();
}

/**
 * Saves all settings and emits saved().
 */
void FourInALineSettings::save()
{
	this->applicationSettings->save();
	this->viewSettings->save();

	emit this->saved();
}
