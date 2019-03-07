#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
	ui->setupUi(this);

	dbc_ = new DatabaseConnector();
	dbc_->OpenConnection();

//	DropTables();
//	dbc.InitializeTables();
//	dbc.FillDatabaseFromDir(QDir("W:/Music"));

	InitDisplay();

}

MainWindow::~MainWindow() {
	delete dbc_;
	delete artist_cbox_;
	delete artist_model_;
	delete artist_table_;

	delete album_cbox_;
	delete album_model_;
	delete album_table_;

	delete track_cbox_;
	delete track_model_;
	delete track_table_;

	delete central_widget_;

	delete label_;

	delete ui;
}

void MainWindow::InitDisplay() {
	InitArtistCombo();
	InitTrackCombo();
	InitAlbumCombo();


	label_ = new QLabel("Welcome");


	label_layout_ = new QHBoxLayout;
	combo_layout_ = new QHBoxLayout;
	main_layout_ = new QVBoxLayout;

	label_layout_->addWidget(label_);
	label_layout_->setAlignment(Qt::AlignmentFlag::AlignCenter);

	combo_layout_->addWidget(artist_cbox_);
	combo_layout_->addWidget(album_cbox_);
	combo_layout_->addWidget(track_cbox_);

	main_layout_->addLayout(label_layout_);
	main_layout_->addLayout(combo_layout_);


	central_widget_ = new QWidget(this);
	central_widget_->setLayout(main_layout_);

	this->setCentralWidget(central_widget_);
}

void MainWindow::InitArtistCombo() {
	artist_cbox_ = new QComboBox;
	artist_model_ = new QSqlQueryModel;
	artist_model_->setQuery("select name from artist order by name");
	artist_cbox_->setModel(artist_model_);

}

void MainWindow::InitAlbumCombo() {
	album_cbox_ = new QComboBox;
	album_model_ = new QSqlQueryModel;
	album_model_->setQuery("select name from album order by name");
	album_cbox_->setModel(album_model_);

}

void MainWindow::InitTrackCombo() {
	track_cbox_ = new QComboBox;
	track_model_ = new QSqlQueryModel;
	track_model_->setQuery("select name from track order by name");
	track_cbox_->setModel(track_model_);

}
