#include <iostream>
#include <c++/random>
#include <c++/chrono>

#include "textDataParser.h"
#include "textDataReader.h"
#include "medoidStoringAlgorithm.h"

std::vector<std::vector<std::vector<sample*>>> medoids;

int main()
{
  // Initialize time-dependent random seed
  srand (time(NULL));

  std::ifstream sourceFile("D:\\Dysk Google\\Data Streams\\sensor.arff");

  dataReader* dr = new textDataReader(&sourceFile);
  dataParser* dp = new textDataParser();

  medoidStoringAlgorithm a(dp, dr);

  dr->gatherAttributesData(NULL);

  a.findAndStoreMedoids(&medoids);

  std::cout
    << medoids.size() << std::endl
    << medoids.at(0).size() << std::endl
    << medoids.at(0).at(0).size() << std::endl
    << medoids.at(0).at(medoids.at(0).size()-1).size() << std::endl
    << medoids.at(medoids.size()-1).size() << std::endl
    << medoids.at(medoids.size()-1).at(medoids.at(medoids.size()-1).size()-1).size();

  medoids.at(0).at(0).at(0)->print();

  return 0;
}