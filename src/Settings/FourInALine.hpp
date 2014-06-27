#ifndef SETTINGS_FOUR_IN_A_LINE_HPP
#define SETTINGS_FOUR_IN_A_LINE_HPP

#include "Application.hpp"
#include "View.hpp"

#include <QObject>

namespace Settings
{

/**
 * Stores and retrieves application settings and other information.
 *
 * The settings are stored in a configuration file and can be retrieved/modified through the getter
 * and setter methods of the provided settings containers.
 *
 * To permanently save the settings of all containers to the configuration, call the save() method,
 * use read() to read the settings for all containers from the configuration file. The apply()
 * method can be used to inform listeners about the changed settings.
 *
 * Use the read()/save()/apply() methods of the individual containers to read/save/apply only their
 * settings.
 */
class FourInALine : public QObject
{
		Q_OBJECT
	public:
		explicit FourInALine(QObject *parent = 0);
		virtual ~FourInALine();

		virtual void read();
		virtual void apply();
		virtual void save();

		Application* getApplicationSettings() const;
		View* getViewSettings() const;

	signals:
		/**
		 * Emitted when all settings are applied.
		 */
		void changed();

		/**
		 * Emitted when all settings are saved.
		 */
		void saved();

	private:
		/**
		 * Key/value storage for the settings.
		 */
		QSharedPointer<QSettings> settings;

		/**
		 * Application settings like GUI language.
		 */
		Application* applicationSettings;

		/**
		 * View settings.
		 */
		View* viewSettings;
};

}

#endif // SETTINGS_FOUR_IN_A_LINE_HPP
