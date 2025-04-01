#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
using namespace std;

class Player {
public:
    Player(string playerName = "Unknown Player", string teamName = "None", vector<double> stats = vector<double>(6, 0.0));
    
    void printStats(ostream& out) const;

    string getPlayerName() const;
    void setPlayerName(string n);
    void setTeamName(string n);
    double setStats(int statChoice, double value);

private:
    string playerName, teamName;
    vector<double> stats;
};

#endif