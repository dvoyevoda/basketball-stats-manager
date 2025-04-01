#include "Functions.h"
#include <iostream>
#include <sstream>
using namespace std;

string normalize(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");

    if (first == string::npos) return "";
    string trimmed = str.substr(first, last - first + 1);
    for (char& c : trimmed) c = tolower(c);

    return trimmed;
}

void printAllPlayersStats(const map<string, Team>& teams, ostream& out) {
    out << endl;
    for (const auto& pair : teams) {
        pair.second.printPlayers(out);
        out << "\n\n";
    }
}

void printPlayerStats(const map<string, Team>& teams) {
    string playerName;
    cin >> ws; getline(cin, playerName);
    cout << endl;

    bool found = false;
    for (const auto& [teamName, team] : teams) {
        for (const Player& player : team.getPlayers()) {
            if (normalize(player.getPlayerName()) == normalize(playerName)) {
                player.printStats(cout);
                cout << endl;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    if (!found) cout << "Player not found.\n\n";
}

void printTeamStats(const map<string, Team>& teams) {
    string teamName;
    cin >> ws; getline(cin, teamName);
    cout << endl;

    bool found = false;
    for (const auto& team : teams) {
        if (normalize(team.first) == normalize(teamName)) {
            team.second.printPlayers(cout);
            cout << endl;
            found = true;
            return;
        }
    }

    if (!found) cout << "Team not found.\n\n";
}

void setPlayerStats(map<string, Team>& teams) {
    string playerName;
    cin >> ws; getline(cin, playerName);
    cout << endl;

    bool found = false;
    for (auto& [teamName, team] : teams) {
        for (Player& player : team.getPlayers()) {
            if (normalize(player.getPlayerName()) == normalize(playerName)) {
                int statChoice;
                double value;
                cout << "Choose a stat to change: | 1. PPG | 2. RPG | 3. APG | 4. SPG | 5. BPG | 6. FGP |: ";
                cin >> statChoice;
                cout << "\nEnter a value: ";
                cin >> value;
                player.setStats(statChoice, value);
                cout << endl;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    if (!found) cout << "Player not found.\n\n";
}

void insertPlayer(map<string, Team>& teams) {
    string playerName, teamName;
    double PPG, RPG, APG, SPG, BPG, FGP;
    Player player;

    cout << "Full name: ";
    cin.ignore(); getline(cin, playerName); player.setPlayerName(playerName);

    cout << "Team name: ";
    getline(cin, teamName); player.setTeamName(teamName);

    cout << "PPG: "; cin >> PPG; player.setStats(1, PPG);
    cout << "RPG: "; cin >> RPG; player.setStats(2, RPG);
    cout << "APG: "; cin >> APG; player.setStats(3, APG);
    cout << "SPG: "; cin >> SPG; player.setStats(4, SPG);
    cout << "BPG: "; cin >> BPG; player.setStats(5, BPG);
    cout << "FG%: "; cin >> FGP; player.setStats(6, FGP);

    if (teams.find(teamName) == teams.end()) {
        teams[teamName] = Team(teamName);
    }

    teams[teamName].addPlayer(player);
}
