#ifndef GUI_WIDGETS_SELECTLANGUAGEMENU_HPP
#define GUI_WIDGETS_SELECTLANGUAGEMENU_HPP

#include "../../Settings/Application.hpp"
#include "../../../app/FourInALine.hpp"

#include <QWidget>
#include <QMenu>

class QActionGroup;

namespace GUI
{
namespace Widgets
{

/**
 * Menu that allows the user to select the application's language.
 */
class SelectLanguageMenu : public QMenu
{
		Q_OBJECT
	public:
		explicit SelectLanguageMenu(::FourInALine* application,
		                            ::Settings::Application* applicationSettings,
		                            QWidget* parent = nullptr);
		virtual ~SelectLanguageMenu();

	signals:

	public slots:
		void updateLanguage();

	private slots:
		void switchLanguage(QAction* action);

	private:
		Q_DISABLE_COPY(SelectLanguageMenu)

		void retranslateUI();
		bool event(QEvent* event);

		void updateActionGroup();

		/**
		 * Application used for changing language.
		 */
		::FourInALine* application;

		/**
		 * Settings used for saving language.
		 */
		::Settings::Application* applicationSettings;

		/**
		 * Action group containing the language actions.
		 */
		QActionGroup* actionGroup;
};

}
}

#endif // GUI_WIDGETS_SELECTLANGUAGEMENU_HPP
