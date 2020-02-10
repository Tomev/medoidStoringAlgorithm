#include <random>
#include <iostream>

#include <QDebug>

#include "medoidStoringAlgorithm.h"

medoidStoringAlgorithm::medoidStoringAlgorithm(std::shared_ptr<groupingAlgorithm> algorithm, unsigned int bufferSize) :
  gAlgorithm(algorithm), BUFFER_SIZE(bufferSize)
{}

void medoidStoringAlgorithm::findAndStoreMedoidsFromObjects(std::vector<std::shared_ptr<sample> > *objects, std::shared_ptr<std::vector<std::vector<std::shared_ptr<cluster> > > > target)
{
  gAlgorithm->groupObjects(objects, &clusters);
  addMedoidsOnLevel(target.get(), 0);
}

void medoidStoringAlgorithm::findAndStoreMedoidsFromClusters(std::vector<std::shared_ptr<cluster> > *container,
                                                             std::vector<std::vector<std::shared_ptr<cluster> > >  *target)
{
  qDebug() << "Start size: " << clusters.size();
  gAlgorithm->groupClusters(container, &clusters);
  qDebug() << "End size: " << clusters.size();
  addMedoidsOnLevel(target, 0);
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
  (*target)[level].clear();
  long clusterShift = target->at(level).size();

  qDebug() << "Creating summaries.";

  // Create clusters summaries
  for(unsigned int i = 0; i < clusters.size(); ++i)
  {
    // During experiments it happened so that two clusters had the same value which caused problems.
    // Until discussed further omit clusters with weight 0.
    if(clusters[i]->getWeight() == 0) continue;

    std::shared_ptr<sample> s;

    s = clusters[i].get()->getMedoid()->getObject();

    std::shared_ptr<cluster> c = std::make_shared<cluster>(cluster(clusterShift + i, s));
    c->setWeight(clusters[i]->getWeight());
    c->setVariantion(clusters[i]->getVariation());

    // Prediction
    c->_lastPrediction = clusters[i]->getLastPrediction();
    c->_deactualizationParameter = clusters[i]->getDeactualizationParameter();
    c->predictionParameters = clusters[i]->getPredictionParameters();
    c->_djVector = clusters[i]->getDjVector();
    //c->_matrixDj = clusters[i]->getDjMatrix();
    c->_j = clusters[i]->getPrognosisJ();

    c->timestamp = clusters[i]->getTimestamp();

    target->at(level).push_back(c);
  }

  clusters.clear();

  long sumWeight = 0;

  for(std::shared_ptr<cluster> c : target->at(0))
      sumWeight += c.get()->getWeight();

  qDebug() << "Clusters size: " << target->at(0).size();
  qDebug() << "Buffer size: " << BUFFER_SIZE;
}
