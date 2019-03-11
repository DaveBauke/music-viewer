#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <QtSql>
#include <QDir>

#include "init_database.h"
#include "artist.h"
#include "album.h"
#include "track.h"

class DatabaseConnector
{
public:
	DatabaseConnector();
	~DatabaseConnector();

	bool InitializeTables() const;
	bool InitializeDatabase(const QString &db_name);
	bool OpenConnection();
	bool FillDatabaseFromDir(const QDir &base_dir) const;

	bool AddArtistsFromDir(const QDir &artists_dir) const;
	bool AddAlbumsFromDir(const QDir &albums_dir, const Artist &artist) const;
	bool AddTracksFromDir(const QDir &tracks_dir, const Album &album) const;

	QSqlDatabase db;
private:


};

#endif // DATABASECONNECTOR_H
