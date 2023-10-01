#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main() {
    std::ifstream file("club.csv");
    std::map<std::string, std::string> context;

    if (file.is_open()) {
        std::string line;
        int line_number = 0;

        while (std::getline(file, line)) {
            ++line_number;

            // Remove leading and trailing whitespaces
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);

            if (line_number == 1) {
                context["club_name"] = line;
            } else if (line_number == 2) {
                context["club_logo_src"] = line;
            }
        }

        file.close();

        // Printing the extracted values
        std::cout << "Club Name: " << context["club_name"] << std::endl;
        std::cout << "Club Logo Source: " << context["club_logo_src"] << std::endl;
    } else {
        std::cerr << "Error opening the file." << std::endl;
    }

    return 0;
}
