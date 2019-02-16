#include <iostream>
#include <vector>

float sum_vec(std::vector<float> &vec) 
{
    float sum = 0;

    for (int i = 0; i < vec.size(); i++) 
    {
        sum += vec[i];
    }

    return sum;
}

void list_smaller(float average, std::vector<float> &vec) {
    for (int i = 0; i < vec.size(); i++) 
    {
        if (vec[i] < average) {
            std::cout << vec[i] << ' '; 
        }
    }
}

int main(int argc, char* argv[]) 
{
    int number;
    std::cout << "Enter a list of number, the first one should be an int (the number of float will be enter)." << std::endl;
    std::cin >> number;

    std::vector<float> vec;

    // Get into the vector
    for (int i = 0; i < number; i++)
    {
        float n;
        std::cin >> n;
        vec.push_back(n);
    } 

    float sum = sum_vec(vec);

    std::cout << sum << std::endl;

    float average = sum / number;

    std::cout << "The average is " << average << std::endl; 

    list_smaller(average, vec);

    return 0;
}