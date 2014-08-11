#ifndef APP_FOUR_IN_A_LINE_HPP
#define APP_FOUR_IN_A_LINE_HPP

#include <QApplication>
#include <QMap>
#include <QString>
#include <QTranslator>

namespace Settings
{
	class FourInALine;
}

/**
 * Sets up application at start and contains frequently used objects.
 */
class FourInALine : public QApplication
{
		Q_OBJECT
	public:
		FourInALine(int& argc, char** argv);
		virtual ~FourInALine();

		static FourInALine* getInstance();

		Settings::FourInALine* getSettings() const;

		QMap<QString, QString> getAvailableLanguages() const;
		void setLanguage(QString locale);
		QString getLanguage() const;

	signals:
		/**
		 * Emitted when the language was changed.
		 */
		void languageChanged();

	private slots:
		void updateLanguage();

	private:
		Q_DISABLE_COPY(FourInALine)

		/**
		 * The application's settings.
		 */
		Settings::FourInALine* settings;

		/**
		 * The current language name/locale.
		 */
		QString currentLanguage;

		/**
		 * Translator for QT's dialogs, etc.
		 */
		QTranslator qtTranslator;

		/**
		 * Translator for the FourInALine application.
		 */
		QTranslator appTranslator;
};

#endif // APP_FOUR_IN_A_LINE_HPP
