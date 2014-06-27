#include "AbstractSettings.hpp"

namespace Settings
{

/**
 * Sets parent on the QObject and stores the settings object.
 *
 * @param settings Settings object to use.
 * @param parent Parent object.
 */
AbstractSettings::AbstractSettings(QSharedPointer<QSettings> settings, QObject* parent) :
    QObject(parent), settings(settings)
{

}

/**
 * Frees all used resources.
 */
AbstractSettings::~AbstractSettings()
{

}

/**
 * Applies changes to the settings (emits changed()).
 */
void AbstractSettings::apply()
{
	emit AbstractSettings::changed();
}

/**
 * Returns the application's settings used to store/retrieve key/value pairs.
 *
 * @return Settings.
 */
const QSharedPointer<QSettings>& AbstractSettings::getSettings() const
{
	return this->settings;
}

}
