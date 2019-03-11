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

	DatabaseConnector *dbc_;

	QWidget *m_central_widget;

	QVBoxLayout *main_layout_;
	QHBoxLayout *label_layout_;
	QHBoxLayout *combo_layout_;
	QHBoxLayout *button_layout_;

	QTableView *m_outcome_table;
	QSqlQueryModel *m_table_query;

	MyComboBox *artist_cbox_;
	MyComboBox *album_cbox_;
	MyComboBox *possesion_cbox_;

	QPushButton *m_add_album;
	QPushButton *m_search_albums;
	QPushButton *m_search_tracks;
	QPushButton *m_clear;

	QLabel *m_label;

	void InitDisplay();
	void InitComboBoxes();
	void InitButtons();

private slots:
	void AddAlbumHandle();
	void SearchAlbumsHandle();
	void SearchTracksHandle();
	void ClearHandle();

	void ArtistSelected(int index);
	void PossesionSelected(int index);

	QString	AlbumsComboBoxQuery(const QString &artist, QString possesion) const;

	QString AlbumTableQuery(const QString &artist, const QString &album, QString possesion) const;
	QString TrackTableQuery(const QString &artist, const QString &album, QString possesion) const;
};

#endif // MAINWINDOW_H
