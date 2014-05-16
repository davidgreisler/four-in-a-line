#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QObject>
#include <QSharedPointer>
#include <QActionGroup>
#include <QAction>

namespace GUI
{
namespace Actions
{

/**
 * Actions for configuring the game, like switching the language or changing settings.
 *
 * Provides an action for opening the settings dialog. It is possible to retrieve an action group
 * containing all supported languages with getLanguages().
 */
class Settings : public QObject
{
		Q_OBJECT
	public:
		explicit Settings(QWidget *parent = 0);
		virtual ~Settings();

		QAction* getOpenSettingsAction() const;

		QSharedPointer<QActionGroup> getLanguages() const;

	signals:

	public slots:
		void openSettings();
		void switchLanguage(QAction* action);

	private:
		Q_DISABLE_COPY(Settings)

		void createActions();
		void retranslateUI();
		void updateLanguages();
		bool event(QEvent* event);

		/**
		 * Parent window, used for dialogs.
		 */
		QWidget* parentWindow;

		/**
		 * Opens the settings dialog.
		 */
		QAction* openSettingsAction;

		/**
		 * Action group containing the languages.
		 */
		QSharedPointer<QActionGroup> languageGroup;
};

}
}


#endif // SETTINGS_HPP
