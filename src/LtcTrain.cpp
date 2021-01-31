#include "Arduino.h"
#include "LtcHub.h"
#include "LtcTrain.h"

LtcTrain::LtcTrain(std::string hubAddress, String hubName, Color color)
    : LtcHub(hubAddress, hubName, color)
{
}

void LtcTrain::incSpeed(bool dir)
{
    int updatedSpeed = 0;

    if (dir) {
        updatedSpeed = min(100, _currentSpeed + 10);
    } else {
        updatedSpeed = min(100, _currentSpeed - 10);
    }

    if (_currentSpeed != updatedSpeed)
    {
      setBasicMotorSpeed(0, updatedSpeed);
      _currentSpeed = updatedSpeed;
    }   
}



void LtcTrain::stop()
{
    _currentSpeed = 0;
    setBasicMotorSpeed(0, 0);
}

void LtcTrain::setSpeed(bool dir, int spd)
{

}
void LtcTrain::tick()
{
}
