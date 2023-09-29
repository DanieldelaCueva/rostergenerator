#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

#include "../.env/env.h"

int generate_pdf(std::map<std::string, std::string> context,
                 std::vector<Player> p_list, std::vector<Coach> c_list, std::string team, std::string outdir)
{

    // Read the HTML template from a file
    std::ifstream templateFile("roster_template.html");
    if (!templateFile.is_open())
    {
        std::cerr << "Failed to open HTML template file." << std::endl;
        return 1;
    }

    std::string htmlTemplate((std::istreambuf_iterator<char>(templateFile)), std::istreambuf_iterator<char>());
    templateFile.close();

    // Replace placeholders with dynamic content
    std::string clubLogoSrc = context["club_logo_src"];
    std::string clubName = context["club_name"];
    std::string category = context["category"];
    ;
    std::string competition = context["competition"]; // Replace with the actual competition name
    std::string day = context["day"];
    ;                                            // Replace with the actual day
    std::string gameDate = context["game_date"]; // Replace with the actual game date
    std::string gameTime = context["game_time"];
    ;                                                        // Replace with the actual game time
    std::string generationDate = context["generation_date"]; // Replace with the actual generation date

    // Replace placeholders in the HTML template with dynamic content
    size_t startPos = 0;
    while ((startPos = htmlTemplate.find("{{", startPos)) != std::string::npos)
    {
        size_t endPos = htmlTemplate.find("}}", startPos);
        if (endPos != std::string::npos)
        {
            std::string placeholder = htmlTemplate.substr(startPos, endPos - startPos + 2);
            if (placeholder == "{{club_logo_src}}")
            {
                htmlTemplate.replace(startPos, endPos - startPos + 2, clubLogoSrc);
            }
            else if (placeholder == "{{club}}")
            {
                htmlTemplate.replace(startPos, endPos - startPos + 2, clubName);
            }
            else if (placeholder == "{{category}}")
            {
                htmlTemplate.replace(startPos, endPos - startPos + 2, category);
            }
            else if (placeholder == "{{competition}}")
            {
                htmlTemplate.replace(startPos, endPos - startPos + 2, competition);
            }
            else if (placeholder == "{{day}}")
            {
                htmlTemplate.replace(startPos, endPos - startPos + 2, day);
            }
            else if (placeholder == "{{game_date}}")
            {
                htmlTemplate.replace(startPos, endPos - startPos + 2, gameDate);
            }
            else if (placeholder == "{{game_time}}")
            {
                htmlTemplate.replace(startPos, endPos - startPos + 2, gameTime);
            }
            else if (placeholder == "{{generation_date}}")
            {
                htmlTemplate.replace(startPos, endPos - startPos + 2, generationDate);
            }
            // Add more replacements for other placeholders as needed
        }
        startPos = endPos;
    }

    // Write the modified HTML back to a file (optional)
    std::ofstream modifiedTemplateFile("modified_template.html");
    if (!modifiedTemplateFile.is_open())
    {
        std::cerr << "Failed to create a modified HTML template file." << std::endl;
        return 1;
    }

    modifiedTemplateFile << htmlTemplate;
    modifiedTemplateFile.close();

    std::string htmlTemplateFile = "modified_template.html";                                              // Replace with your HTML template file
    std::string outputFile = outdir + "/roster-" + context["team"] + "-" + context["game_date"] + ".pdf"; // Replace with the desired output PDF file name

    // Use system() to invoke wkhtmltopdf
    std::string command = "wkhtmltopdf " + htmlTemplateFile + " " + outputFile;

    int result = system(command.c_str());

    if (result == 0)
    {
        std::cout << "PDF generation successful." << std::endl;
    }
    else
    {
        std::cerr << "PDF generation failed." << std::endl;
    }

    return 0;
}
