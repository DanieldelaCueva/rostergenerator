#include <vector>
#include <string>

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

struct Team
{
    std::string teamId;
    std::string category;
    std::string teamOutputDirectory;
    std::vector<Player> players;
    std::vector<Coach> coaches;
};

int generate_pdf(std::map<std::string, std::string> context,
                 std::vector<Player> p_list, std::vector<Coach> c_list, std::string team, std::string outdir);
