#ifndef VOICERECOGNIZER_H
#define VOICERECOGNIZER_H
#include <string>
using namespace std;


class VoiceRecognizer
{
public:
    VoiceRecognizer();
    static double getCorrCoefficientBetweenTwoSamples(string, string);
};

#endif // VOICERECOGNIZER_H
