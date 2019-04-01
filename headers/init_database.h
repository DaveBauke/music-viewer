#ifndef INIT_DATABASE_H
#define INIT_DATABASE_H

#include <QtSql>
#include <QDir>


void	AddArtistTable();
void	AddAlbumTable();
void	AddTrackTable();

void	DropTables();

void	AddData(const QDir &dir);


#endif // INIT_DATABASE_H
