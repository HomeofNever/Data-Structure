#include <iostream>
#include <string>
#include <list>


template <class T>
void print(std::list<T> &data, const std::string &label) {
  std::cout << label << " ";
  for (typename std::list<T>::iterator i = data.begin(); i != data.end(); i++) {
    std::cout << " " << *i;
  }
  std::cout << std::endl;
}


template <class T>
void reverse(std::list<T> &data) {
  if (data.size() > 0)
  {
    if (data.size() > 1)
    {
      unsigned int half = data.size() / 2;
      unsigned int counter = 0;
      typename std::list<T>::reverse_iterator e = data.rbegin();
      typename std::list<T>::iterator b = data.begin();
      for (unsigned i = 0; i < half; i++)
      {
        T temp = *e;
        *e = *b;
        *b = temp;
        if (e != data.rend())
        {
          e++;
        }
        if (b != data.end())
        {
          b++;
        }
      }
    }
  }
}


int main() {
  std::list<int> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);

  print(data,"before:");
  reverse(data);
  print(data,"after: ");

  std::list<std::string> data2;
  data2.push_back("apple");
  data2.push_back("banana");
  data2.push_back("carrot");
  data2.push_back("date");

  print(data2,"before:");
  reverse(data2);
  print(data2,"after: ");

  std::list<std::string> data3;
  data3.push_back("apple");
  data3.push_back("banana");

  print(data3,"before:");
  reverse(data3);
  print(data3,"after: ");
}