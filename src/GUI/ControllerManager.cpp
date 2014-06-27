#include "ControllerManager.hpp"
#include "AbstractController.hpp"

#include <QDebug>
#include <QMainWindow>

namespace GUI
{

/**
 * Creates a new controller manager.
 *
 * @param mainWindow Main window for which the central widget will be managed.
 * @param parent Parent object.
 */
ControllerManager::ControllerManager(QMainWindow* mainWindow, QObject* parent)
    : QObject(parent), mainWindow(mainWindow), currentController(nullptr)
{

}

/**
 * Frees all used resources.
 */
ControllerManager::~ControllerManager()
{

}

/**
 * Returns the current controller.
 *
 * @return Current controller or nullptr if there is no currently active controller.
 */
AbstractController* ControllerManager::getCurrentController() const
{
	return this->currentController;
}

/**
 * Returns the main window.
 *
 * @return The main window.
 */
QMainWindow* ControllerManager::getMainWindow() const
{
	return this->mainWindow;
}

/**
 * Deactivates the current controller and activates the given controller.
 *
 * @param controller The controller that should be active.
 */
void ControllerManager::setController(AbstractController* controller)
{
	if (nullptr != this->currentController)
	{
		// Prevent Qt from deleting the widget when it isn't shown anymore.

		this->currentController->getWidget()->setParent(0);

		this->currentController->deactivate();

		emit this->controllerDeactivated(this->currentController);
	}

	this->currentController = controller;

	QWidget* controllerWidget = nullptr;
	if (nullptr != controller)
	{
		controllerWidget = controller->getWidget();
		this->currentController->activate();

		emit controller->activated();
		emit this->controllerActivated(this->currentController);
	}

	/// @todo is it ok to set the central widget to null?

	this->mainWindow->setCentralWidget(controllerWidget);
}

/**
 * Requests the current controller to deactivate and activates the requested controller.
 *
 * The currently active controller can refuse this request.
 *
 * Does nothing if the requested controller is already active.
 *
 * @param controller Controller that should be active.
 * @return When the requested controller is now active true, otherwise false.
 */
bool ControllerManager::requestController(AbstractController* controller)
{
	bool result = false;

	// Requested controller is already active.

	if (this->currentController == controller)
	{
		result = true;
	}

	// No currently active controller, requested controller is not null.

	else if (this->currentController == nullptr && controller != nullptr)
	{
		this->setController(controller);
		result = true;
	}

	// There is an active controller, request deactivation.

	else if (this->currentController != nullptr && this->currentController->confirmDeactivation())
	{
		this->setController(controller);
		result = true;
	}

	return result;
}

}
