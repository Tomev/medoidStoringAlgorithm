//
// Created by Tomev on 29.05.2017.
//

#ifndef RESERVOIRALGORITHM_TEXTDATAPARSER_H
#define RESERVOIRALGORITHM_TEXTDATAPARSER_H

/*
 * Parsing from .arff files to sample.
 */

#include <string>
#include <vector>
#include <c++/iostream>

#include "dataParser.h"
#include "textDataSample.h"

class textDataParser : public dataParser
{

  public:

    textDataParser();

    void parseData(void *target);
    int addDatumToContainer(std::vector<sample*> *container);
    void writeDatumOnPosition(std::vector<sample*> *container, int position);
};


#endif //RESERVOIRALGORITHM_TEXTDATAPARSER_H
