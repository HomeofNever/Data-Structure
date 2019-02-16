#include <iostream>
#include <string>
#include <math.h>

int main(int argc, char *argv[])
{
    if (argc > 4)
    {
        double q1 = std::stod(argv[1]);
        double p1 = std::stod(argv[2]);

        double q2 = std::stod(argv[3]);
        double p2 = std::stod(argv[4]);

        double change_q = q2 - q1;
        double change_p = p2 - p1;
        double slope = change_p / change_q;

        std::cout << "Changed quantity: " << change_q << std::endl;
        std::cout << "Changed price: " << change_p << std::endl;
        std::cout << "Slope: " << slope << std::endl;

        std::cout << std::string(10, '-') << std::endl;

        double mid_q = q1 + change_q / 2;
        double mid_p = p1 + change_p / 2;

        std::cout << "mid quantity: " << mid_q << std::endl;
        std::cout << "mid price: " << mid_p << std::endl;

        std::cout << std::string(10, '-') << std::endl;

        double change_rate_q = (change_q / mid_q);
        double change_rate_p = (change_p / mid_p);

        std::cout << "mid rate quantity: " << change_rate_q << std::endl;
        std::cout << "mid rate price: " << change_rate_p << std::endl;

        double elastic = fabs(change_rate_q / change_rate_p);

        std::cout << "PED: " << elastic << std::endl;

        std::cout << std::string(10, '-') << std::endl;

        std::cout << "Situation: ";
        if (elastic == 1.00)
        {
            std::cout << "Unit Elastic" << std::endl;
        } else if (elastic < 1.00)
        {
            std::cout << "inelastic" << std::endl;
        } else {
            std::cout << "Elastic" << std::endl;
        }

    } else {
        std::cout << "Usage: elastic.exe [old quantity] [old price] [new quantity] [new price]" << std::endl;
    }

}
