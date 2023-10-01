#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

struct Player {
    int n;
    std::string name;
    std::string surname;
};

struct Coach {
    std::string n;
    std::string name;
    std::string surname;
};

struct Team {
    std::string teamId;
    std::string category;
    std::string teamOutputDirectory;
    std::vector<Player> players;
    std::vector<Coach> coaches;
};

int main() {
    std::ifstream inputFile("teams.csv");
    std::string line;
    std::vector<Team> teams;
    Team currentTeam;

    bool isParsingPlayers = true;

    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;

        if (line == "//") {
            isParsingPlayers = true; // Reset to parsing players when encountering a new team
            teams.push_back(currentTeam);
            currentTeam = Team();
            continue;
        }

        if (line == "--") {
            // Switch between parsing players and coaches
            isParsingPlayers = !isParsingPlayers;
            continue;
        }

        if (currentTeam.teamId.empty()) {
            currentTeam.teamId = line;
        } else if (currentTeam.category.empty()) {
            currentTeam.category = line;
        } else if (currentTeam.teamOutputDirectory.empty()) {
            currentTeam.teamOutputDirectory = line;
        } else if (line.find(';') != std::string::npos) {
            if (isParsingPlayers) {
                // Assuming it's a player line
                Player player;
                size_t pos = line.find(';');
                std::string nStr = line.substr(0, pos);
                line = line.substr(pos + 1);

                // Convert nStr to an integer, handling potential exceptions
                try {
                    player.n = std::stoi(nStr);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error converting n to integer: " << e.what() << std::endl;
                    // Handle the error or continue to the next line as needed
                }

                pos = line.find(';');
                player.name = line.substr(0, pos);
                line = line.substr(pos + 1);
                player.surname = line;
                currentTeam.players.push_back(player);
            } else {
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
    if (!currentTeam.teamId.empty()) {
        teams.push_back(currentTeam);
    }

    // Print the parsed teams
    for (const Team& team : teams) {
        std::cout << "Team ID: " << team.teamId << std::endl;
        std::cout << "Category: " << team.category << std::endl;
        std::cout << "Team Output Directory: " << team.teamOutputDirectory << std::endl;
        std::cout << "Players:" << std::endl;
        for (const Player& player : team.players) {
            std::cout << "  Player ID: " << player.n << ", Name: " << player.name << ", Surname: " << player.surname << std::endl;
        }
        std::cout << "Coaches:" << std::endl;
        for (const Coach& coach : team.coaches) {
            std::cout << "  Coach ID: " << coach.n << ", Name: " << coach.name << ", Surname: " << coach.surname << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
