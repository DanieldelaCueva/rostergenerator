#include <map>
#include <string>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <vector>

#include "../.env/env.h"

using namespace std;

int filter_roster(std::map<std::string, std::string> context, std::vector<Player> p_list, std::vector<Coach> c_list, std::string outdir)
{
    std::string n;

    // ANSI escape codes for text color
    const std::string redColor = "\033[1;31m";
    const std::string resetColor = "\033[0m";

    do
    {
        std::cout << "PLAYERS:" << std::endl;
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