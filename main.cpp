#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "Player.h"
#include "Team.h"
#include "Functions.h"

using namespace std;

int main() {
    ifstream inFile("basketball_player_stats.txt");
    if (!inFile.is_open()) {
        cout << "Error opening file." << endl;
        return 0;
    }

    string playerName, teamName, statsLine;
    vector<double> stats;
    double stat;
    map<string, Team> teams;

    while (getline(inFile, playerName)) {
        getline(inFile, teamName);
        getline(inFile, statsLine);
        stats.clear();
        istringstream ss(statsLine);
        while (ss >> stat) stats.push_back(stat);
        if (stats.size() != 6) continue;

        Player player(playerName, teamName, stats);
        if (teams.find(teamName) == teams.end()) teams[teamName] = Team(teamName);
        teams[teamName].addPlayer(player);
    }

    int input;
    bool firstRun = true;

    cout << "\n======= Basketball Stats Manager =======\n\n"
        << "Choose an option by entering the number:\n\n"
        << "  1.  View all players and statistics.\n"
        << "  2.  View stats for a specific player.\n"
        << "  3.  View stats for a specific team.\n"
        << "  4.  Update stats for a specific player.\n"
        << "  5.  Insert a new player and their stats.\n"
        << "  6.  Export all data to a file.\n"
        << "  0.  Exit.\n\n"
        << "Your choice: ";

    do {
        if (!firstRun) cout << "Enter another option: ";
        cin >> input;

        switch (input) {
            case 0: 
                cout << "Exiting..." << endl; 
                break;
            case 1: 
                printAllPlayersStats(teams, cout); 
                break;
            case 2: 
                cout << "Enter the name of your player: "; 
                printPlayerStats(teams); 
                break;
            case 3: 
                cout << "Enter team name: "; 
                printTeamStats(teams); 
                break;
            case 4: 
                cout << "Enter the name of your player: "; 
                setPlayerStats(teams); 
                break;
            case 5: 
                cout << "\nComplete each step to insert your player and stats.\n\n"; 
                insertPlayer(teams); 
                break;
            case 6: {
                ofstream exportFile("ExportedData.txt");
                printAllPlayersStats(teams, exportFile);
                exportFile.close();
                cout << "\nAll player statistics have been saved to ExportedData.txt\n\n";
                break;
            }
            default: cout << "Invalid Input. Try again.\n\n"; break;
        }
        firstRun = false;
    } while (input != 0);

    return 0;
}
