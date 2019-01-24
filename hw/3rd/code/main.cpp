#include <iostream>
#include <fstream>
#include <vector>

#include "ScheduleCollection.h"

/**
 * General output for no data available situation
 * @param out_str
 */
void noData(std::ofstream &out_str)
{
    out_str << "No data available." << std::endl;
}

// Main Entry
/* Command line example:
 * .----------------.-------------.---------------------------.---------.-------------------.
 * | argv[0]        | argv[1]     | argv[2]                   | argv[3] | argv[4](optional) |
 * :----------------+-------------+---------------------------+---------+-------------------:
 * | scheduling.exe | simple2.txt | out_simple2_room.txt      | room    |                   |
 * :----------------+-------------+---------------------------+---------+-------------------:
 * | scheduling.exe | simple2.txt | out_simple2_room.txt      | room    | ACADMY_AUD        |
 * :----------------+-------------+---------------------------+---------+-------------------:
 * | scheduling.exe | simple2.txt | out_simple2_dept_ECSE.txt | dept    | ECSE              |
 * :----------------+-------------+---------------------------+---------+-------------------:
 * | scheduling.exe | simple2.txt | out_simple2_custom.txt    | custom  |                   |
 * '----------------'-------------'---------------------------'---------'-------------------'
 */
int main(int argc, char *argv[])
{
    // No matter what happened, 4 parameters are required.
    if (argc < 4)
    {
        std::cerr << "Program required at least 3 parameters to run." << std::endl;
        return 1;
    }

    // Input file name
    std::string input = argv[1];

    // Open input file
    std::ifstream in_str(input);
    if (!in_str.good())
    {
        std::cerr << "Can't open " << input << " to read." << std::endl;
        return 1;
    }

    // Output file name
    std::string output = argv[2];

    // Open output file
    std::ofstream out_str(output);
    if (!out_str.good())
    {
        std::cerr << "Can't open " << output << " to write." << std::endl;
        return 1;
    }

    // Possible operation: room / dept / custom
    std::string operation = argv[3];

    // Process Input
    ScheduleCollection collection = ScheduleCollection(in_str);

    // Decide which operation to go
    if (operation == "room")
    {
        // 4 parameters required.
        if (argc > 4)
        {
            std::string key(argv[4]);

            SearchCollection result = collection.getRoomCollection(key);

            // Collection Size should not be zero, or maybe not data given
            if (result.getCollectionSize() > 0)
            {
                result.draw(out_str);
            } else {
                noData(out_str);
            }
        }
        else
        {
            // All Room
            std::vector<SearchCollection> result = collection.getRoomCollection();

            // Result Size should not be zero, or maybe not data given
            if (result.size() > 0)
            {
                for (unsigned int i = 0; i < result.size(); i++)
                {
                    result[i].draw(out_str);
                }
            } else {
                noData(out_str);
            }
        }
    }
    else if (operation == "dept")
    {
        // 4 parameters required
        if (argc > 4)
        {
            std::string key(argv[4]);
            SearchCollection result = collection.getDeptCollection(key);

            // Collection Size should not be zero, or maybe not data given
            if (result.getCollectionSize() > 0)
            {
                result.draw(out_str);
            } else {
                noData(out_str);
            }
        }
        else
        {
            std::cerr << "The function you enters requires 1 extra parameters." << std::endl;
            return 1;
        }
    }
    else if (operation == "custom")
    {
        // Custom Sort (Using Day)
        std::vector<SearchCollection> result = collection.getDayCollection();

        if (result.size() > 0)
        {
            for (unsigned int i = 0; i < result.size(); i++)
            {
                result[i].draw(out_str);
            }
        } else {
            noData(out_str);
        }
    }
    else
    {
        std::cerr << "The function you enters is not recognized." << std::endl;
        return 1;
    }

    in_str.close();
    out_str.close();
    
    return 0;
}