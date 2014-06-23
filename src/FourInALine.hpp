#ifndef FOUR_IN_A_LINE_HPP
#define FOUR_IN_A_LINE_HPP

#include <QApplication>
#include <QMap>
#include <QString>
#include <QTranslator>

class FourInALineSettings;

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

		FourInALineSettings* getSettings() const;

		QMap<QString, QString> getAvailableLanguages() const;
		void setLanguage(QString locale);
		QString getLanguage() const;

	private slots:
		void updateLanguage();

	private:
		/**
		 * The application's settings.
		 */
		FourInALineSettings* settings;

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

#endif // FOUR_IN_A_LINE_HPP
