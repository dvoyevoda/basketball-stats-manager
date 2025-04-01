#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

class Player {
public:
    Player(std::string playerName = "Unknown Player", std::string teamName = "None", std::vector<double> stats = std::vector<double>(6, 0.0));
    
    void printStats(std::ostream& out) const;

    std::string getPlayerName() const;
    void setPlayerName(std::string n);
    void setTeamName(std::string n);
    double setStats(int statChoice, double value);

private:
    std::string playerName, teamName;
    std::vector<double> stats;
};

#endif