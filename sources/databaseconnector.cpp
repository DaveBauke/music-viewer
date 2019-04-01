#include "databaseconnector.h"

//initialise connector with default options
DatabaseConnector::DatabaseConnector() {
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setPort(3306);
	db.setUserName("root");
	db.setPassword("5Nb!d8rVX3%wkSN=");
	db.setDatabaseName("MusicDB");
}

DatabaseConnector::~DatabaseConnector() {
	db.close();
}

//create tables for artists, albums and tracks
bool DatabaseConnector::InitializeTables() const{
	AddArtistTable();
	AddAlbumTable();
	AddTrackTable();

	return true;
}

//creates database with given name
bool DatabaseConnector::InitializeDatabase(const QString &db_name) {
	db.setDatabaseName(db_name);

	return true;
}

//iniitalizes database connection
//returns true if succeeded
bool DatabaseConnector::OpenConnection() {
	if(db.open()){
		qDebug() << "connected to database" << db.databaseName() << endl;
		return true;
	}
	else {
		qDebug() << "Couldn't connect to database:\n" << db.lastError();
		return false;
	}
}

//fills the database with data from given directory
//following structure is assumed:
//base_dir
//	-artist name 1
//		-album name 1
//			-01 track name 1.mp3
//			-02 track name 1.mp3
//		-album name 2
//			-01 track name 1.mp3
//	-artist name 2...
bool DatabaseConnector::FillDatabaseFromDir(const QDir &base_dir) const {
	return AddArtistsFromDir(base_dir);
}

//adds all artists from artist_dir and all albums found inside artist directory
bool DatabaseConnector::AddArtistsFromDir(const QDir &artist_dir) const {
	QStringList artist_list = artist_dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
	QSqlQuery	artist_query;

	artist_query.prepare("INSERT INTO artist (name) VALUES (?)");
	for (int i = 0; i < artist_list.size(); ++i) {							//iterate through all folders
		QString artist_name = artist_list.at(i);
		artist_name.replace("'", "^");										//replace apostrophes

		//TODO check if this works and makes no problem with searching for it later
		//artist_name.replace("'", "''");										//escape apostrophe in query

		Artist artist(artist_name);
		artist_query.bindValue(0, artist.getName());
		qDebug() << artist.getName() << '\t' << artist_query.exec();

		QDir albums_dir(artist_dir.absoluteFilePath( artist_list.at(i) ));
		AddAlbumsFromDir(albums_dir, artist);								//add artist's albums
	}
	return true;
}

//adds all albums of given artist from album_dir and all tracks found inside album directory
bool DatabaseConnector::AddAlbumsFromDir(const QDir &albums_dir, const Artist &artist) const {
	QStringList album_list = albums_dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
	QSqlQuery	album_query, get_artist_id;
	QString		select_artist_id("SELECT id FROM artist WHERE name = '" + artist.getName() + "'");
	uint32_t	artist_id = 0;

	if (!get_artist_id.exec(select_artist_id) || !get_artist_id.next())	//if query failes
		return false;

	artist_id = get_artist_id.value(0).toString().toUInt();
	album_query.prepare("INSERT INTO album (name, artist_id) VALUES (?, ?)");
	album_query.bindValue(1, artist_id);
	for (int i = 0; i < album_list.size(); ++i) {						//iterate through all directories
		QString album_name = album_list.at(i);
		album_name.replace("'", "^");									//replace apostrophe

		//TODO check if this works and makes no problem with searching for it later
//		album_name.replace("'", "''");

		Album album(album_name, artist);
		album_query.bindValue(0, album.getName());
		qDebug() << '\t' << album.getName() << '\t' << album_query.exec();

		QDir tracks_dir(albums_dir.absoluteFilePath( album_list.at(i) ));
		AddTracksFromDir(tracks_dir, album);							//add album's tracks
	}

	return true;
}

//adds all tracks from given album
bool DatabaseConnector::AddTracksFromDir(const QDir &tracks_dir, const Album &album) const {
	QStringList filter;
	QStringList track_list;
	QSqlQuery	track_query, get_album_id;
	uint32_t	album_id = 0;
	QString		select_album_id("SELECT alb.id FROM album alb, artist art WHERE art.id = alb.artist_id");

	select_album_id += " and alb.name = '" + album.getName() + "'";
	select_album_id += " and art.name = '" + album.getArtist().getName() + "'";

	if (!get_album_id.exec(select_album_id) || !get_album_id.next())	//if query failes
		return false;

	album_id = get_album_id.value(0).toString().toUInt();

	filter << "*.mp3" << "*.wma";
	track_list = tracks_dir.entryList(filter, QDir::NoFilter, QDir::Name);

	track_query.prepare("INSERT INTO track (name, album_id, number) VALUES (?, ?, ?)");
	track_query.bindValue(1, album_id);
	for (uint8_t i = 0; i < track_list.size(); ++i) {			//iterate through all tracks in directory
		QString track_name = track_list.at(i);
		track_name.remove(0, 3);								//delete number and space
		track_name.remove(track_name.size() - 4, 4);			//delete file extension
		track_name.replace("'", "^");							//replace apostrophe

		//TODO check if this works and makes no problem with searching for it later
//		track_name.replace("'", "''");

		Track track(track_name, album, i+1);

		track_query.bindValue(0, track.getName());
		track_query.bindValue(2, track.getNumber());
		qDebug() << '\t' << '\t' << track.getName() << '\t' << track_query.exec();
	}
	return true;
}
