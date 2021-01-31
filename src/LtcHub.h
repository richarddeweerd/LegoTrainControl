/*
    LtcHub.h - Library to extend the LegoIno Hub library.
    Created by Richard de Weerd, January 26, 2021.
*/

#ifndef LtcHub_h
#define LtcHub_h

#include "Arduino.h"
#include "Lpf2Hub.h"

class LtcHub: public Lpf2Hub
{
    public:
        LtcHub(std::string hubAddress, String hubName, Color color);
        LtcHub();
        void connect();




        bool isIgnored() {return _isIgnored;};

        void setRssi(int rssi) {_rssi = rssi; _newRssiAvailable = true;};
        void setBatLevel(uint8_t batLevel) {_batLevel = batLevel; _newBatLevelAvailable = true;};
        void setFwVersion(Version ver) {_fwVersion = ver; _isFwVersionAvailable = true;};
        void setHwVersion(Version ver) {_hwVersion = ver; _isHwVersionAvailable = true;};

        int getRssi() {_newRssiAvailable = false; return _rssi;};
        uint8_t getBatLevel() {_newBatLevelAvailable = false; return _batLevel;};

        Version getFwVersion() {return _fwVersion;};
        Version getHwVersion() {return _hwVersion;};


        bool isNewRssiAvailable() {return _newRssiAvailable;};
        bool isNewBatLevelAvailable() {return _newBatLevelAvailable;};
        bool isFwVersionAvailable() {return _isFwVersionAvailable;};
        bool isHwVersionAvailable() {return _isHwVersionAvailable;};

        std::string _hubAddress;
        String _hubNameStr;
        char _hubNameArr[14];

        Color _color;


    private:
        bool _isIgnored;
        bool _scanning;
        uint32_t _scanStart;

        bool _isFwVersionAvailable;
        bool _isHwVersionAvailable;
        int _rssi;
        uint8_t _batLevel;
        bool _newRssiAvailable;
        bool _newBatLevelAvailable;
        Version _fwVersion;
        Version _hwVersion;

};

#endif
