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
	delete album_cbox_;

	delete m_add_album;
	delete m_search_albums;
	delete m_clear;

	delete m_outcome_table;
	delete m_table_query;

	delete label_layout_;
	delete combo_layout_;
	delete button_layout_;
	delete main_layout_;

	delete m_central_widget;

	delete m_label;

	delete ui;
}

//initializes all control on user display
void MainWindow::InitDisplay() {
	InitComboBoxes();
	InitButtons();

	label_layout_ = new QHBoxLayout;	//create layouts
	combo_layout_ = new QHBoxLayout;
	button_layout_ = new QHBoxLayout;
	main_layout_ = new QVBoxLayout;

	m_label = new QLabel("Welcome", this);			//create welcome text
	QFont font;										//set it size
	font.setPointSize(50);
	m_label->setFont(font);
	label_layout_->addWidget(m_label);				//add to layout
	label_layout_->setAlignment(Qt::AlignmentFlag::AlignCenter);
	main_layout_->addLayout(label_layout_);			//and add to main layout

	combo_layout_->addLayout(artist_cbox_->getLayout());	//add combo boxes with labels to cbox layout
	combo_layout_->addLayout(album_cbox_->getLayout());
	combo_layout_->addLayout(possesion_cbox_->getLayout());
	main_layout_->addLayout(combo_layout_);					//and add it to main layout

	button_layout_->addWidget(m_add_album);					//add buttons to button layout
	button_layout_->addWidget(m_search_albums);
	button_layout_->addWidget(m_search_tracks);
	button_layout_->addWidget(m_clear);
	main_layout_->addLayout(button_layout_);				//and add it to main layout

	m_outcome_table = new QTableView();						//create outcome table and its query model
	m_table_query = new QSqlQueryModel();
	m_outcome_table->setModel(m_table_query);
	main_layout_->addWidget(m_outcome_table);
	m_outcome_table->hide();

	m_central_widget = new QWidget(this);					//create and add main widget
	m_central_widget->setLayout(main_layout_);
	this->setCentralWidget(m_central_widget);
}

//initializes combo boxes with artist album and possesion
void MainWindow::InitComboBoxes() {
	artist_cbox_ = new MyComboBox("Artist:", "SELECT name FROM artist ORDER BY name", this);
	album_cbox_ = new MyComboBox("Album:", "SELECT name FROM album ORDER BY name", this);
	QStringList list;		list << "yes" << "no";
	possesion_cbox_ = new MyComboBox("Owned", list, this);

	connect(artist_cbox_->getComboBox(),SIGNAL(currentIndexChanged(int)), this, SLOT(ArtistSelected(int)));
	connect(possesion_cbox_->getComboBox(),SIGNAL(currentIndexChanged(int)), this, SLOT(PossesionSelected(int)));
}

//initializes push buttons to add albums, search for albums or tracks and clear all searches
void MainWindow::InitButtons() {
	m_add_album = new QPushButton("Add album", this);
	m_search_albums = new QPushButton("Search albums", this);
	m_search_tracks = new QPushButton("Search tracks", this);
	m_clear = new QPushButton("Clear", this);

	connect(m_add_album,SIGNAL(clicked()),this,SLOT(AddAlbumHandle()));
	connect(m_search_albums,SIGNAL(clicked()),this,SLOT(SearchAlbumsHandle()));
	connect(m_search_tracks,SIGNAL(clicked()),this,SLOT(SearchTracksHandle()));
	connect(m_clear,SIGNAL(clicked()),this,SLOT(ClearHandle()));
}

//Add album handle
void MainWindow::AddAlbumHandle() {

}

//Search albums slot displays table with albums of given artist or possesion
void MainWindow::SearchAlbumsHandle() {
	m_table_query->setQuery(AlbumTableQuery(artist_cbox_->itemText(), album_cbox_->itemText(), possesion_cbox_->itemText()));

	m_outcome_table->resizeColumnToContents(2);		//fit owned and wanted column to proper size
	m_outcome_table->resizeColumnToContents(3);

	m_outcome_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);	//stretch other columns
	m_outcome_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

	m_outcome_table->show();
}

