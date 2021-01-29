/**
    A Legoino implementation for multiple trains and a Lego remote

    (c) Copyright 2021 - Richard de Weerd

*/

#include "config.h"
//#include "Lpf2Hub.h"
#include "ltc\LtcHub.h"
#include "ltc\LtcRemote.h"
#include "ltc\LtcTrain.h"
#include "Arduino.h"

// create a hub instance
LtcRemote remote(REMOTE_ADDRESS, REMOTE_NAME, BLUE);
LtcTrain train1(T1_ADDRESS, T1_NAME, RED);
LtcTrain train2(T2_ADDRESS, T2_NAME, GREEN);

#include "functions.h"
#include "callbacks.h"

bool initialized = false;

void setup()
{
    Serial.begin(115200);
    Serial.println("Lego Train Control");
    Serial.println("Booting");

}

// main loop
void loop()
{

    if (!initialized) {
        if (!remote.isConnected() && (!remote.isIgnored())) {
            remote.connect();
        }
        if (remote.isConnected() && !train1.isConnected() && (!train1.isIgnored())) {
            train1.connect();
        }
        if (train1.isConnected() && !train2.isConnected() && (!train2.isIgnored())) {
            train2.connect();
        }

        if ((remote.isConnected() || remote.isIgnored()) && (train1.isConnected() || train1.isIgnored()) && (train2.isConnected() || train2.isIgnored()) && !initialized) {
            if (remote.isConnected()) {
                setHubCallbacks(&remote);
                setRemoteCallbacks(&remote);

            }
            if (train1.isConnected()) {
                setHubCallbacks(&train1);

            }
            if (train2.isConnected()) {
                setHubCallbacks(&train2);
            }
            initialized = true;
        }

    }
    if (remote.isNewBatLevelAvailable()) {
        Serial.print(remote.getHubName().c_str());
        Serial.print(" BatLevel: ");
        Serial.println(remote.getBatLevel());
        //        if (remote.isFwVersionAvailable()) {
        //            Serial.print("FWVersion: ");
        //            printVersion(remote.getFwVersion());
        //        }
        //        if (remote.isHwVersionAvailable()) {
        //            Serial.print("HWVersion: ");
        //            printVersion(remote.getHwVersion());
        //        }
    }
    if (train1.isNewBatLevelAvailable()) {
        Serial.print(train1.getHubName().c_str());
        Serial.print(" BatLevel: ");
        Serial.println(train1.getBatLevel());
        //        if (train1.isFwVersionAvailable()) {
        //            Serial.print("FWVersion: ");
        //            printVersion(train1.getFwVersion());
        //        }
        //        if (train1.isHwVersionAvailable()) {
        //            Serial.print("HWVersion: ");
        //            printVersion(train1.getHwVersion());
        //        }
    }

    if (train2.isNewBatLevelAvailable()) {
        Serial.print(train2.getHubName().c_str());
        Serial.print(" BatLevel: ");
        Serial.println(train2.getBatLevel());
        //        if (train2.isFwVersionAvailable()) {
        //            Serial.print("FWVersion: ");
        //            printVersion(train2.getFwVersion());
        //        }
        //        if (train2.isHwVersionAvailable()) {
        //            Serial.print("HWVersion: ");
        //            printVersion(train2.getHwVersion());
        //        }
    }


} // End of loop
