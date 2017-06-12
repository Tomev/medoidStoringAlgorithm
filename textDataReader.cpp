//
// Created by Tomev on 29.05.2017.
//

#include <c++/iostream>

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


