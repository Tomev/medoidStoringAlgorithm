//
// Created by Tomev on 13.06.2017.
//

#ifndef MEDOIDSTORINGALGORITHM_MEDOIDSTORINGALGORITHM_H
#define MEDOIDSTORINGALGORITHM_MEDOIDSTORINGALGORITHM_H

#include <vector>
#include <set>

#include "dataParser.h"
#include "dataReader.h"
#include "sample.h"

class medoidStoringAlgorithm
{
  public:
    medoidStoringAlgorithm(dataParser *parser, dataReader *reader);
    void findAndStoreMedoids(std::vector<std::vector<std::vector<sample*>>>* target);

  private:
    dataParser *parser;
    dataReader *reader;

    std::vector<sample*> buffer;
    std::set<int> medoidsIndexes;

    // It'd be best if this was
    int BUFFOR_SIZE     = 1000;
    int MEDOIDS_NUMBER  = 10;

    void fillBufforWithData();
    void selectMedoids(std::vector<sample*>* container);
    void addMedoidsOnLevel(std::vector<std::vector<std::vector<sample *>>>* target, int level);


};


#endif //MEDOIDSTORINGALGORITHM_MEDOIDSTORINGALGORITHM_H
