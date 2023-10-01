#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cstdio>

#include "../.env/env.h"

int generate_pdf(std::map<std::string, std::string> context,
                 std::vector<Player> p_list, std::vector<Coach> c_list, std::string team, std::string outdir)
{

    // Read the HTML template from a file
    std::ifstream templateFile("generator/roster_template.html");
    if (!templateFile.is_open())
    {
        std::cerr << "Error: Unable to open template file." << std::endl;
        return 1;
    }

    // Read the template content into a string
    std::string htmlTemplate((std::istreambuf_iterator<char>(templateFile)),
                             std::istreambuf_iterator<char>());

    // Replace placeholders with values
    for (const auto &pair : context)
    {
        std::string placeholder = "{{" + pair.first + "}}";
        size_t pos = htmlTemplate.find(placeholder);
        while (pos != std::string::npos)
        {
            htmlTemplate.replace(pos, placeholder.length(), pair.second);
            pos = htmlTemplate.find(placeholder, pos + pair.second.length());
        }
    }

    // Write the modified HTML to a file
    std::ofstream outputFile("temp/modified_template.html");
    if (!outputFile.is_open())
    {
        std::cerr << "Error: Unable to create or open output file." << std::endl;
        return 1;
    }
    outputFile << htmlTemplate;
    outputFile.close();

    std::cout << "Modified HTML template has been written to modified_template.html." << std::endl;

    // Open the template.html file for reading
    std::ifstream templateFile2("temp/modified_template.html");
    if (!templateFile2.is_open())
    {
        std::cerr << "Failed to open template.html" << std::endl;
        return 1;
    }

    // Read the content of the template file into a string
    std::string templateContent(
        (std::istreambuf_iterator<char>(templateFile2)),
        (std::istreambuf_iterator<char>()));

    // Close the template file
    templateFile2.close();

    // Generate HTML code for p_list
    std::string playerHtml;
    for (const Player &player : p_list)
    {
        playerHtml += "<tr style='height: 18px;'>\n";
        playerHtml += "<td style='width: 10%; height: 18px; text-align: center;'>" + std::to_string(player.n) + "</td>\n";
        playerHtml += "<td style='width: 45%; height: 18px; padding-left: 1%;'>" + player.surname + "</td>\n";
        playerHtml += "<td style='width: 45%; height: 18px; padding-left: 1%;'>" + player.name + "</td>\n";
        playerHtml += "</tr>\n";
    }

    // Generate HTML code for c_list
    std::string coachHtml;
    for (const Coach &coach : c_list)
    {
        coachHtml += "<tr style='height: 18px;'>\n";
        coachHtml += "<td style='width: 10%; height: 18px; text-align: center;'>" + coach.n + "</td>\n";
        coachHtml += "<td style='width: 45%; height: 18px; padding-left: 1%;'>" + coach.surname + "</td>\n";
        coachHtml += "<td style='width: 45%; height: 18px; padding-left: 1%;'>" + coach.name + "</td>\n";
        coachHtml += "</tr>\n";
    }

    // Replace placeholders in the template with generated HTML
    size_t insert1Pos = templateContent.find("<!--insert1-->");
    if (insert1Pos != std::string::npos)
    {
        templateContent.replace(insert1Pos, 14, playerHtml);
    }

    size_t insert2Pos = templateContent.find("<!--insert2-->");
    if (insert2Pos != std::string::npos)
    {
        templateContent.replace(insert2Pos, 14, coachHtml);
    }

    // Write the modified content to a new HTML file
    std::ofstream outputFile2("temp/output.html");
    if (!outputFile2.is_open())
    {
        std::cerr << "Failed to create output.html" << std::endl;
        return 1;
    }

    outputFile2 << templateContent;
    outputFile2.close();

    std::string htmlTemplateFile = "temp/output.html"; // Replace with your HTML template file
    std::string outputDirect = outdir + "/roster-" + context["team"] + "-" + context["game_date"] + ".pdf\""; // Replace with the desired output PDF file name
    // std::string outputDirect = "output.pdf";
    // std::string outputDirect = "roster-" + context["team"] + "-" + context["game_date"] + ".pdf";

    // Use system() to invoke wkhtmltopdf
    std::string command = "wkhtmltopdf " + htmlTemplateFile + " " + outputDirect;

    int result = system(command.c_str());

    if (result == 0)
    {
        std::cout << "PDF generation successful." << std::endl;
        std::remove("temp/modified_template.html");
        std::remove("temp/output.html");
    }
    else
    {
        std::cerr << "PDF generation failed." << std::endl;
    }

    return 0;
}
