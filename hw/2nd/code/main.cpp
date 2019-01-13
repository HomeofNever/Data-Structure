#include <iostream>
#include <fstream>
#include <vector>

// Convert input stream into 2D vector
std::vector< std::vector<char> > process(std::ifstream &in_str) 
{
    std::string line;
    std::vector< std::vector<char> > vec;
    
    while (in_str >> line) 
    {
        // Generate a new vector with current line.
        std::vector<char> v(line.begin(), line.end());
        vec.push_back(v);
    }

    return vec;
}

// Edge tester
// When accessing the vector, use this method for comparison to prevent undefined behavior
bool compare(int row, 
            int col,
            std::vector< std::vector<char> > &vec,
            char targetChar) 
{
    int vecRow = (int)vec.size() - 1;
    int vecCol = (int)vec[0].size() - 1;

    if (row < 0 || row > vecRow || col < 0 || col > vecCol) {
        // Unable to access target location
        // Return false by default
        return false;
    }
    else if (vec[row][col] == targetChar)
    {
        return true;
    } else {
        return false;
    }
}

// Write 2D Vector to destination
void writeVec(std::vector< std::vector<char> > &vec, std::ofstream &out_str) 
{
    for (int i = 0; i < (int)vec.size(); i++) {
        for (int j = 0; j < (int)vec[i].size(); j++) {
            out_str << vec[i][j];
        }

        // Add a newline at the end of each line.
        out_str << std::endl;
    }
}


void replace(char char1, 
             char char2, 
             std::vector< std::vector<char> > &vec, 
             std::vector< std::vector<char> > &result) 
{
    for (unsigned int i = 0; i < vec.size(); i++) 
    {
        for (unsigned int j = 0; j < vec[i].size(); j++) 
        {
            // Find if target matched
            if (vec[i][j] == char1) 
            {
                // Matched! Replace it!
                result[i][j] = char2;
            }
        }
    }
}

void erosion(char char1, 
             char char2, 
             std::vector< std::vector<char> > &vec, 
             std::vector< std::vector<char> > &result) 
{
    // Remove the first and the last coordinate

    for (int i = 0; i < (int)vec.size(); i++) 
    {
        for (int j = 0; j < (int)vec[i].size(); j++) 
        {
            char current = vec[i][j];

            // Skip if current is not target char
            if (current == char1) 
            {
                // Four candicates
                bool up = compare(i - 1, j, vec, char2);
                bool down = compare(i + 1, j, vec, char2);
                bool left = compare(i, j - 1, vec, char2);
                bool right = compare(i, j + 1, vec, char2);

                // If any candicate match target
                if (left && right && up && down) 
                {
                    // Special: when all cancidate matched, do nothing
                } 
                else if (left || right || up || down ) 
                {
                    // Replace when target appears
                    result[i][j] = char2;
                }
            }
        }
    }
}

void dilation(char char1, 
              std::vector< std::vector<char> > &vec, 
              std::vector< std::vector<char> > &result) 
{
    // Remove the first and the last coordinate
    for (int i = 0; i < (int)vec.size(); i++) 
    {
        for (int j = 0; j < (int)vec[i].size(); j++) 
        {
            char current = vec[i][j];

            // Skip if current is not target char
            if (current != char1) 
            {
                // Four candicates
                bool up = compare(i - 1, j, vec, char1);
                bool down = compare(i + 1, j, vec, char1);
                bool left = compare(i, j - 1, vec, char1);
                bool right = compare(i, j + 1, vec, char1);

                // If any candicate matches target
                if (left || right || up || down) 
                {
                    // Replace that pixel!
                    result[i][j] = char1;
                }
            }
        }
    }
}

// Commandline Format
// argv[0]                argv[1]    argv[2]              argv[3]  argv[4] argv[5]
// ./image_processing.out input4.txt output4_dilation.txt dilation X
// ./image_processing.out input4.txt output4_erosion.txt erosion X \.
int main(int argc, char* argv[]) 
{
    if (argc < 4) 
    {
        std::cerr << "Program required at least 4 parameters to run." << std::endl;
        exit(1);
    }

    // Input file name
    std::string input = argv[1];
    
    // Open input file
    std::ifstream in_str(input);
    if (!in_str.good()) 
    {
        std::cerr << "Can't open " << input << " to read." << std::endl;
        exit(1);
    }

    // Output file name
    std::string output = argv[2];

    // Open output file
    std::ofstream out_str(output);
    if (!out_str.good()) 
    {
        std::cerr << "Can't open " << output << " to write." << std::endl;
        exit(1);
    }

    // Possible operation: replace, dilation, or erosion
    std::string operation = argv[3];

    // Read the chars
    char char1 = argv[4][0];

    // Process Input 
    std::vector< std::vector<char> > vec = process(in_str);
    // Copy new Vec (memory boom?)
    std::vector< std::vector<char> > result = vec;

    // Decide which operation to go
    if (operation == "replace")
    {
        if (argc > 5)
        {
            char char2 = argv[5][0];
            replace(char1, char2, vec, result);
        }
        else 
        {
            std::cerr << "The function you enters requires 5 parameters." << std::endl;
            exit(1);
        }
    } 
    else if (operation == "erosion") 
    {
        if (argc > 5)
        {
            char char2 = argv[5][0];
            erosion(char1, char2, vec, result);
        }
        else
        {
            std::cerr << "The function you enters requires 5 parameters." << std::endl;
            exit(1);
        }
    } 
    else if (operation == "dilation")
    {
        dilation(char1, vec, result);
    }
    else
    {
        std::cerr << "The function you enters is not recognized." << std::endl;
        exit(1);
    }

    writeVec(result, out_str);

    in_str.close();
    out_str.close();

    return 0;
}