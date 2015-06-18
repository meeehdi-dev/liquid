#pragma once

#include "user.hpp"

class Peer {
	private:
		User* user;
		unsigned long total_stats;
		unsigned long stats;
		unsigned long left;
		bool seeding;
		bool completed;
		bool active;
		std::string hexIP;
		std::string peerID;
		unsigned int fid;
		std::string client;
		long long seedtime;
		long long lastUpdate;
		unsigned int speed;
		unsigned int corrupt;
	public:
		Peer (std::string, User*, bool, unsigned long, unsigned int, std::string, std::string);
		User* User();
		const std::string& getPeerID();
		const std::string& getHexIP();
		const std::string& getClient();
		void updateStats(unsigned long, unsigned long, unsigned int, long long);
		unsigned long getTotalStats();
		unsigned long getStats();
		unsigned long getLeft();
		long long getLastUpdate();
		unsigned int getSpeed();
		unsigned int getFID();
		unsigned int getCorrupt();
		bool isSeeding();
		bool isCompleted();
		bool isActive();
		void inactive();
		bool timedOut(long long);
		bool isSnatched();
		void snatched();
		long long getSeedtime();
		void reset(long long);
};
