#include <vector>
#include <string>

struct Player {
    int n;
    std::string name;
    std::string surname;
};

struct Coach {
    int n;
    std::string name;
    std::string surname;
};

int generate_pdf(std::map<std::string, std::string> context,
                 std::vector<Player> p_list, std::vector<Coach> c_list, std::string team, std::string outdir);
