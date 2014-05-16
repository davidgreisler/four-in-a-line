#ifndef CONNECTFOURSETTINGS_HPP
#define CONNECTFOURSETTINGS_HPP

#include "Settings/Application.hpp"
#include "Settings/View.hpp"

#include <QObject>

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
class ConnectFourSettings : public QObject
{
		Q_OBJECT
	public:
		explicit ConnectFourSettings(QObject *parent = 0);
		virtual ~ConnectFourSettings();

		void read();
		void apply();
		void save();

		Settings::Application* getApplicationSettings() const;
		Settings::View* getViewSettings() const;

	signals:
		/**
		 * Emitted when all settings are applied.
		 */
		void changed();

		/**
		 * Emitted when all settings are saved.
		 */
		void saved();

	public slots:

	private:
		/**
		 * Key/value storage for the settings.
		 */
		QSharedPointer<QSettings> settings;

		/**
		 * Application settings like GUI language.
		 */
		Settings::Application* applicationSettings;

		/**
		 * View settings.
		 */
		Settings::View* viewSettings;
};

#endif // CONNECTFOURSETTINGS_HPP