//Search tracks slot displays table with albums of given artist or album or possesion
void MainWindow::SearchTracksHandle() {
	m_table_query->setQuery(TrackTableQuery(artist_cbox_->itemText(), album_cbox_->itemText(), possesion_cbox_->itemText()));

	m_outcome_table->resizeColumnToContents(1);		//fit number column to proper size

	m_outcome_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);	//stretch other columns
	m_outcome_table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
	m_outcome_table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

	m_outcome_table->show();
}

//function sets default values in combo boxes
void MainWindow::ClearHandle() {
	artist_cbox_->ClearSelection();
	album_cbox_->ClearSelection();
	possesion_cbox_->ClearSelection();

	m_outcome_table->hide();
}

//function called on artist selection in the artist combo box, fills album combo box respectively
void MainWindow::ArtistSelected(int index) {
	QString query = AlbumsComboBoxQuery(artist_cbox_->itemText(index), possesion_cbox_->itemText());
	album_cbox_->PopulateComboBox(query);
}

//function called on owned selection in the possesion combo box, fills album combo box respectively
void MainWindow::PossesionSelected(int index) {
	QString query = AlbumsComboBoxQuery(artist_cbox_->itemText(), possesion_cbox_->itemText(index));
	album_cbox_->PopulateComboBox(query);
}

//function creates query with given artist and possesion used to fill album combo box
QString MainWindow::AlbumsComboBoxQuery(const QString &artist, QString possesion) const {
	QString query("SELECT alb.name FROM album alb");

	if(artist != ""){
		query += ", artist art WHERE art.id = alb.artist_id and art.name = '" + artist + "'";

		if(possesion != "" ){
			possesion = (possesion == "yes") ? "true" : "false";

			query += " and alb.owned = " + possesion;
		}
	}
	else{
		if(possesion != "" ){
			possesion = (possesion == "yes") ? "true" : "false";
			query += " WHERE alb.owned = " + possesion;
		}
	}

	query += " ORDER BY alb.name";

	return query;
}

//create string with query to fill table view with albums matching given arguments
QString MainWindow::AlbumTableQuery(const QString &artist, const QString &album, QString possesion) const {
	QString query("SELECT alb.name AS 'Album', art.name AS 'Artist', alb.owned AS 'Owned', alb.wanted AS 'Wanted'"	//select columns
	              " FROM album alb, artist art"
	              " WHERE alb.artist_id = art.id");																	//join tables

	if(artist != ""){									//artist name specified
		query += " AND art.name = '" + artist + "'";
	}
	if(album != ""){									//album name specified
		query += " AND alb.name = '" + album + "'";
	}
	if(possesion != "" ){								//possesion specified
		possesion = (possesion == "yes") ? "true" : "false";

		query += " AND alb.owned = " + possesion;
	}

	query += " ORDER BY art.name, alb.name";			//sort

	return query;
}

//create string with query to fill table view with tracks matching given arguments
QString MainWindow::TrackTableQuery(const QString &artist, const QString &album, QString possesion) const {
	QString query("SELECT t.name AS 'Track', t.number AS 'Number', alb.name AS 'Album', art.name AS 'Artist'"	//select columns
	              " FROM track t, album alb, artist art"														//from tables
	              " WHERE t.album_id = alb.id AND alb.artist_id = art.id");										//join tables

	if(artist != ""){									//artist name specified
		query += " AND art.name = '" + artist + "'";
	}
	if(album != ""){									//album name specified
		query += " AND alb.name = '" + album + "'";
	}
	if(possesion != "" ){								//possesion specified
		possesion = (possesion == "yes") ? "true" : "false";

		query += " AND alb.owned = " + possesion;
	}

	query += " ORDER BY art.name, alb.name, t.number";	//sort

	return query;
}
