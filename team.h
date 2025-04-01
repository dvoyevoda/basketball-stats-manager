#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>
#include "Player.h"
using namespace std;

class Team {
public:
    Team(string name = "Unknown");

    void addPlayer(const Player& p);
    void printPlayers(ostream& out) const;

    vector<Player>& getPlayers();
    const vector<Player>& getPlayers() const;

private:
    string teamName;
    vector<Player> players;
};

#endif