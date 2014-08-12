#include "Sound.hpp"

#include <stdexcept>

namespace Settings
{

/**
 * Creates new soudn settings container and reads settings from given key/value storage.
 *
 * @param settings Key/value storage to use for storing/retrieving settings.
 * @param parent Parent object.
 */
Sound::Sound(QSharedPointer<QSettings> settings, QObject *parent) :
    AbstractSettings(settings, parent)
{
	this->read();
}

/**
 * Frees all used resources.
 */
Sound::~Sound()
{

}

void Sound::read()
{
	this->soundEnabled = this->getSettings()->value("sound/enabled", true).toBool();
	this->volume = this->getSettings()->value("sound/volume", 1.0f).toFloat();

	emit this->changed();
}

void Sound::save()
{
	this->getSettings()->setValue("sound/enabled", this->soundEnabled);
	this->getSettings()->setValue("sound/volume", this->volume);

	emit this->saved();
}

/**
 * Returns whether sound is enabled or not.
 *
 * @return When sound is enabled true, otherwise false.
 */
bool Sound::isSoundEnabled() const
{
	return this->soundEnabled;
}

/**
 * Enables/disables sound.
 *
 * @param enabled To enable sound true, otherwise false.
 */
void Sound::setSoundEnabled(bool enabled)
{
	this->soundEnabled = enabled;
}

/**
 * Returns the current volume.
 *
 * @return Volume between 0.0 and 1.0.
 */
float Sound::getVolume() const
{
	return this->volume;
}

/**
 * Sets the volume to the given volume.
 *
 * @param volume The new volume, between 0.0 and 1.0.
 */
void Sound::setVolume(float volume)
{
	if (volume < 0.0f || volume > 1.0f)
	{
		throw std::runtime_error("Volume must be between 0.0 and 1.0.");
	}

	this->volume = volume;
}

}
