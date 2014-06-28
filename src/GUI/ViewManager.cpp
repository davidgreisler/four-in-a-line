#include "ViewManager.hpp"
#include "AbstractView.hpp"

#include <QDebug>
#include <QMainWindow>

namespace GUI
{

/**
 * Creates a new view manager.
 *
 * @param mainWindow Main window for which the central widget will be managed.
 * @param parent Parent object.
 */
ViewManager::ViewManager(QMainWindow* mainWindow, QObject* parent)
    : QObject(parent), mainWindow(mainWindow), currentView(nullptr)
{

}

/**
 * Frees all used resources.
 */
ViewManager::~ViewManager()
{

}

/**
 * Returns the current view.
 *
 * @return Current view or nullptr if there is no currently active view.
 */
AbstractView* ViewManager::getCurrentView() const
{
	return this->currentView;
}

/**
 * Returns the main window.
 *
 * @return The main window.
 */
QMainWindow* ViewManager::getMainWindow() const
{
	return this->mainWindow;
}

/**
 * Deactivates the current view and activates the given view.
 *
 * @param view The view that should be active.
 */
void ViewManager::setView(AbstractView* view)
{
	if (nullptr != this->currentView)
	{
		// Prevent Qt from deleting the widget when it isn't shown anymore.

		this->currentView->getWidget()->setParent(0);

		this->currentView->deactivate();

		emit this->viewDeactivated(this->currentView);
	}

	this->currentView = view;

	QWidget* viewWidget = nullptr;
	if (nullptr != view)
	{
		viewWidget = view->getWidget();
		this->currentView->activate();

		emit view->activated();
		emit this->viewActivated(this->currentView);
	}

	/// @todo is it ok to set the central widget to null?

	this->mainWindow->setCentralWidget(viewWidget);
}

/**
 * Requests the current view to deactivate and activates the requested view.
 *
 * The currently active view can refuse this request.
 *
 * Does nothing if the requested view is already active.
 *
 * @param view View that should be active.
 * @return When the requested view is now active true, otherwise false.
 */
bool ViewManager::requestView(AbstractView* view)
{
	bool result = false;

	// Requested view is already active.

	if (this->currentView == view)
	{
		result = true;
	}

	// No currently active view, requested view is not null.

	else if (this->currentView == nullptr && view != nullptr)
	{
		this->setView(view);
		result = true;
	}

	// There is an active view, request deactivation.

	else if (this->currentView != nullptr && this->currentView->confirmDeactivation())
	{
		this->setView(view);
		result = true;
	}

	return result;
}

}
