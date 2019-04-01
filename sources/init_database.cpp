#include "init_database.h"


void	AddArtistTable() {
	QSqlQuery q;
	qDebug() <<"Adding artist table: "<< q.exec("CREATE TABLE artist (id INT UNSIGNED NOT NULL UNIQUE AUTO_INCREMENT)");
	qDebug() <<"Adding name col: " << q.exec("ALTER TABLE artist ADD (name VARCHAR(75) NOT NULL UNIQUE)");
	qDebug() <<"Adding year col: " << q.exec("ALTER TABLE artist ADD (year SMALLINT UNSIGNED)");
}

void	AddAlbumTable() {
	QSqlQuery q;
	qDebug() <<"Adding album table: " << q.exec("CREATE TABLE album (id INT UNSIGNED NOT NULL UNIQUE AUTO_INCREMENT)");
	qDebug() <<"Adding name col: " << q.exec("ALTER TABLE album ADD (name VARCHAR(100) NOT NULL)");
	qDebug() <<"Adding artist col: "<< q.exec("ALTER TABLE album ADD (artist_id INT UNSIGNED NOT NULL)");
	qDebug() <<"Adding year col: "<< q.exec("ALTER TABLE album ADD (year SMALLINT UNSIGNED)");
	qDebug() <<"Adding owned col: "<< q.exec("ALTER TABLE album ADD (owned BOOL DEFAULT 0)");
	qDebug() <<"Adding wanted col: "<< q.exec("ALTER TABLE album ADD (wanted BOOL DEFAULT 0)");
}

void	AddTrackTable() {
	QSqlQuery q;
	qDebug() <<"Adding track table: "<< q.exec("CREATE TABLE track (id INT UNSIGNED NOT NULL UNIQUE AUTO_INCREMENT)");
	qDebug() <<"Adding name col: "<< q.exec("ALTER TABLE track ADD (name VARCHAR(100) NOT NULL)");
	qDebug() <<"Adding album col: "<< q.exec("ALTER TABLE track ADD (album_id INT UNSIGNED NOT NULL)");
	qDebug() <<"Adding number col: "<< q.exec("ALTER TABLE track ADD (number TINYINT UNSIGNED)");
}

void	DropTables() {
	QSqlQuery q;
	q.exec("DROP TABLE artist");
	q.exec("DROP TABLE album");
	q.exec("DROP TABLE track");
}
