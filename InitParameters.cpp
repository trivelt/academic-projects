#include "InitParameters.h"

InitParameters::InitParameters()
{
}

QString InitParameters::configFilepath()
{
    return "/home/maciej/biometryConfig.xml";
}

QString InitParameters::audioOutputFile()
{
    return "/home/maciej/tmpAudio.wav";
}

double InitParameters::thresholdCorrelationValue()
{
    return 0.2;
}
