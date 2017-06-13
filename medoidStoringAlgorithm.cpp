//
// Created by Tomev on 13.06.2017.
//

#include <random>
#include <iostream>

#include "medoidStoringAlgorithm.h"

medoidStoringAlgorithm::medoidStoringAlgorithm(dataParser *parser, dataReader *reader) :
reader(reader), parser(parser)
{}

void medoidStoringAlgorithm::findAndStoreMedoids(std::vector<std::vector<std::vector<sample *>>> *target)
{
  int i = 0;

  while(reader->hasMoreData())
  {
    std::cout << "Iteration: " << i << std::endl;
    ++i;

    fillBufforWithData();
    selectMedoids(&buffor);
    addMedoidsOnLevel(target, 0);
  }
}

void medoidStoringAlgorithm::fillBufforWithData()
{
  buffor.clear();

  while(buffor.size() < BUFFOR_SIZE)
  {
    parser->addDatumToContainer(&buffor);

    reader->getNextRawDatum(parser->buffor);
    parser->parseData(buffor.at(buffor.size()-1));
  }
}

void medoidStoringAlgorithm::selectMedoids(std::vector<sample *> *container)
{
  // This method temporarily selects objects at random.
  medoidsIndexes.clear();

  while(medoidsIndexes.size() < MEDOIDS_NUMBER)
  {
    medoidsIndexes.insert(rand() % container->size());
  }
}

void medoidStoringAlgorithm::addMedoidsOnLevel(std::vector<std::vector<std::vector<sample *>>>* target, int level)
{
  if(target->size() == level)
  {
    target->push_back(std::vector<std::vector<sample*>>());
    target->at(level).push_back(std::vector<sample*>());
  }

  if(target->at(level).back().size() == BUFFOR_SIZE) target->at(level).push_back(std::vector<sample*>());

  while(!medoidsIndexes.empty())
  {
    target->at(level).back().push_back(buffor.at(*medoidsIndexes.begin()));

    medoidsIndexes.erase(medoidsIndexes.begin());
  }

  if(target->at(level).back().size() == BUFFOR_SIZE)
  {
    selectMedoids(&(target->at(level).back()));
    addMedoidsOnLevel(target, level+1);
  }
}
