//
// Created by Tomev on 29.05.2017.
//

#include "textDataParser.h"

#include <sstream>

textDataParser::textDataParser()
{
  this->buffer = new std::string();
}

void textDataParser::parseData(void *target)
{
  std::string *line = static_cast<std::string*>(this->buffer);
  textDataSample *sampleHolder = static_cast<textDataSample*>(target);

  std::istringstream ss(*line);
  std::string value;

  sampleHolder->values.clear();

  while(getline(ss, value, ',')) sampleHolder->values.push_back(value);
}

int textDataParser::addDatumToContainer(std::vector<sample*> *container)
{
  container->push_back(new textDataSample());

  return container->size()-1;
}

void textDataParser::writeDatumOnPosition(std::vector<sample*> *container, int position)
{
  parseData(container->at(position));
}