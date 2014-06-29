#ifndef GUI_FILEIO_HPP
#define GUI_FILEIO_HPP

#include <QString>

class QWidget;

namespace GUI
{

/**
 * Provides static methods for frequently needed file operations and file dialogs.
 *
 * It is possible to get a file's content with GetFileContent() and set a file's content with
 * SetFileContent(). Use GetExistingFileName() to request the user to open an existing file, and
 * GetSaveFileName() to let the user select a file for saving.
 */
class FileIO
{
	public:
		static bool GetFileContent(QWidget* parentWidget, QString fileName, QByteArray& content);
		static bool SetFileContent(QWidget* parentWidget, QString fileName, const QByteArray& content);

		static bool GetExistingFileName(QWidget* parentWidget, QString& fileName,
		                                QString nameFilter);
		static bool GetSaveFileName(QWidget* parentWidget, QString& fileName,
		                            QString defaultSuffix, QString nameFilter);

	private:
		FileIO();
};

}

#endif // GUI_FILEIO_HPP
