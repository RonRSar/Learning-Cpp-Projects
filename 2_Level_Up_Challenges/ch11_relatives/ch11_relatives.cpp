// C++ Code Challenges, LinkedIn Learning

// Challenge #11: Finding Relatives
// Write an application that reads a list of people's names in a CSV file and outputs the first pair of people it finds to be possibly related based on their family names.
// Assume that all entries have one name and one family name.
// Entries are separated by commas.
// Names and family names are separated by spaces.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

// Finding Relatives, main()
// Summary: This application displays the first pair of possible relatives from a list of names in a CSV file.

void create_sample_csv()
{
    // I added this function here for a cleaner commit (no csv in repo)
    std::ofstream out("names.csv");
    out << "George Phillips,Anna Brady,Rhonda Davis,Jessica Thomas,Jeff Thomas,Rick Davis";
    out.close();
}

int main()
{
    create_sample_csv();
    std::fstream file("names.csv", std::ios::in);
    std::vector<std::string> name_str{};
    // Read the CSV file.
    if (file.is_open())
    {
        std::string name{};
        while (std::getline(file, name, ','))
        {
            name_str.push_back(name);
        }
        file.close();
    }
    else
    {
        std::cout << "Something went wrong\n"
                  << std::flush;
        return 1;
    }

    std::vector<std::string> last_name{};
    for (const auto& n : name_str)
    {
        auto name_it = n.find(' '); // assume no middle names
        last_name.push_back(n.substr(name_it + 1));
    }

    bool seen{};
    std::vector<std::pair<std::string, std::string>> relatives{};  //using a pair so we can find all relatives even if that is not the prompt
    for (auto i = 0; i < last_name.size(); i++)
    {
        for (auto j = i + 1; j < last_name.size(); j++)
        {
            if (last_name[i] == last_name[j])
            {
                seen = true;
                relatives.push_back(std::pair<std::string, std::string>(name_str[i], name_str[j]));
            }
        }
    }

    if (!relatives.empty())
    {
        for (auto relative : relatives) //this is just extra we could do relatives[0].first and .second to meet the spec
        {
            std::cout << relative.first << " and " << relative.second << " are likely relatives.\n";
        }
    }
    else
        std::cout << "No relatives found.\n\n"
                  << std::flush;
    return 0;
}
