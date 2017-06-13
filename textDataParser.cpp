//
// Created by Tomev on 29.05.2017.
//

#include "textDataParser.h"

#include <sstream>

textDataParser::textDataParser()
{
  this->buffor = new std::string();
}

void textDataParser::parseData(void *target)
{
  std::string *line = static_cast<std::string*>(this->buffor);
  textDataSample *sampleHolder = static_cast<textDataSample*>(target);

  std::istringstream ss(*line);
  std::string value;

  sampleHolder->values.clear();

  while(getline(ss, value, ',')) sampleHolder->values.push_back(value);

}

int textDataParser::addDatumToContainer(void *container)
{
  std::vector<sample*> *samples = static_cast<std::vector<sample*>*>(container);
  samples->push_back(new textDataSample());

  return samples->size();
}

void textDataParser::writeDatumOnPosition(void *container, int position)
{
  parseData(static_cast<std::vector<sample*>*>(container)->at(position));
}