#ifndef SETTINGS_SOUND_HPP
#define SETTINGS_SOUND_HPP

#include "AbstractSettings.hpp"

namespace Settings
{

/**
 * Contains sound settings.
 *
 * This class allows to change sound settings. It is possible to retrieve and set the volume with
 * setVolume() and getVolume().
 *
 * The sound engine can be disabled/enabled with setSoundEnabled().
 */
class Sound : public AbstractSettings
{
		Q_OBJECT
	public:
		explicit Sound(QSharedPointer<QSettings> settings, QObject *parent = 0);
		virtual ~Sound();

		virtual void read() override;
		virtual void save() override;

		bool isSoundEnabled() const;
		void setSoundEnabled(bool enabled);

		float getVolume() const;
		void setVolume(float volume);

	private:
		Q_DISABLE_COPY(Sound)

		/**
		 * Whether sound is enabled or not.
		 */
		bool soundEnabled;

		/**
		 * The sound volume (0.0 - 1.0).
		 */
		float volume;
};

}

#endif // SETTINGS_SOUND_HPP
