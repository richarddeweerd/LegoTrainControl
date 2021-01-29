/*
    LtcRemote.h - Library to extend the LegoIno Hub library.
    Created by Richard de Weerd, January 26, 2021.
*/

#ifndef LtcRemote_h
#define LtcRemote_h

#include "Arduino.h"
#include "Lpf2Hub.h"

class LtcTrain: public LtcHub
{
    public:
        LtcTrain(std::string hubAddress, String hubName, Color color);
        void setSpeed(bool dir, int spd);
        void tick();

        void incSpeed(bool dir);
        void stop();

    private:
        int _currentSpeed;
};

#endif
