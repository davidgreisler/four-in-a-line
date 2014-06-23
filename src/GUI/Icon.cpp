#include "Icon.hpp"

#include <QSize>
#include <QPainter>
#include <QDebug>

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

		if (!secondIcon.availableSizes().contains(iconSize))
		{
			// The second icon is not available in this size.

			continue;
		}

		QImage image(iconSize, QImage::Format_ARGB32);
		image.fill(QColor(0, 0, 0, 0));

		if (!painter.begin(&image))
		{
			qDebug() << "[ Icon::combineIcons ] Failed to begin painting.";

			continue;
		}

		painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
		painter.drawPixmap(0, 0, firstIcon.pixmap(iconSize));
		painter.drawPixmap(0, 0, secondIcon.pixmap(iconSize));

		painter.end();

		result.addPixmap(QPixmap::fromImage(image));
	}

	return result;
}

}
