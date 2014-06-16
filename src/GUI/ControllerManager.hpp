#ifndef GUI_CONTROLLERMANAGER_HPP
#define GUI_CONTROLLERMANAGER_HPP

#include <QObject>

class QMainWindow;

namespace GUI
{

class AbstractController;

/**
 * Manages central widget of the main window and currently active controller.
 *
 * A controller provides a specific functionality and a widget. This class manages the currently
 * visible/usable controller and makes sure it's widget is shown as central widget of the main
 * window.
 *
 * It is possible to request a controller to become active with requestController(), but the
 * currently active controller can refuse the request, e.g. if the user clicked no in a confirmation
 * dialog. Reimplement AbstractController::confirmDeactivation() to change the behaviour when the
 * controller is asked to deactivate. Use setController() to force switching to another controller.
 *
 * The current controller can be retrieved with getCurrentController().
 */
class ControllerManager : public QObject
{
		Q_OBJECT
	public:
		explicit ControllerManager(QMainWindow* mainWindow, QObject *parent = 0);
		virtual ~ControllerManager();

		void setController(AbstractController* controller);
		bool requestController(AbstractController* controller);

		AbstractController* getCurrentController() const;
		QMainWindow* getMainWindow() const;

	signals:
		/**
		 * Emitted when a controller is deactivated.
		 *
		 * @param controller The controller that was deactivated.
		 */
		void controllerDeactivated(AbstractController* controller);

		/**
		 * Emitted when a controller is activated.
		 *
		 * @param controller The controller that was activated.
		 */
		void controllerActivated(AbstractController* controller);

	private:
		Q_DISABLE_COPY(ControllerManager)

		/**
		 * Pointer to the main window, used to change central widget.
		 */
		QMainWindow* mainWindow;

		/**
		 * The currently active controller.
		 */
		AbstractController* currentController;
};

}

#endif // GUI_CONTROLLERMANAGER_HPP
