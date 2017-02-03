#ifndef INITPARAMETERS_H
#define INITPARAMETERS_H

#include <QString>

class InitParameters
{
public:
    InitParameters();
    static QString configFilepath();
    static QString audioOutputFile();
    static double thresholdCorrelationValue();
};

#endif // INITPARAMETERS_H
