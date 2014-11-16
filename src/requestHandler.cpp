#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "requestHandler.hpp"
#include "response.hpp"
#include "utility.hpp"
#include "torrent.hpp"

torrentMap RequestHandler::torMap;

std::string RequestHandler::handle(std::string str, std::string ip)
{
	request req = Parser::parse(str); // parse the request
	try {
		if (req.at("accept-encoding").find("gzip") != std::string::npos)
			req.emplace("gzip", "true");
	} catch (const std::exception& e) {
		req.emplace("gzip", "false");
	}
	std::string check = Parser::check(req); // check if we have all we need to process (saves time if not the case
	if (check != "success")
		return error(check, req.at("gzip") == "true");
	req.emplace("ip", ip);
	if (req.at("action") == "announce")
		return announce(req);
	return error("invalid action", req.at("gzip") == "true"); // not possible, since the request is checked, but, well, who knows :3
}

std::string RequestHandler::announce(const request& req)
{
	torMap.emplace(req.at("info_hash"), new Torrent());
	Torrent *tor = torMap.at(req.at("info_hash"));
	PeerMap *pmap;
	if (std::stoi(req.at("left")) > 0) {
		pmap = tor->Leechers();
		if (pmap->getPeer(req.at("peer_id")) == nullptr)
			pmap->addPeer(req.at("peer_id"), 
					(Utility::ip_hex_encode(req.at("ip"))
					 +
					 Utility::port_hex_encode(req.at("port"))));
		pmap = tor->Seeders();
	} else {
		pmap = tor->Seeders();
		if (!pmap->getPeer(req.at("peer_id")))
			pmap->addPeer(req.at("peer_id"), 
					(Utility::ip_hex_encode(req.at("ip"))
					 +
					 Utility::port_hex_encode(req.at("port"))));
		pmap = tor->Leechers();
	}
	std::string peers;
	unsigned long i = 10;
	try {
		i = std::stoi(req.at("numwant"));
	} catch (const std::exception& e) {}
	i = std::min(i, pmap->size());
	while (i-- > 0)
		peers.append(pmap->nextPeer()->getHexIP());
	return response(
			("d8:completei"
			 + std::to_string(tor->Seeders()->size())
			 + "e10:incompletei"
			 + std::to_string(tor->Leechers()->size())
			 + "e8:intervali"
			 + std::to_string(900)
			 + "e12:min intervali"
			 + std::to_string(300)
			 + "e5:peers"
			 + std::to_string(peers.length())
			 + ":"
			 + peers
			 + "e"),
			req.at("gzip") == "true"
		       ); // doesn't look as bad as it is stated on ocelot, needs stresstesting to check
}
