#include "env.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

std::map<std::string, std::string> context;
std::vector<Team> teams;

int setContext()
{

    std::ifstream file(".env/club.csv");

    if (file.is_open())
    {
        std::string line;
        int line_number = 0;

        while (std::getline(file, line))
        {
            ++line_number;

            // Remove leading and trailing whitespaces
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);

            if (line_number == 1)
            {
                context["club_name"] = line;
            }
            else if (line_number == 2)
            {
                context["club_logo_src"] = line;
            }
        }

        file.close();
    }
    else
    {
        std::cerr << "Error opening the file." << std::endl;
    }

    std::ifstream inputFile(".env/teams.csv");
    std::string line;
    Team currentTeam;

    bool isParsingPlayers = true;

    while (std::getline(inputFile, line))
    {
        if (line.empty())
            continue;

        if (line == "//")
        {
            isParsingPlayers = true; // Reset to parsing players when encountering a new team
            teams.push_back(currentTeam);
            currentTeam = Team();
            continue;
        }

        if (line == "--")
        {
            // Switch between parsing players and coaches
            isParsingPlayers = !isParsingPlayers;
            continue;
        }

        if (currentTeam.teamId.empty())
        {
            currentTeam.teamId = line;
        }
        else if (currentTeam.category.empty())
        {
            currentTeam.category = line;
        }
        else if (currentTeam.teamOutputDirectory.empty())
        {
            currentTeam.teamOutputDirectory = line;
        }
        else if (line.find(';') != std::string::npos)
        {
            if (isParsingPlayers)
            {
                // Assuming it's a player line
                Player player;
                size_t pos = line.find(';');
                std::string nStr = line.substr(0, pos);
                line = line.substr(pos + 1);

                // Convert nStr to an integer, handling potential exceptions
                try
                {
                    player.n = std::stoi(nStr);
                }
                catch (const std::invalid_argument &e)
                {
                    std::cerr << "Error converting n to integer: " << e.what() << std::endl;
                    // Handle the error or continue to the next line as needed
                }

                pos = line.find(';');
                player.name = line.substr(0, pos);
                line = line.substr(pos + 1);
                player.surname = line;
                currentTeam.players.push_back(player);
            }
            else
            {
                // Assuming it's a coach line
                Coach coach;
                size_t pos = line.find(';');
                coach.n = line.substr(0, pos);
                line = line.substr(pos + 1);
                pos = line.find(';');
                coach.name = line.substr(0, pos);
                line = line.substr(pos + 1);
                coach.surname = line;
                currentTeam.coaches.push_back(coach);
            }
        }
    }

    // Add the last team
    if (!currentTeam.teamId.empty())
    {
        teams.push_back(currentTeam);
    }

    return 0;
}