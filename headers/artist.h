#ifndef ARTIST_H
#define ARTIST_H

#include <QString>

class Artist
{
public:
	Artist(const QString &name, const qint32 &year = 0);

	QString getName() const;

	qint32 getYear() const;

private:
	QString name_;
	qint32 year_;
};

#endif // ARTIST_H
