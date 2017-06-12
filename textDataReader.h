/*
  Created by Tomev on 29.05.2017.

  Class meant to read txt files (in this case .arff)
  from data stream repository:

  http://www.cse.fau.edu/~xqzhu/stream.html.

*/


#ifndef RESERVOIRALGORITHM_TEXTDATAREADER_H
#define RESERVOIRALGORITHM_TEXTDATAREADER_H

#include "dataReader.h"

#include <fstream>
#include <string>

class textDataReader : public dataReader
{
  public:
    textDataReader(std::ifstream *sourceFile);
    void getNextRawDatum(void *target);

  private:
    std::ifstream *sourceFile;

};


#endif //RESERVOIRALGORITHM_TEXTDATAREADER_H
