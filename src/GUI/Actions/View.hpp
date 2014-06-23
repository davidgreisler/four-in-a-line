#ifndef GUI_ACTIONS_VIEW_HPP
#define GUI_ACTIONS_VIEW_HPP

#include <QObject>
#include <QScopedPointer>
#include <QList>

class QAction;
class QActionGroup;
class QMenu;

namespace GUI
{
class MainWindow;
}

namespace GUI
{
namespace Actions
{

/**
 * Contains actions regarding the view, e.g. to toggle fullscreen mode.
 *
 * Provides a checkbox action to toggle fullscreen mode on/off.
 *
 * Contains a toolbar menu, which has one action for every toolbar, to toggle display on/off.
 * The toolbars are usually created after this class is instantiated, therefore the toolbar menu is
 * empty until it is populated using updateToolbars().
 */
class View : public QObject
{
		Q_OBJECT
	public:
		explicit View(::GUI::MainWindow* mainWindow, QObject *parent = 0);
		virtual ~View();

		QAction* getFullscreenCheckboxAction() const;

		QMenu* getMenu() const;
		QMenu* getToolbarMenu() const;

		void updateToolbars(QList<QAction*> actions);

	signals:

	public slots:
		void changeFullscreen();
		void updateFullscreen();

	private:
		Q_DISABLE_COPY(View)

		void createActions();
		void createMenu();
		void createToolbarMenu();
		void retranslateUI();
		bool event(QEvent* event);

		/**
		 * Main window, used to toggle fullscreen mode.
		 */
		::GUI::MainWindow* mainWindow;

		/**
		 * Checkbox for activating/deactivating fullscreen mode.
		 */
		QAction* fullscreenCheckboxAction;

		/**
		 * Menu containing the view actions.
		 */
		QScopedPointer<QMenu> menu;

		/**
		 * Menu containing an action for every toolbar, to toggle display on/off.
		 */
		QScopedPointer<QMenu> toolbarMenu;
};

}
}

#endif // GUI_ACTIONS_VIEW_HPP
