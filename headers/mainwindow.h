#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableView>
#include <QWidget>
#include <QSpacerItem>
#include <QPushButton>

#include "mycombobox.h"
#include "databaseconnector.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow *ui;

	DatabaseConnector *m_dbc;

	QWidget *m_central_widget;

	QVBoxLayout *m_main_layout;
	QHBoxLayout *m_label_layout;
	QHBoxLayout *m_combo_layout;
	QHBoxLayout *m_button_layout;

	QTableView *m_outcome_table;
	QSqlQueryModel *m_table_query;

	MyComboBox *m_artist_cbox;
	MyComboBox *m_album_cbox;
	MyComboBox *m_possesion_cbox;

	QPushButton *m_add_album;
	QPushButton *m_search_albums;
	QPushButton *m_search_tracks;
	QPushButton *m_clear;

	QLabel *m_label;

	void InitDisplay();
	void InitComboBoxes();
	void InitButtons();

	QString	AlbumsComboBoxQuery(const QString &artist, QString possesion) const;

	QString AlbumTableQuery(const QString &artist, const QString &album, QString possesion) const;
	QString TrackTableQuery(const QString &artist, const QString &album, QString possesion) const;

private slots:
	void AddAlbumHandle();
	void SearchAlbumsHandle();
	void SearchTracksHandle();
	void ClearHandle();

	void ArtistSelected(int index);
	void PossesionSelected(int index);
};

#endif // MAINWINDOW_H
