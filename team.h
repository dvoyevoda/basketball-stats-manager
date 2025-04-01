#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <iostream>
#include "player.h"

class Team {
public:
    Team(std::string name = "Unknown");

    void addPlayer(const Player& p);
    void printPlayers(std::ostream& out) const;

    std::vector<Player>& getPlayers();
    const std::vector<Player>& getPlayers() const;

private:
    std::string teamName;
    std::vector<Player> players;
};

#endif