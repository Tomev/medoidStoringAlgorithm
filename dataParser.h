//
// Created by Tomev on 29.05.2017.
//

#ifndef RESERVOIRALGORITHM_DATAPARSER_H
#define RESERVOIRALGORITHM_DATAPARSER_H

#include <vector>

#include "sample.h"

class dataParser
{
  public:

    virtual void parseData(void *target) = 0;
    virtual int addDatumToContainer(std::vector<sample*> *container) = 0;
    virtual void writeDatumOnPosition(std::vector<sample*> *container, int position) = 0;

    void *buffer;
};


#endif //RESERVOIRALGORITHM_DATAPARSER_H
