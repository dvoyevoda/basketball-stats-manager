#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <map>
#include <iostream>
#include "team.h"

std::string normalize(const std::string& str);
void printAllPlayersStats(const map<std::string, Team>& teams, std::ostream& out);
void printPlayerStats(const std::map<std::string, Team>& teams);
void printTeamStats(const std::map<std::string, Team>& teams);
void setPlayerStats(std::map<std::string, Team>& teams);
void insertPlayer(std::map<std::string, Team>& teams);

#endif
