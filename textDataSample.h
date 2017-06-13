//
// Created by Tomev on 13.06.2017.
//

#ifndef MEDOIDSTORINGALGORITHM_TEXTDATASAMPLE_H
#define MEDOIDSTORINGALGORITHM_TEXTDATASAMPLE_H

#include <vector>
#include <string>
#include <iostream>

#include "sample.h"

class textDataSample : public sample
{
  public:
    std::vector<std::string> values;
    void print();
};


#endif //MEDOIDSTORINGALGORITHM_TEXTDATASAMPLE_H
