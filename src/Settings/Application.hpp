#ifndef SETTINGS_APPLICATION_HPP
#define SETTINGS_APPLICATION_HPP

#include "AbstractSettings.hpp"

namespace Settings
{

/**
 * Application settings like the GUI language.
 */
class Application : public AbstractSettings
{
		Q_OBJECT
	public:
		explicit Application(QSharedPointer<QSettings> settings, QObject *parent = 0);

		QString getLanguage() const;
		void setLanguage(QString locale);

		virtual void read() override;
		virtual void save() override;

	private:
		Q_DISABLE_COPY(Application)

		/**
		 * The application language (locale).
		 */
		QString language;
};

}

#endif // SETTINGS_APPLICATION_HPP
