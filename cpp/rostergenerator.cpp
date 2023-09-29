#include <iostream>
#include <map>
#include <string>
#include <time.h>
#include <algorithm>

using namespace std;

// #include "generator/generate_pdf.h"
#include ".env/env.h"

int filter_roster(map<string, string> context, vector<Player>& p_list, vector<Coach>& c_list, string outdir)
{
    string n;

    // ANSI escape codes for text color
    const std::string redColor = "\033[1;31m";
    const std::string resetColor = "\033[0m";

    do
    {
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

    // do
    // {
    //     cout << "Add player: ";
    //     cin >> n;
    //     cout << endl;
    //     if (n != "")
    //     {
    //         map<string, string> new_player;
    //         new_player["num"] = n;

    //         cout << "Name: ";
    //         cin >> new_player["name"];
    //         cout << endl;

    //         cout << "Surname: ";
    //         cin >> new_player["surname"];
    //         cout << endl;

    //         Player newPlayer;
    //         newPlayer.n = stoi(new_player["num"]); // Convert string to int
    //         newPlayer.name = new_player["name"];
    //         newPlayer.surname = new_player["surname"];

    //         p_list.push_back(newPlayer);
    //     }
    // } while (n != "");

    do
    {
        cout << "Delete coach... ";
        cin >> n;
        cout << endl;

        auto it = std::remove_if(c_list.begin(), c_list.end(), [&](const Coach &coach)
                                 { return to_string(coach.n) == n; });

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

    // do
    // {
    //     cout << "Add coach: ";
    //     cin >> n;
    //     cout << endl;
    //     if (n != "")
    //     {
    //         map<string, string> new_coach;
    //         new_coach["num"] = n;

    //         cout << "Name: ";
    //         cin >> new_coach["name"];
    //         cout << endl;

    //         cout << "Surname: ";
    //         cin >> new_coach["surname"];
    //         cout << endl;

    //         Coach newCoach;
    //         newCoach.n = stoi(new_coach["num"]); // Convert string to int
    //         newCoach.name = new_coach["name"];
    //         newCoach.surname = new_coach["surname"];

    //         c_list.push_back(newCoach);
    //     }
    // } while (n != "");

    generate_pdf(context, p_list, c_list, context["team"], outdir);

    return 0;
}

int main()
{
    setContext();

    cout << "***********************************" << endl;
    cout << "**********ROSTER GENERATOR*********" << endl;
    cout << "***********************************" << endl;
    cout << endl;

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

    if (context["team"] == "kdt8")
    {
        context["category"] = "CADETE FEMENINO B";
        filter_roster(context, p_list_08, c_list_08, "C:/Users/Daniel De la Cueva/OneDrive/BASKET/KDT 08 23-24/ROSTERS");
    }
    else if (context["team"] == "kdt9")
    {
        context["category"] = "CADETE FEMENINO C";
        filter_roster(context, p_list_09, c_list_09, "C:/Users/Daniel De la Cueva/OneDrive/BASKET/KDT 09 23-24/ROSTERS");
    }
    else if (context["team"] == "inf")
    {
        context["category"] = "INFANTIL FEMENINO C";
        filter_roster(context, p_list_10, c_list_10, "C:/Users/Daniel De la Cueva/OneDrive/BASKET/INF 23-24/ROSTERS");
    }

    return 0;
}
