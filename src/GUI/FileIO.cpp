#include "FileIO.hpp"

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

namespace GUI
{

/**
 * Opens the file with the given filename, reads the whole file and stores it in content.
 *
 * @param parentWidget Parent widget.
 * @param fileName File name/path of the file.
 * @param content Reference to a string where the file's content is stored.
 * @return When the file has been read successfully true, otherwise false.
 */
bool FileIO::GetFileContent(QWidget* parentWidget, QString fileName, QString& content)
{
	QFile file(fileName);

	if (file.open(QIODevice::ReadOnly))
	{
		QTextStream stream(&file);
		content.append(stream.readAll());

		return true;
	}
	else
	{
		QString errorMessage = parentWidget->tr("Failed to open the file '%1' for reading.");
		QMessageBox::critical(parentWidget, parentWidget->tr("Failed to open file"),
		                      errorMessage.arg(fileName),
		                      QMessageBox::Abort);
	}

	return false;
}

/**
 * Opens the file with the given filename for writing, truncates it and then writes content into the
 * file.
 *
 * @param parentWidget Parent widget.
 * @param fileName File name/path of the file.
 * @param content Content to write into the file.
 * @return When the content was written into the file successfully true, otherwise false.
 */
bool FileIO::SetFileContent(QWidget* parentWidget, QString fileName, const QString& content)
{
	QFile file(fileName);

	if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		QTextStream stream(&file);
		stream << content;
		stream.flush();

		return true;
	}
	else
	{
		QString errorMessage = parentWidget->tr("Failed to open the file '%1' for writing.");
		QMessageBox::critical(parentWidget, parentWidget->tr("Failed to open file"),
		                      errorMessage.arg(fileName),
		                      QMessageBox::Abort);
	}

	return false;
}

/**
 * Shows an open file dialog asking the user for one existing file and returns the specified
 * filename.
 *
 * @param parentWidget Parent widget.
 * @param fileName Reference to a string where the filename is stored.
 * @param nameFilter Name filter for the open file dialog.
 * @return When the user specified an existing file name true, otherwise false.
 */
bool FileIO::GetExistingFileName(QWidget* parentWidget, QString& fileName, QString nameFilter)
{
	QFileDialog fileDialog(parentWidget);
	fileDialog.setFileMode(QFileDialog::ExistingFile);
	fileDialog.setNameFilter(nameFilter);

	if (fileDialog.exec())
	{
		QStringList selectedFiles = fileDialog.selectedFiles();

		if (!selectedFiles.empty())
		{
			fileName = selectedFiles.at(0);

			return true;
		}
	}

	return false;
}

/**
 * Shows a save file dialog asking the user for one filename and returns the specified filename.
 *
 * @param parentWidget Parent widget.
 * @param fileName Reference to a string where the filename is stored.
 * @param defaultSuffix The default suffix to use.
 * @param nameFilter Name filter for the save file dialog.
 * @return When the user specified a file name true, otherwise false.
 */
bool FileIO::GetSaveFileName(QWidget* parentWidget,
                             QString& fileName, QString defaultSuffix, QString nameFilter)
{
	QFileDialog fileDialog(parentWidget);
	fileDialog.setFileMode(QFileDialog::AnyFile);
	fileDialog.setAcceptMode(QFileDialog::AcceptSave);
	fileDialog.setDefaultSuffix(defaultSuffix);
	fileDialog.setNameFilter(nameFilter);

	if (fileDialog.exec())
	{
		QStringList selectedFiles = fileDialog.selectedFiles();

		if (!selectedFiles.empty())
		{
			fileName = selectedFiles.at(0);

			return true;
		}
	}

	return false;
}

}
