//
// Created by Tomev on 29.05.2017.
//

#ifndef RESERVOIRALGORITHM_DATAPARSER_H
#define RESERVOIRALGORITHM_DATAPARSER_H

class dataParser
{
  public:

    virtual void parseData(void *target) = 0;
    virtual int addDatumToContainer(void *container) = 0;
    virtual void writeDatumOnPosition(void *container, int position) = 0;

    void *buffor;
};


#endif //RESERVOIRALGORITHM_DATAPARSER_H
