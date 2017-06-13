//
// Created by Tomev on 29.05.2017.
//

#include <c++/iostream>
#include <sstream>

#include "textDataReader.h"

textDataReader::textDataReader(std::ifstream *sourceFile) : sourceFile(sourceFile){}

void textDataReader::getNextRawDatum(void *target)
{
  // If file is opened
  if(sourceFile->is_open())
  {
    std::string *line = static_cast<std::string*>(target);
    std::getline(*sourceFile, *line);
  }
  else
  {
    // If not then return error
    std::cout << "Couldn't read file.\n";
  }
}

void textDataReader::gatherAttributesData(void *attributesPtr)
{

  // This only works for .arff files. Not tested for others.
  std::string line;

  if(attributesPtr != NULL)
  {
    std::vector<attributeData> *attributes = static_cast<std::vector<attributeData> *>(attributesPtr);

    // While line doesn't start with @attribute
    while (line.find("@attribute")) getNextRawDatum(&line);

    // While line starts with @attribute
    while (!line.find("@attribute")) {
      std::istringstream ss(line);
      std::string substring;

      getline(ss, substring, ' ');

      attributes->push_back(attributeData());

      getline(ss, substring, ' ');

      attributes->at(attributes->size() - 1).attributeName = substring;

      getline(ss, substring, ' ');

      if (substring.find("Numeric") == 0) attributes->at(attributes->size() - 1).attributeType = substring;
      else attributes->at(attributes->size() - 1).attributeType = "Symbolic";

      getNextRawDatum(&line);
    }
  }

  // If pointer was null, then only prepare for data reading.

  while(line.find("@data")) getNextRawDatum(&line);
  getNextRawDatum(&line);

}


