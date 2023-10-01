// env.h

#ifndef ENV_H
#define ENV_H

#include <map>
#include <string>
#include <vector>

#include "../generator/generate_pdf.h"

extern std::vector<Team> teams;
extern std::map<std::string,std::string>context;

#endif // ENV_H

int setContext();