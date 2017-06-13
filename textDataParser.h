//
// Created by Tomev on 29.05.2017.
//

#ifndef RESERVOIRALGORITHM_TEXTDATAPARSER_H
#define RESERVOIRALGORITHM_TEXTDATAPARSER_H

/*
 * Parsing from .arff files to sample.
 */

#include "dataParser.h"
#include "textDataSample.h"

#include <string>
#include <vector>
#include <c++/iostream>

class textDataParser : public dataParser
{

  public:

    textDataParser();

    void parseData(void *target);
    int addDatumToContainer(void *container);
    void writeDatumOnPosition(void *container, int position);
};


#endif //RESERVOIRALGORITHM_TEXTDATAPARSER_H
