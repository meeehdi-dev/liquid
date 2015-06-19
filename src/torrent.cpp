#include <iostream>
#include "logger.hpp"
#include "torrent.hpp"

Torrent::Torrent (unsigned int id, unsigned long size, unsigned char free, long balance) {
	this->id = id;
	this->size = size;
	this->free = free;
	this->balance = balance;
	snatches = 0;
	changed = false;
}

unsigned int Torrent::getID () {
	return id;
}

unsigned int Torrent::getSize () {
	return size;
}

Peers* Torrent::getSeeders() {
	return &seeders;
}

Peers* Torrent::getLeechers() {
	return &leechers;
}

unsigned int Torrent::getSnatches() {
	return snatches;
}

void Torrent::incSnatches() {
	LOG_INFO("New snatch on torrent " + std::to_string(id));
	++snatches;
	changed = true;
}

void Torrent::reset() {
	snatches = 0;
	changed = false;
}

unsigned char Torrent::getFree() {
	return free;
}

void Torrent::setFree(unsigned char free) {
	this->free = free;
}

long Torrent::getBalance() {
	return balance;
}

void Torrent::incBalance(unsigned long inc) {
	changed = true;
	balance += inc;
}

void Torrent::decBalance(unsigned long dec) {
	changed = true;
	balance -= dec;
}

void Torrent::change() {
	changed = true;
}

bool Torrent::hasChanged() {
	return changed;
}
