#include <random>
#include <iostream>

#include "medoidStoringAlgorithm.h"

#include "../kMedoidsAlgorithm/kMedoidsAlgorithm.h"

medoidStoringAlgorithm::medoidStoringAlgorithm(std::shared_ptr<groupingAlgorithm> algorithm) :
  gAlgorithm(algorithm)
{}

void medoidStoringAlgorithm::findAndStoreMedoidsFromObjects(std::vector<std::shared_ptr<sample> > *objects, std::shared_ptr<std::vector<std::vector<std::shared_ptr<cluster> > > > target)
{
  gAlgorithm->groupObjects(objects, &clusters);
  addMedoidsOnLevel(target.get(), 0);
}

void medoidStoringAlgorithm::findAndStoreMedoidsFromClusters(std::vector<std::shared_ptr<cluster> > *container,
                                                             std::shared_ptr<std::vector<std::vector<std::shared_ptr<cluster> > > > target)
{
  gAlgorithm->groupClusters(container, &clusters);
  addMedoidsOnLevel(target.get(), 0);
}



void medoidStoringAlgorithm::fillBufferWithData()
{
  buffer.clear();

  while(buffer.size() < BUFFER_SIZE)
  {
    parser->addDatumToContainer(&buffer);

    reader->getNextRawDatum(parser->buffer);
    parser->parseData(buffer.at(buffer.size()-1).get());
  }
}

void medoidStoringAlgorithm::selectMedoids(std::vector<std::shared_ptr<cluster>> *container)
{
  gAlgorithm->groupClusters(container, &clusters);
}

void medoidStoringAlgorithm::addMedoidsOnLevel(std::vector<std::vector<std::shared_ptr<cluster> > > *target, unsigned int level)
{
  // Create new level if needed
  if(target->size() == level)
    target->push_back(std::vector<std::shared_ptr<cluster>>());

  long clusterShift = target->at(level).size();


  // Create clusters summaries
  for(unsigned int i = 0; i < clusters.size(); ++i)
  {
    std::shared_ptr<sample> s;

    s = clusters[i].get()->getMedoid()->getObject();

    std::shared_ptr<cluster> c = std::make_shared<cluster>(cluster(clusterShift + i,
                                                                   s));

    c.get()->setWeight(clusters[i].get()->getWeight());

    target->at(level).push_back(c);
  }

  clusters.clear();

  long sumWeight = 0;

  for(std::shared_ptr<cluster> c : target->at(0))
      sumWeight += c.get()->getWeight();

  std::cout << "Summaric weight: " << sumWeight << ".\n";

  // Check if there are next level clusters
  if(target->at(level).size() >= BUFFER_SIZE)
  {
    //clusters.push_back(std::vector<std::shared_ptr<cluster>>());

    std::cout << "Next level - " << level + 1 << ".\n";

    selectMedoids(&(target->at(level)));

    std::cout << "Medoids selected.";

    addMedoidsOnLevel(target, level+1);

    target->at(level).clear();
  }
}
