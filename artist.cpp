#include "artist.h"


Artist::Artist(const QString &name, const qint32 &year) : name_(name), year_(year) {
}

QString Artist::getName() const {
	return name_;
}

qint32 Artist::getYear() const {
	return year_;
}
