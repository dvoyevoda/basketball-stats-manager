#include "player.h"
#include <iomanip>
using namespace std;

Player::Player(string playerName, string teamName, vector<double> stats)    
    : playerName(playerName), teamName(teamName), stats(stats) {}   // assigned values trying the initializer list format

    // STATS PER GAME ORDER IN VECTOR: Points, Rebounds, Assists, Steals, Blocks, Field Goal %

void Player::printStats(ostream& out) const {
    out << left << setw(22) << playerName
        << " | Team: " << setw(20) << teamName
        << " | PPG: " << setw(4) << fixed << setprecision(1) << stats.at(0)
        << " | RPG: " << setw(4) << stats.at(1)
        << " | APG: " << setw(4) << stats.at(2)
        << " | SPG: " << setw(4) << stats.at(3)
        << " | BPG: " << setw(4) << stats.at(4)
        << " | FGP: " << setw(6) << setprecision(2) << stats.at(5) << "%" << endl;
}

string Player::getPlayerName() const { return playerName; }

void Player::setPlayerName(string n) { playerName = n; }
void Player::setTeamName(string n) { teamName = n; }

double Player::setStats(int statChoice, double value) {

    // keep range 0-100
    if (value < 0) value = 0;
    else if (value > 100) value = 100;
    
    // modifies stat in vector based on choice which becomes the index
    if (statChoice > 0 && statChoice < 7)
        stats.at(statChoice - 1) = value;
    
    return value;
}