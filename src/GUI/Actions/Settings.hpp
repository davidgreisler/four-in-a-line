#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QObject>
#include <QSharedPointer>
#include <QScopedPointer>

class QMenu;
class QAction;
class QActionGroup;
class QWidget;

namespace GUI
{
namespace Actions
{

/**
 * Actions for configuring the game, like switching the language or changing settings.
 *
 * Provides an action for opening the settings dialog. It is possible to retrieve an action group
 * containing all supported languages with getLanguages().
 *
 * Provides 2 menus, getMenu() returns a menu containing the language menu and the open settings
 * action, while getLanguageMenu() only returns the language menu.
 */
class Settings : public QObject
{
		Q_OBJECT
	public:
		explicit Settings(QWidget* parentWindow, QObject* parent = 0);
		virtual ~Settings();

		QAction* getOpenSettingsAction() const;

		QMenu* getMenu() const;
		QMenu* getLanguageMenu() const;

		QSharedPointer<QActionGroup> getLanguages() const;

	signals:

	public slots:
		void openSettings();
		void switchLanguage(QAction* action);

	private:
		Q_DISABLE_COPY(Settings)

		void createActions();
		void createMenu();
		void createLanguagesMenu();
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

		/**
		 * Menu containing the available languages.
		 */
		QScopedPointer<QMenu> languageMenu;

		/**
		 * Menu containing the settings actions.
		 */
		QScopedPointer<QMenu> menu;
};

}
}


#endif // SETTINGS_HPP
