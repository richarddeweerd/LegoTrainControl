/*
    LtcHub.cpp - Library to extend the LegoIno Hub library.
    Created by Richard de Weerd, January 26, 2021.
*/

#include "Arduino.h"
#include "LtcHub.h"
#include "Lpf2Hub.h"



LtcHub::LtcHub()
{

}

LtcHub::LtcHub(std::string hubAddress, String hubName, Color color)
{
    _hubAddress = hubAddress;
    _hubNameStr = hubName;
    hubName.toCharArray(_hubNameArr, 14);
    _color = color;
    _isIgnored = false;
    _scanning = false;
    _newRssiAvailable = false;
    _newBatLevelAvailable = false;
    _isFwVersionAvailable = false;
    _isHwVersionAvailable = false;

}


void LtcHub::connect()
{
    if (!isConnected() && !isConnecting() ) {
        if (!_scanning) {
            _scanning = true;
            _scanStart = millis();
            init(_hubAddress);
            Serial.println("Connecting...");
        } else {
            if (_scanStart + 6000 <= millis()) {
                _scanning = false;
            }
        }
    }
    // connect flow. Search for BLE services and try to connect if the uuid of the hub is found
    if (isConnecting()) {
        connectHub();
        if (isConnected()) {
            Serial.println("Connected to HUB");
            Serial.print("Hub address: ");
            Serial.println(getHubAddress().toString().c_str());
            delay(250);
            setHubName(_hubNameArr);
            delay(250);
            Serial.print("Hub name: ");
            Serial.println(getHubName().c_str());
            delay(250);
            setLedColor(_color);

            delay(2500);
        }
    }
}
