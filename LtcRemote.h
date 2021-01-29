/*
    LtcTrain.h - Library to extend the LegoIno Hub library.
    Created by Richard de Weerd, January 26, 2021.
*/

#ifndef LtcTrain_h
#define LtcTrain_h

#include "Arduino.h"
#include "Lpf2Hub.h"

class LtcRemote: public LtcHub
{
    public:
        LtcRemote(std::string hubAddress, String hubName, Color color);

    private:

};

#endif
