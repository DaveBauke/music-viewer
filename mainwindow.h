#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableView>
#include <QWidget>

#include "databaseconnector.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow *ui;

	DatabaseConnector *dbc_;

	QWidget *central_widget_;

	QVBoxLayout *main_layout_;
	QHBoxLayout *label_layout_;
	QHBoxLayout *combo_layout_;

	QSqlQueryModel *artist_model_;
	QSqlQueryModel *album_model_;
	QSqlQueryModel *track_model_;

	QTableView *artist_table_;
	QTableView *album_table_;
	QTableView *track_table_;

	QComboBox *artist_cbox_;
	QComboBox *album_cbox_;
	QComboBox *track_cbox_;

	QLabel *label_;

	void InitDisplay();
	void InitArtistCombo();
	void InitAlbumCombo();
	void InitTrackCombo();
};

#endif // MAINWINDOW_H
