//
// Created by Tomev on 29.05.2017.
//

#ifndef RESERVOIRALGORITHM_TEXTDATAPARSER_H
#define RESERVOIRALGORITHM_TEXTDATAPARSER_H

/*
 * Parsing from .arff files to sample.
 */

#include "dataParser.h"

#include <string>
#include <vector>
#include <c++/iostream>

struct sample
{
  std::vector<std::string> values;

  void print()
  {
    std::cout << "Data: ";

    for(int i = 0; i < values.size(); ++i)
    {
      std::cout << values.at(i) << ", ";
    }

    std::cout << std::endl;
  }
};

class textDataParser : public dataParser
{

  public:

    textDataParser();

    void parseData(void *target);
    int addDatumToContainer(void *container);
    void writeDatumOnPosition(void *container, int position);
};


#endif //RESERVOIRALGORITHM_TEXTDATAPARSER_H
