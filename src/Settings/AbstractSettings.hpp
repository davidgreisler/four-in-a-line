#ifndef ABSTRACTSETTINGS_HPP
#define ABSTRACTSETTINGS_HPP

#include <QObject>
#include <QSharedPointer>
#include <QSettings>

namespace Settings
{

/**
 * Abstract base class for settings containers.
 *
 * It is possible to read the configuration from the key/value storage with read(), store the
 * current configuration with save() or apply the settings with apply(). The read() and apply()
 * methods emit the changed() signal, save() emits the saved() signal.
 */
class AbstractSettings : public QObject
{
		Q_OBJECT
	public:
		explicit AbstractSettings(QSharedPointer<QSettings> settings, QObject* parent = 0);
		virtual ~AbstractSettings();

		/**
		 * Read settings from the key/value storage and emit changed().
		 */
		virtual void read() = 0;

		/**
		 * Apply settings (emit changed()).
		 */
		virtual void apply();

		/**
		 * Apply and save the settings to the key/value storage.
		 */
		virtual void save() = 0;

	signals:
		/**
		 * Emitted when the settings have changed and were applied.
		 */
		void changed();

		/**
		 * Emitted when the settings have been saved.
		 */
		void saved();

	protected:
		const QSharedPointer<QSettings>& getSettings() const;

	private:
		Q_DISABLE_COPY(AbstractSettings)

		/**
		 * Settings instance used to store/retrieve settings.
		 */
		QSharedPointer<QSettings> settings;

};

}

#endif // ABSTRACTSETTINGS_HPP
