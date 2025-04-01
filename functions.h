#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <map>
#include <string>
#include "Team.h"
using namespace std;

string normalize(const string& str);
void printAllPlayersStats(const map<string, Team>& teams, ostream& out);
void printPlayerStats(const map<string, Team>& teams);
void printTeamStats(const map<string, Team>& teams);
void setPlayerStats(map<string, Team>& teams);
void insertPlayer(map<string, Team>& teams);

#endif
