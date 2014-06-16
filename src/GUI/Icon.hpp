#ifndef GUI_ICON_HPP
#define GUI_ICON_HPP

#include <QIcon>

namespace GUI
{

/**
 * Provides a static method for combining two icons into one by overlaying the second over the
 * first.
 */
class Icon
{
	public:
		static QIcon combineIcons(const QIcon& firstIcon, const QIcon& secondIcon);

	private:
		Icon();
};

}

#endif // GUI_ICON_HPP
