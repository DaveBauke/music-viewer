#include "track.h"

Track::Track(const QString &name, const Album &album, const uint8_t &number) :
    name_(name), album_(album), number_(number){
}

QString		Track::getName() const {
	return name_;
}

const Album &Track::getAlbum() const {
	return album_;
}

uint8_t		Track::getNumber() const {
    return number_;
}
