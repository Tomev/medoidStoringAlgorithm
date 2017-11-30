#ifndef MEDOIDSTORINGALGORITHM_MEDOIDSTORINGALGORITHM_H
#define MEDOIDSTORINGALGORITHM_MEDOIDSTORINGALGORITHM_H

#include <vector>
#include <set>
#include <memory>

#include "../../Reservoir_sampling/sample.h"
#include "../../Reservoir_sampling/dataParser.h"
#include "../../Reservoir_sampling/dataReader.h"

#include "../kMedoidsAlgorithm/groupingAlgorithm/groupingAlgorithm.h"

class medoidStoringAlgorithm
{
  public:
    medoidStoringAlgorithm(std::shared_ptr<groupingAlgorithm> algorithm);

    void findAndStoreMedoids(std::vector<std::shared_ptr<sample> > *objects,
                             std::shared_ptr<std::vector<std::vector<std::shared_ptr<cluster> > > > target);


  private:

    std::unique_ptr<dataParser> parser;
    std::unique_ptr<dataReader> reader;
    std::shared_ptr<groupingAlgorithm> gAlgorithm;

    std::vector<std::shared_ptr<sample>> buffer;
    std::vector<std::shared_ptr<cluster>> clusters;
    std::set<int> medoidsIndexes;

    unsigned int BUFFER_SIZE = 100;

    void fillBufferWithData();
    void selectMedoids(std::vector<std::shared_ptr<cluster>> *container);
    void addMedoidsOnLevel(std::vector<std::vector<std::shared_ptr<cluster>>>* target, unsigned int level);

};


#endif //MEDOIDSTORINGALGORITHM_MEDOIDSTORINGALGORITHM_H
