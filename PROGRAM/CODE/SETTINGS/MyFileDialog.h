#ifndef MY_FILE_DIALOG
#define MY_FILE_DIALOG


#include <QFileDialog>
class QWidget;


namespace MyFileDialog
{
	QString getExistingDirectory(QWidget *parent = 0,
		const QString &caption = QString(), const QString &dirProp = QString(), QFileDialog::Options options = QFileDialog::ShowDirsOnly);
	
	QString getOpenFileName(QWidget *parent = 0,
		const QString &caption = QString(), const QString &dirProp = QString(), const QString &filter = QString(),
		QString *selectedFilter = 0, QFileDialog::Options options = 0);
	
	QStringList getOpenFileNames(QWidget *parent = 0,
		const QString &caption = QString(), const QString &dirProp = QString(), const QString &filter = QString(),
		QString *selectedFilter = 0, QFileDialog::Options options = 0);
	
	QString getSaveFileName(QWidget *parent = 0,
		const QString &caption = QString(), const QString &dirProp = QString(), const QString &filter = QString(),
		QString *selectedFilter = 0, QFileDialog::Options options = 0);
};


#endif



