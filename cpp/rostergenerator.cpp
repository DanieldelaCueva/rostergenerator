#include <iostream>
#include <map>
#include <string>
#include <time.h>
#include <algorithm>
#include <vector>
#include <Windows.h>

using namespace std;

#include "filter/filter.h"

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main()
{
    setContext();

    // Set title with colors
    setColor(1); // Red text
    cout << "***************************************************" << endl;
    cout << "******************ROSTER GENERATOR*****************" << endl;
    cout << "***************************************************" << endl;
    cout << "                         by Daniel De la Cueva v1.0" << endl;
    cout << endl;
    setColor(7); // Red text

    cout << "Team code: ";
    cin >> context["team"];
    cout << endl;

    cout << "Competition: ";
    cin >> context["competition"];
    cout << endl;

    cout << "Day: ";
    cin >> context["day"];
    cout << endl;

    cout << "Game date: ";
    cin >> context["game_date"];
    cout << endl;

    cout << "Game time: ";
    cin >> context["game_time"];
    cout << endl;

    // get generation time
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    context["generation_date"] = buf;

    std::string teamId = context["team"];

    for (const Team& team : teams) {
        if (team.teamId == teamId) {
            context["category"] = team.category;
            // Call your filter_roster function here with team.players, team.coaches, and team.teamOutputDirectory
            // filter_roster(context, team.players, team.coaches, team.teamOutputDirectory);
            filter_roster(context, team.players, team.coaches, team.teamOutputDirectory);
            return 0; // Exit the loop when a match is found
        }
    }
    std::cout << "Team not found." << std::endl;

    return 0;
}
