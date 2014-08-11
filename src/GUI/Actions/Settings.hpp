#ifndef GUI_ACTIONS_SETTINGS_HPP
#define GUI_ACTIONS_SETTINGS_HPP

#include "../Widgets/SelectLanguageMenu.hpp"

#include <QObject>
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
		explicit Settings(QWidget* parentWindow, QObject* parent = nullptr);
		virtual ~Settings();

		QAction* getOpenSettingsAction() const;

		QMenu* getMenu() const;
		::GUI::Widgets::SelectLanguageMenu* createLanguageMenu(QWidget* parent = nullptr) const;

	public slots:
		void showSettingsDialog();

	private:
		Q_DISABLE_COPY(Settings)

		void createActions();

		void retranslateUI();
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
		 * The settings menu.
		 */
		QScopedPointer<QMenu> menu;
};

}
}


#endif // GUI_ACTIONS_SETTINGS_HPP
