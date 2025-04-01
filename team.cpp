#include "Team.h"

Team::Team(string name) : teamName(name) {}

void Team::addPlayer(const Player& p) {
    players.push_back(p);
}

void Team::printPlayers(ostream& out) const {
    out << teamName << " Team Statistics: \n\n";
    for (const Player& player : players) {
        player.printStats(out);
    }
}

vector<Player>& Team::getPlayers() { return players; }
const vector<Player>& Team::getPlayers() const { return players; }
