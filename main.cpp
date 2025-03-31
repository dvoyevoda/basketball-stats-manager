#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<map>
using namespace std;

// allows inputted names to be case insensitive & removes whitespace
string normalize(const string& str) {

    size_t first = str.find_first_not_of(" \t\n\r"); // find first letter
    size_t last = str.find_last_not_of(" \t\n\r"); // find last letter

    if (first == string::npos) return ""; 
    string trimmed = str.substr(first, last - first + 1); // cuts whitespace

    for (char& c : trimmed) c = tolower(c); // to lowercase

    return trimmed;
}

class Player {  
    public:
        Player(string playerName = "Unknown Player", string teamName = "None", vector<double> stats = vector<double>(6, 0.0)) {

            this->playerName = playerName; this->teamName = teamName; this->stats = stats;

            // STATS PER GAME ORDER IN VECTOR: Points, Rebounds, Assists, Steals, Blocks, Field Goal %
        } 
        
        void printStats(ostream& out) const {
            out << left << setw(22) << playerName
                << " | Team: " << setw(20) << teamName
                << " | PPG: " << setw(4) << fixed << setprecision(1) << stats.at(0)
                << " | RPG: " << setw(4) << stats.at(1)
                << " | APG: " << setw(4) << stats.at(2)
                << " | SPG: " << setw(4) << stats.at(3)
                << " | BPG: " << setw(4) << stats.at(4)
                << " | FGP: " << setw(6) << setprecision(2) << stats.at(5) << "%" << endl;
        }
        
        string getPlayerName() const {return playerName;}

        void setPlayerName(string n) {playerName = n;}
        void setTeamName(string n) {teamName = n;}

        double setStats(int statChoice, double value) {

            if (value < 0) { 
                value = 0;
            } else if (value > 100) { // keep range 0-100
                value = 100;
            }
            
            if (statChoice > 0 && statChoice < 7)
                stats.at(statChoice-1) = value;

        }

    private:
        string playerName, teamName;
        vector<double> stats;
};

class Team {
    public:
        Team(string name = "Unknown") : teamName(name) {} // assigned teamName trying the initializer list format

        void addPlayer(const Player& p) {
            players.push_back(p);
        }

        void printPlayers(ostream& out) const {
            out << teamName << " Team Statistics: \n\n";
            for (const Player& player : players) {
                player.printStats(out);
            }
        }

        vector<Player>& getPlayers() { return players; }                   // for setters
        const vector<Player>& getPlayers() const { return players; }       // for getters
        
    private:
        string teamName;
        vector<Player> players;
};

void printAllPlayersStats(const map<string, Team>& teams, ostream& out);
void printPlayerStats(const map<string, Team>& teams);
void printTeamStats(const map<string, Team>& teams);
void setPlayerStats(map<string, Team>& teams);
void insertPlayer(map<string, Team>& teams);

int main() {

    // Check if file opened
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

        stats.clear(); // reset vector for each run
        istringstream ss(statsLine);

        while (ss >> stat) {
            stats.push_back(stat);  // converts stats from string to vector
        }

        // Safety check
        if (stats.size() != 6) {
            cerr << "Error: expected 6 stats for player " << playerName << ", got " << stats.size() << endl;
            continue; // skip malformed entries
        }

        Player player(playerName, teamName, stats);

        if (teams.find(teamName) == teams.end()) {
            teams[teamName] = Team(teamName);
        }
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
            default:
                cout << "Invalid Input. Try again.\n\n";
                break;
        }
        
    firstRun = false;

    } while (input != 0);


return 0;
}

void printAllPlayersStats(const map<string, Team>& teams, ostream& out) {
    out << endl; // cleaner formatting
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

    // compare input name to each player name until match
    for (const auto& [teamName, team] : teams) {
        for (const Player& player: team.getPlayers()) {
            if (normalize(player.getPlayerName()) == normalize(playerName)) {
                player.printStats(cout);
                cout << endl;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    if (!found) {
        cout << "Player not found.\n\n";
    }

}

void printTeamStats(const map<string, Team>& teams) {
    string teamName;
    cin >> ws; getline(cin, teamName);
    cout << endl;

    bool found = false;

    // compare input name to each team name until match
    for (const auto& team : teams) {
        if (normalize(team.first) == normalize(teamName)) {
            team.second.printPlayers(cout);
            cout << endl;
            found = true;
            return;
        }
    }

    if (!found) {
        cout << "Team not found.\n\n";
    }
}

void setPlayerStats(map<string, Team>& teams) {
    string playerName;
    cin >> ws; getline(cin, playerName); 
    cout << endl;

    bool found = false;

    // find player first THEN prompt to change stat
    for (auto& [teamName, team] : teams) {
        for (Player& player: team.getPlayers()) {
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

    if (!found) {
        cout << "Player not found.\n\n";
    }
}

void insertPlayer(map<string, Team>& teams) {
    string playerName, teamName;       
    double PPG, RPG, APG, SPG, BPG, FGP; 

    Player player;
    
    cout << "Full name: ";
    cin.ignore(); // clear leftover newline
    getline(cin, playerName); player.setPlayerName(playerName);

    cout << "Team name: ";
    getline(cin, teamName); player.setTeamName(teamName);
    
    cout << "PPG: ";
    cin >> PPG; player.setStats(1,PPG);
    
    cout << "RPG: ";
    cin >> RPG; player.setStats(2,RPG);

    cout << "APG: ";
    cin >> APG; player.setStats(3,APG);

    cout << "SPG: ";
    cin >> SPG; player.setStats(4,SPG);

    cout << "BPG: ";
    cin >> BPG; player.setStats(5,BPG);

    cout << "FG%: ";
    cin >> FGP; player.setStats(6,FGP);

    if (teams.find(teamName) == teams.end()) {
        teams[teamName] = Team(teamName);
    }
    teams[teamName].addPlayer(player);
}