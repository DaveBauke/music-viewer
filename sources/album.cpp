#include "album.h"

Album::Album(const QString &name,
             const Artist &artist,
             const qint32 &year,
             const bool &owned,
             const bool &wanted) :
    name_(name), artist_(artist), year_(year), owned_(owned), wanted_(wanted){
}

QString Album::getName() const {
	return name_;
}

const Artist &Album::getArtist() const {
	return artist_;
}

qint32 Album::getYear() const {
	return year_;
}

bool Album::getOwned() const {
	return owned_;
}

void Album::setOwned(const bool &owned) {
	owned_ = owned;
}

bool Album::getWanted() const {
	return wanted_;
}

void Album::setWanted(const bool &wanted) {
	wanted_ = wanted;
}
