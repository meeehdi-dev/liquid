#pragma once

#include <string>
#include <unordered_map>
#include "peers.hpp"

class Torrent {
	private:
		Peers seeders;
		Peers seeders6;
		Peers leechers;
		Peers leechers6;
		unsigned int id;
		unsigned char free;
		unsigned int snatches;
		long balance;
		bool changed;
	public:
		Torrent(unsigned int, unsigned char, long);
		Peers* getSeeders();
		Peers* getSeeders6();
		Peers* getLeechers();
		Peers* getLeechers6();
		unsigned int getSnatches();
		void incSnatches();
		void reset();
		unsigned int getID();
		unsigned char getFree();
		void setBalance(long);
		long getBalance();
		void setFree(unsigned char);
		void change();
		bool hasChanged();
};
