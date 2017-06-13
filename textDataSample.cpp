//
// Created by Tomev on 13.06.2017.
//

#include "textDataSample.h"

void textDataSample::print()
{
    std::cout << "Data: ";

    for(int i = 0; i < values.size(); ++i)
    {
      std::cout << values.at(i) << ", ";
    }

    std::cout << std::endl;
}
