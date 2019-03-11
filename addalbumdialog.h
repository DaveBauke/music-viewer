#ifndef ADDALBUMDIALOG_H
#define ADDALBUMDIALOG_H

#include <QDialog>
#include <QFileDialog>

class AddAlbumDialog : public QDialog {
	Q_OBJECT

public:
	AddAlbumDialog();

private:
	QFileDialog *m_file_dialog;
};

#endif // ADDALBUMDIALOG_H
