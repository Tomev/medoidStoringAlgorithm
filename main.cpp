#include <iostream>
#include <c++/random>
#include <c++/chrono>

#include "textDataParser.h"
#include "textDataReader.h"

int main()
{
  // Initialize time-dependent random seed
  srand (time(NULL));

  std::ifstream sourceFile("D:\\Dysk Google\\Data Streams\\sensor.arff");
  dataReader* dr = new textDataReader(&sourceFile);

  std::string s;

  for(int i = 0; i < 10; ++i)
  {
    dr->getNextRawDatum(&s);

    std::cout << s << std::endl;
  }

  std::cout << "Hello, World!" << std::endl;
  return 0;
}