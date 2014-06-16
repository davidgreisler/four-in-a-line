#include "Icon.hpp"

#include <QSize>
#include <QPainter>

namespace GUI
{

/**
 * Combines two icons into one icon by overlaying the second icon over the first.
 *
 * @param firstIcon First icon.
 * @param secondIcon Second icon.
 * @return Combined icon.
 */
QIcon Icon::combineIcons(const QIcon& firstIcon, const QIcon& secondIcon)
{
	QIcon result;
	QSize iconSize;
	QPainter painter;

	auto availableSizes = firstIcon.availableSizes();
	for (int i = 0; i < availableSizes.size(); ++i)
	{
		iconSize = availableSizes[i];

		QImage image(iconSize, QImage::Format_ARGB32);

		painter.begin(&image);
		painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

		painter.drawPixmap(0, 0, firstIcon.pixmap(iconSize));
		painter.drawPixmap(0, 0, secondIcon.pixmap(iconSize));

		painter.end();

		result.addPixmap(QPixmap::fromImage(image));
	}

	return result;
}

}
