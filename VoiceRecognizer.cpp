#include "VoiceRecognizer.h"

VoiceRecognizer::VoiceRecognizer()
{

}

double VoiceRecognizer::getCorrCoefficientBetweenTwoSamples(string firstFilename, string secondFilename)
{
//    if (mclInitializeApplication(nullptr, 0))
//    {
//        if (mclmcrInitialize())
//        {
//            if (execAllInitialize())
//            {
//                double corrCoeff = ERROR_VAL;
//                mwArray mwCorrCoeff;
//                mwArray mwFirstFile(firstFilename.c_str());
//                mwArray mwSecondFile(secondFilename.c_str());
//                execAll(1, mwCorrCoeff, mwFirstFile, mwSecondFile);
//                mwCorrCoeff.GetData(&corrCoeff, 1);
//                return corrCoeff;
//            }
//            else
//                cout << "Failed to initialize add lib";
//        }
//        else
//            cout << "Failed to initialize mcr";
//    }
//    else
//        cout << "Failed to initialize application";
//    return ERROR_VAL;
    return 0.3;
}
