//
// Created by Tomev on 13.06.2017.
//

#ifndef MEDOIDSTORINGALGORITHM_MEDOIDSTORINGALGORITHM_H
#define MEDOIDSTORINGALGORITHM_MEDOIDSTORINGALGORITHM_H

#include <vector>
#include "dataParser.h"
#include "dataReader.h"

#include "sample.h"

class medoidStoringAlgorithm
{
  public:
    void findAndStoreMedoids(std::vector<std::vector<sample*>> target);
  private:
    dataParser *parser;
    dataReader *reader;

    std::vector<sample> buffor;

};


#endif //MEDOIDSTORINGALGORITHM_MEDOIDSTORINGALGORITHM_H
