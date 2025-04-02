// STD Library Header Files
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

// Project Header Files
#include "player.h"
#include "team.h"
#include "functions.h"

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
        getline(inFile, statsLine); // get the line with all 6 stats

        stats.clear();  // reset vector each run
        istringstream ss(statsLine);  // allow taking individual input from string with >>

        while (ss >> stat) stats.push_back(stat);  // essentially converting string stats to vector stats

        // Safety Check
        if (stats.size() != 6) {
            cerr << "Error: expected 6 stats for player " << playerName << ", got " << stats.size() << endl;
            continue; // skip malformed entries
        }

        Player player(playerName, teamName, stats);

        // search for teamName (Key) in teams map, if not found then assign teamName string (Key) to a new Team object (Value)
        // otherwise add player to existing team
        if (teams.find(teamName) == teams.end()) {
            teams[teamName] = Team(teamName);
        }
        teams[teamName].addPlayer(player);
    }

    int input;

    do {
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
    } while (input != 0);

    return 0;
}
