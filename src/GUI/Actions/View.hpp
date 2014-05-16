#ifndef ACTIONS_VIEW_HPP
#define ACTIONS_VIEW_HPP

#include <QObject>
#include <QAction>

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
 */
class View : public QObject
{
		Q_OBJECT
	public:
		explicit View(::GUI::MainWindow* mainWindow, QObject *parent = 0);
		virtual ~View();

		QAction* getFullscreenCheckboxAction() const;
	signals:

	public slots:
		void changeFullscreen();

	private:
		Q_DISABLE_COPY(View)

		void createActions();
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
};

}
}

#endif // ACTIONS_VIEW_HPP
