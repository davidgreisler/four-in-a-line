#ifndef CONNECTFOUR_HPP
#define CONNECTFOUR_HPP

#include <QApplication>
#include <QMap>
#include <QString>
#include <QTranslator>

class ConnectFourSettings;

/**
 * Sets up application at start and contains frequently used objects.
 */
class ConnectFour : public QApplication
{
	public:
		ConnectFour(int& argc, char** argv);
		virtual ~ConnectFour();

		static ConnectFour* getInstance();

		ConnectFourSettings* getSettings() const;

		QMap<QString, QString> getAvailableLanguages() const;
		void setLanguage(QString locale);
		QString getLanguage() const;

	private:
		/**
		 * The application's settings.
		 */
		ConnectFourSettings* settings;

		/**
		 * The current language name/locale.
		 */
		QString currentLanguage;

		/**
		 * Translator for QT's dialogs, etc.
		 */
		QTranslator qtTranslator;

		/**
		 * Translator for the ConnectFour application.
		 */
		QTranslator appTranslator;
};

#endif // CONNECTFOUR_HPP
