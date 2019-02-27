#include <iostream>

unsigned int i = 0;

void one_step(int x, int y)
{
  if (x == 0 && y == 0)
  {
    i++;
  } else if (x >= 0 && y >= 0)
  {
    one_step(x - 1, y);
    one_step(x, y - 1);
  }
}

int main() {
  one_step(2, 3);
  std::cout << "Possible Paths: " << i << std::endl;
  return 0;
}