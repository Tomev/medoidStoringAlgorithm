#include <random>
#include <iostream>

#include <QDebug>

#include "medoidStoringAlgorithm.h"

medoidStoringAlgorithm::medoidStoringAlgorithm(std::shared_ptr<groupingAlgorithm> algorithm, unsigned int bufferSize) :
  gAlgorithm(algorithm), BUFFER_SIZE(bufferSize)
{
    _gen = QRandomGenerator(0);
}

void medoidStoringAlgorithm::findAndStoreMedoidsFromObjects(std::vector<std::shared_ptr<sample> > *objects, std::vector<std::shared_ptr<cluster> > *target)
{
  gAlgorithm->groupObjects(objects, &clusters);
  addMedoidsToStorage(target);
}

void medoidStoringAlgorithm::findAndStoreMedoidsFromClusters(std::vector<std::shared_ptr<cluster> > *container,
                                                             std::vector<std::shared_ptr<cluster> > *target)
{
  clusters.clear();
  gAlgorithm->groupClusters(container, &clusters);
  addMedoidsToStorage(target);

  /*
  qDebug() << "Random deletion.";
  int rand = _gen.bounded(0, container->size() + 1);
  container->erase(container->begin() + rand, container->begin() + rand + 1);

  (*target)[0].clear();

  for(auto c : *container){
    (*target)[0].push_back(c);
  }
  */

  /*
  qDebug() << "First subcluster after grouping.";
  gAlgorithm->groupClusters(container, &clusters);

  (*target)[0].clear();

  for(auto c : clusters){
      std::vector<std::shared_ptr<cluster>> subclusters;
      c->getSubclusters(&subclusters);
      if(c->getWeight() > 0)
        (*target)[0].push_back(subclusters[0]);
  }
  */

  /*
  qDebug() << "Random subcluster after grouping.";
  gAlgorithm->groupClusters(container, &clusters);

  (*target).clear();

  for(auto c : clusters){
      std::vector<std::shared_ptr<cluster>> subclusters;
      c->getSubclusters(&subclusters);
      if(c->getWeight() > 0){
        int rand = _gen.bounded(0, subclusters.size() - 1);
        (*target).push_back(subclusters[rand]);
      }
  }
  */
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

void medoidStoringAlgorithm::addMedoidsToStorage(std::vector<std::shared_ptr<cluster> > *target)
{
  target->clear();

  qDebug() << "Creating summaries.";

  // Create clusters summaries
  for(unsigned int i = 0; i < clusters.size(); ++i)
  {
    // During experiments it happened so that two clusters had the same value which caused problems.
    // Until discussed further omit clusters with weight 0.
    if(clusters[i]->getWeight() == 0) continue;

    std::shared_ptr<cluster> c;

    if(clusters[i]->size() == 1){
        std::vector<std::shared_ptr<cluster>> subclusters;
        clusters[i]->getSubclusters(&subclusters);
        c = subclusters[0];
    }
    else {
        std::shared_ptr<sample> s;

        s = clusters[i].get()->getMedoid()->getObject();

        c = std::make_shared<cluster>(cluster(i, s));
        c->setWeight(clusters[i]->getWeight());
        c->setVariantion(clusters[i]->getVariation());

        // Prediction
        c->_lastPrediction = clusters[i]->getLastPrediction();
        c->_deactualizationParameter = clusters[i]->getDeactualizationParameter();
        c->predictionParameters = clusters[i]->getPredictionParameters();
        c->_djVector = clusters[i]->getDjVector();
        c->_j = clusters[i]->getPrognosisJ();

        c->timestamp = clusters[i]->getTimestamp();
    }

    target->push_back(c);
  }



  clusters.clear();

  long sumWeight = 0;

  for(std::shared_ptr<cluster> c : *target)
      sumWeight += c.get()->getWeight();

  qDebug() << "Clusters size: " << target->size();
  qDebug() << "Buffer size: " << BUFFER_SIZE;
}
