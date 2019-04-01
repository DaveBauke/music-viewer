#ifndef ALBUM_H
#define ALBUM_H

#include <QString>

#include "artist.h"

class Album {
public:
	Album(const QString &name,
	      const Artist &artist,
	      const qint32 &year = 0,
	      const bool &owned = false,
	      const bool &wanted = false);

	QString getName() const;

	const Artist &getArtist() const;

	qint32 getYear() const;

	bool getOwned() const;
	void setOwned(const bool &owned);

	bool getWanted() const;
	void setWanted(const bool &wanted);

private:
	QString name_;
	const Artist &artist_;
	qint32	year_;
	bool	owned_;
	bool	wanted_;
};

#endif // ALBUM_H
