#ifndef TRACK_H
#define TRACK_H

#include <QString>

#include "album.h"

class Track {
public:
	Track(const QString &name, const Album &album, const uint8_t &number);

	QString		getName() const;
	const Album &getAlbum() const;
	uint8_t		getNumber() const;

private:
	QString		name_;
	Album		album_;
	uint8_t		number_;
};


#endif // TRACK_H
