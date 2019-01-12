#include <iostream>
#include <fstream>
#include <vector>

std::vector< std::vector<char> > process(std::ifstream &in_str) {
    std::string line;
    std::vector< std::vector<char> > vec;
    
    while (in_str >> line) {
        std::vector<char> v(line.begin(), line.end());
        vec.push_back(v);
    }

    return vec;
}

void writeVec(std::vector< std::vector<char> > &vec, std::ofstream &out_str) {
    for (unsigned int i = 0; i < vec.size(); i++) {
        for (unsigned int j = 0; j < vec[i].size(); j++) {
            out_str << vec[i][j];
        }

        // Add a newline when each line finished.
        out_str << std::endl;
    }
}


void replace(char &char1, char &char2, std::vector< std::vector<char> > &vec, std::vector< std::vector<char> > &result) {
    for (unsigned int i = 0; i < vec.size(); i++) {
        for (unsigned int j = 0; j < vec[i].size(); j++) {
            // Find if target matched
            if (vec[i][j] == char1) {
                // Matched! Replace it!
                result[i][j] = char2;
            }
        }
    }
}

void erosion(char char1, char char2, std::vector< std::vector<char> > &vec, std::vector< std::vector<char> > &result) {
    // Remove the first and the last coordinate
    for (unsigned int i = 1; i < vec.size() - 1; i++) {
        for (unsigned int j = 1; j < vec[i].size() - 1; j++) {
            char current = vec[i][j];

            // Skip if current is not targeted
            if (current != char2)
            {
                // four candicates
                char up = vec[i - 1][j];
                char down = vec[i + 1][j];
                char left = vec[i][j - 1];
                char right = vec[i][j + 1];

                // If any candicate match target
                if (left == char1 && right == char1 && up == char1 && down == char1) {
                    // Special: when all matched, do nothing
                } else if (left == char1 || right == char1 || up == char1 || down == char1) {
                    // replace when target appear
                    result[i][j] = char2;
                }
            }
        }
    }
}

void dilation(char char1, std::vector< std::vector<char> > &vec, std::vector< std::vector<char> > &result) {
    // Remove the first and the last coordinate
    for (unsigned int i = 1; i < vec.size() - 1; i++) {
        for (unsigned int j = 1; j < vec[i].size() - 1; j++) {
            char current = vec[i][j];

            // Skip if current has added
            if (current != char1) {
                // four candicates
                char up = vec[i - 1][j];
                char down = vec[i + 1][j];
                char left = vec[i][j - 1];
                char right = vec[i][j + 1];

                // If any candicate matches target
                if (left == char1 || right == char1 || up == char1 || down == char1) {
                    // add new pixel
                    result[i][j] = char1;
                }
            }
        }
    }
}

// ./image_processing.out input4.txt output4_dilation.txt dilation X

int main(int argc, char* argv[]) {
    // Input
    std::string input = argv[1];
    
    // Open target file
    std::ifstream in_str(input);
    if (!in_str.good()) {
        std::cerr << "Can't open " << argv[3] << " to read.\n";
        exit(1);
    }

    // Output
    std::string output = argv[2];

    // Open output file
    std::ofstream out_str(output);
    if (!out_str.good()) {
        std::cerr << "Can't open " << argv[4] << " to write.\n";
        exit(1);
    }

    // Possible operation: replace, dilation, or erosion
    std::string operation = argv[3];

    // Read the first symbol
    char char1 = argv[4][0];

    // Process Input 
    std::vector< std::vector<char> > vec = process(in_str);
    // Copy new Vec (emmm memory boom)
    std::vector< std::vector<char> > result = vec;

    if (operation == "replace") {
        char char2 = argv[5][0];
        replace(char1, char2, vec, result);
    } else if (operation == "erosion") {
        char char2 = argv[5][0];
        erosion(char1, char2, vec, result);
    } else {
        // dilation
        dilation(char1, vec, result);
    }

    writeVec(result, out_str);

    in_str.close();
    out_str.close();

    return 0;
}