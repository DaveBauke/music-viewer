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

	delete outcome_table_;

	delete label_layout_;
	delete combo_layout_;
	delete button_layout_;
	delete main_layout_;

	delete central_widget_;

	delete label_;

	delete ui;
}

void MainWindow::InitDisplay() {
	InitComboBoxes();
	InitButtons();

	label_ = new QLabel("Welcome");		//create welcome text
	QFont font;							//and set it size
	font.setPointSize(50);
	label_->setFont(font);

	label_layout_ = new QHBoxLayout;	//create layouts
	combo_layout_ = new QHBoxLayout;
	button_layout_ = new QHBoxLayout;
	main_layout_ = new QVBoxLayout;

	label_layout_->addWidget(label_);
	label_layout_->setAlignment(Qt::AlignmentFlag::AlignCenter);

	combo_layout_->addLayout(artist_cbox_->getLayout());		//add combo boxes with labels
	combo_layout_->addLayout(album_cbox_->getLayout());
	combo_layout_->addLayout(possesion_cbox_->getLayout());

	button_layout_->addWidget(m_add_album);					//add buttons
	button_layout_->addWidget(m_search_albums);
	button_layout_->addWidget(m_search_tracks);
	button_layout_->addWidget(m_clear);

	main_layout_->addLayout(label_layout_);						//add layouts to main layout
	main_layout_->addLayout(combo_layout_);
	main_layout_->addLayout(button_layout_);

	central_widget_ = new QWidget(this);
	central_widget_->setLayout(main_layout_);

	this->setCentralWidget(central_widget_);
}

void MainWindow::InitComboBoxes() {
	artist_cbox_ = new MyComboBox("Artist:", "SELECT name FROM artist ORDER BY name", this);
	album_cbox_ = new MyComboBox("Album:", "SELECT name FROM album ORDER BY name", this);
	QStringList list;
	list << "yes" << "no";
	possesion_cbox_ = new MyComboBox("Owned", list, this);

	connect(artist_cbox_->getComboBox(),SIGNAL(currentIndexChanged(int)), this, SLOT(ArtistSelected(int)));
	connect(possesion_cbox_->getComboBox(),SIGNAL(currentIndexChanged(int)), this, SLOT(PossesionSelected(int)));
}

void MainWindow::InitButtons() {
	m_add_album = new QPushButton("Add album");
	m_search_albums = new QPushButton("Search albums");
	m_search_tracks = new QPushButton("Search tracks");
	m_clear = new QPushButton("Clear");

//	connect(m_add_album,SIGNAL(clicked()),outcome_table_,SLOT(AddAlbumHandle()));
//	connect(m_search_albums,SIGNAL(clicked()),this,SLOT(SearchAlbumsHandle()));
//	connect(m_search_tracks,SIGNAL(clicked()),this,SLOT(SearchTracksHandle()));
	connect(m_clear,SIGNAL(clicked()),this,SLOT(ClearHandle()));
}

//Add album handle
void MainWindow::AddAlbumHandle() {

}

//Search albums slot displays table with albums of given artist or possesion
void MainWindow::SearchAlbumsHandle() {
	QString q("SELECT alb.name, art.name, alb.owned FROM album alb, artist art WHERE art.id = alb.artist_id");
	QString artist = artist_cbox_->itemText();
	if(artist != ""){
	   q += " and art.name = '" + artist + "'";
	}

	q+=" ORDER BY alb.name";
	qDebug() << q;
	album_cbox_->PopulateComboBox(q);
}

//Search tracks slot displays table with albums of given artist or album or possesion
void MainWindow::SearchTracksHandle() {

}

//function sets default values in combo boxes
void MainWindow::ClearHandle() {
	artist_cbox_->ClearSelection();
	album_cbox_->ClearSelection();
	possesion_cbox_->ClearSelection();
}

//function called on artist selection in the artist combo box, fills album combo box respectively
void MainWindow::ArtistSelected(int index) {
	QString query = AlbumComboBoxQuery(artist_cbox_->itemText(index), possesion_cbox_->itemText());
	album_cbox_->PopulateComboBox(query);
}

//function called on owned selection in the possesion combo box, fills album combo box respectively
void MainWindow::PossesionSelected(int index) {
	QString query = AlbumComboBoxQuery(artist_cbox_->itemText(), possesion_cbox_->itemText(index));
	album_cbox_->PopulateComboBox(query);
}

//function creates query with given artist and possesion used to fill album combo box
QString MainWindow::AlbumComboBoxQuery(const QString &artist, QString possesion) const {
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
