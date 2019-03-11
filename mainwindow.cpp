#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
	ui->setupUi(this);

	m_dbc = new DatabaseConnector();
	m_dbc->OpenConnection();

//	DropTables();
//	dbc.InitializeTables();
//	dbc.FillDatabaseFromDir(QDir("W:/Music"));

	InitDisplay();

}

MainWindow::~MainWindow() {
	delete m_dbc;
	delete m_artist_cbox;
	delete m_album_cbox;

	delete m_add_album;
	delete m_search_albums;
	delete m_clear;

	delete m_outcome_table;
	delete m_table_query;

	delete m_label_layout;
	delete m_combo_layout;
	delete m_button_layout;
	delete m_main_layout;

	delete m_central_widget;

	delete m_label;

	delete ui;
}

//initializes all control on user display
void MainWindow::InitDisplay() {
	InitComboBoxes();
	InitButtons();

	m_label_layout = new QHBoxLayout;	//create layouts
	m_combo_layout = new QHBoxLayout;
	m_button_layout = new QHBoxLayout;
	m_main_layout = new QVBoxLayout;

	m_label = new QLabel("Welcome", this);			//create welcome text
	QFont font;										//set it size
	font.setPointSize(50);
	m_label->setFont(font);
	m_label_layout->addWidget(m_label);				//add to layout
	m_label_layout->setAlignment(Qt::AlignmentFlag::AlignCenter);
	m_main_layout->addLayout(m_label_layout);			//and add to main layout

	m_combo_layout->addLayout(m_artist_cbox->getLayout());	//add combo boxes with labels to cbox layout
	m_combo_layout->addLayout(m_album_cbox->getLayout());
	m_combo_layout->addLayout(m_possesion_cbox->getLayout());
	m_main_layout->addLayout(m_combo_layout);					//and add it to main layout

	m_button_layout->addWidget(m_add_album);					//add buttons to button layout
	m_button_layout->addWidget(m_search_albums);
	m_button_layout->addWidget(m_search_tracks);
	m_button_layout->addWidget(m_clear);
	m_main_layout->addLayout(m_button_layout);				//and add it to main layout

	m_outcome_table = new QTableView();						//create outcome table and its query model
	m_table_query = new QSqlQueryModel();
	m_outcome_table->setModel(m_table_query);
	m_main_layout->addWidget(m_outcome_table);
	m_outcome_table->hide();

	m_central_widget = new QWidget(this);					//create and add main widget
	m_central_widget->setLayout(m_main_layout);
	this->setCentralWidget(m_central_widget);
}

//initializes combo boxes and connects slots to currentIndexChanged(int) signals
void MainWindow::InitComboBoxes() {
	m_artist_cbox = new MyComboBox("Artist:", "SELECT name FROM artist ORDER BY name", this);
	m_album_cbox = new MyComboBox("Album:", "SELECT name FROM album ORDER BY name", this);
	QStringList list;		list << "yes" << "no";
	m_possesion_cbox = new MyComboBox("Owned", list, this);

	connect(m_artist_cbox->getComboBox(),SIGNAL(currentIndexChanged(int)), this, SLOT(ArtistSelected(int)));
	connect(m_possesion_cbox->getComboBox(),SIGNAL(currentIndexChanged(int)), this, SLOT(PossesionSelected(int)));
}

//initializes push buttons and connects slots to clicked() signal
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
	m_table_query->setQuery(AlbumTableQuery(m_artist_cbox->itemText(), m_album_cbox->itemText(), m_possesion_cbox->itemText()));

	m_outcome_table->resizeColumnToContents(2);		//fit owned and wanted column to proper size
	m_outcome_table->resizeColumnToContents(3);

	m_outcome_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);	//stretch other columns
	m_outcome_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

	m_outcome_table->show();
}

//Search tracks slot displays table with albums of given artist or album or possesion
void MainWindow::SearchTracksHandle() {
	m_table_query->setQuery(TrackTableQuery(m_artist_cbox->itemText(), m_album_cbox->itemText(), m_possesion_cbox->itemText()));

	m_outcome_table->resizeColumnToContents(1);		//fit number column to proper size

	m_outcome_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);	//stretch other columns
	m_outcome_table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
	m_outcome_table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

	m_outcome_table->show();
}

//function sets default values in combo boxes and hides outcome table
void MainWindow::ClearHandle() {
	m_artist_cbox->ClearSelection();
	m_album_cbox->ClearSelection();
	m_possesion_cbox->ClearSelection();

	m_outcome_table->hide();
}

//function called on artist selection in the artist combo box, fills album combo box respectively
void MainWindow::ArtistSelected(int index) {
	QString query = AlbumsComboBoxQuery(m_artist_cbox->itemText(index), m_possesion_cbox->itemText());
	m_album_cbox->PopulateComboBox(query);
}

//function called on owned selection in the possesion combo box, fills album combo box respectively
void MainWindow::PossesionSelected(int index) {
	QString query = AlbumsComboBoxQuery(m_artist_cbox->itemText(), m_possesion_cbox->itemText(index));
	m_album_cbox->PopulateComboBox(query);
}

//function creates query with given artist and possesion used to fill album combo box
QString MainWindow::AlbumsComboBoxQuery(const QString &artist, QString possesion) const {
	QString query("SELECT alb.name FROM album alb");

	if(artist != ""){											//if artist is given, artist table is also needed
		query += ", artist art WHERE art.id = alb.artist_id"
		         " AND art.name = '" + artist + "'";

		if(possesion != "" ){
			possesion = (possesion == "yes") ? "true" : "false";

			query += " AND alb.owned = " + possesion;
		}
	}
	else{														//no artist, just check for possesion
		if(possesion != "" ){
			possesion = (possesion == "yes") ? "true" : "false";
			query += " WHERE alb.owned = " + possesion;
		}
	}

	query += " ORDER BY alb.name";								//sort

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
