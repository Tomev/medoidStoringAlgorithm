#ifndef MEDOIDSTORINGALGORITHM_MEDOIDSTORINGALGORITHM_H
#define MEDOIDSTORINGALGORITHM_MEDOIDSTORINGALGORITHM_H

#include <vector>
#include <set>
#include <memory>

#include "../../Reservoir_sampling/sample.h"
#include "../../Reservoir_sampling/dataParser.h"
#include "../../Reservoir_sampling/dataReader.h"

#include "../kMedoidsAlgorithm/groupingAlgorithm/groupingAlgorithm.h"

#include <QRandomGenerator>

class medoidStoringAlgorithm
{
  public:
    medoidStoringAlgorithm(std::shared_ptr<groupingAlgorithm> algorithm, unsigned int bufferSize);

    void findAndStoreMedoidsFromObjects(std::vector<std::shared_ptr<sample> > *objects,
                                        std::vector<std::shared_ptr<cluster> > *target);
    void findAndStoreMedoidsFromClusters(std::vector<std::shared_ptr<cluster>> *container,
        std::vector<std::shared_ptr<cluster> > *target);


  private:

    QRandomGenerator _gen;

    std::unique_ptr<dataParser> parser;
    std::unique_ptr<dataReader> reader;
    std::shared_ptr<groupingAlgorithm> gAlgorithm;

    std::vector<std::shared_ptr<sample>> buffer;
    std::vector<std::shared_ptr<cluster>> clusters;
    std::set<int> medoidsIndexes;

    unsigned int BUFFER_SIZE = 1000;

    void fillBufferWithData();
    void selectMedoids(std::vector<std::shared_ptr<cluster>> *container);
    void addMedoidsToStorage(std::vector<std::shared_ptr<cluster>> *target);

};


#endif //MEDOIDSTORINGALGORITHM_MEDOIDSTORINGALGORITHM_H
