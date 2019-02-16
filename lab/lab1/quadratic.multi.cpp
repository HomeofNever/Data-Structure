#include <iostream>   // library for reading & writing from the console/keyboard
#include <cmath>      // library with the square root function & absolute value
#include <cstdlib>    // library with the exit function

// For the rest of this lab we will work with arrays and the logic of manipulating them. Modify the main
// program so that instead of a while loop, the program will read in 5 different quadratic polynomials from
// the keyboard. We will assume that all of the a coefficients are 1. So we only need to read in and store the 5
// b coefficients into an integer array named b_array with 5 slots and similarly read and store 5 c coefficients
// into a variable c_array. 


// Returns true if the candidate root is indeed a root of the polynomial a*x*x + b*x + c = 0 
bool check_root(int a, int b, int c, float root) {  
  // plug the value into the formula
  float check = a * root * root + b * root + c;
  // see if the absolute value is zero (within a small tolerance)
  if (fabs(check) > 0.0001) {
    std::cerr << "ERROR:  " << root << " is not a root of this formula." << std::endl;
    return false;
  } else {
    return true;
  }
}

/* Use the quadratic formula to find the two real roots of polynomial.   Returns 
true if the roots are real, returns false if the roots are imaginary.  If the roots 
are real, they are returned through the reference parameters root_pos and root_neg. */
bool find_roots(int a, int b, int c, float &root_pos, float &root_neg)
{
  // compute the quantity under the radical of the quadratic formula
  int radical = b * b - 4 * a * c;
  // if the radical is negative, the roots are imaginary
  if (radical < 0)
  {
    std::cerr << "ERROR:  Imaginary roots" << std::endl;
    return false;
  }
  float sqrt_radical = sqrt(radical);
  // compute the two roots
  root_pos = (-b + sqrt_radical) / (2 * a);
  root_neg = (-b - sqrt_radical) / (2 * a);
  return true;
}

int main() {
  // Init array
  int b_array[5];
  int c_array[5];

  std::cout << "Enter 5 eq with 2 integer coefficients to a quadratic function: 1*x*x + b*x + c = 0" << std::endl;

  for (int i = 0; i < 5; i++) 
  {
    int my_b, my_c;

    std::cin >> my_b >> my_c;

    b_array[i] = my_b;
    c_array[i] = my_c;
  }

  // Calculate
  for (int i = 0; i < 5; i++)
  {
    // create a place to store the roots
    float root_1, root_2;
    bool success = find_roots(1, b_array[i], c_array[i], root_1, root_2);
    // If the polynomial has imaginary roots, skip the rest of this loop and start over
    if (!success)
      continue;
    std::cout << "The roots are: " << root_1 << " and " << root_2 << std::endl;
    // Check our work...
    if (check_root(1, b_array[i], c_array[i], root_1) && check_root(1, b_array[i], c_array[i], root_2))
    {
      // Verified roots, break out of the while loop
      break;
    } else {
    std::cerr << "ERROR:  Unable to verify one or both roots." << std::endl;
    // if the program has an error, we choose to exit with a
    // non-zero error code
    exit(1); 
    }
  }

  // by convention, main should return zero when the program finishes normally
  return 0; 
}
