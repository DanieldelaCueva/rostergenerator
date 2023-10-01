#include <iostream>
#include <map>
#include <string>
#include <time.h>
#include <algorithm>
#include <vector>
#include <Windows.h>

using namespace std;

#include ".env/env.h"

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int filter_roster(map<string, string> context, vector<Player> p_list, vector<Coach> c_list, string outdir)
{
    string n;

    // ANSI escape codes for text color
    const std::string redColor = "\033[1;31m";
    const std::string resetColor = "\033[0m";

    do
    {
        cout << "PLAYERS:" << endl;
        for (const Player& player : p_list) {
        std::cout << player.n << " - " << player.surname << " " << player.name << std::endl;
        }
        cout << "Delete player... ";
        cin >> n;
        // cout << endl;

        auto it = std::remove_if(p_list.begin(), p_list.end(), [&](const Player &player)
                                 { return to_string(player.n) == n; });

        // Check if 'it' is equal to 'p_list.end()' here and erase if needed
        if (it != p_list.end())
        {
            p_list.erase(it, p_list.end());
            cout << endl;
        }else{
            cout << redColor << "Player not found" << resetColor;
            cout << endl;
            cout << endl;
        }

    } while ((n != "n"));

    do
    {
        cout << "COACHES:" << endl;
        for (const Coach& coach : c_list) {
        std::cout << coach.n << " - " << coach.surname << " " << coach.name << std::endl;
        }
        cout << "Delete coach... ";
        cin >> n;
        cout << endl;

        auto it = std::remove_if(c_list.begin(), c_list.end(), [&](const Coach &coach)
                                 { return coach.n == n; });

        // Check if 'it' is equal to 'c_list.end()' here and erase if needed
        if (it != c_list.end())
        {
            c_list.erase(it, c_list.end());
            cout << endl;
        }else{
            cout << redColor << "Coach not found" << resetColor;
            cout << endl;
            cout << endl;
        }
    } while (n != "n");
    generate_pdf(context, p_list, c_list, context["team"], outdir);

    return 0;
}

int main()
{

    setContext();

    // Set title with colors
    setColor(1); // Red text
    cout << "***************************************************" << endl;
    cout << "******************ROSTER GENERATOR*****************" << endl;
    cout << "***************************************************" << endl;
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
