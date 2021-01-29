#include "Arduino.h"
#include "LtcHub.h"
#include "LtcRemote.h"

LtcRemote::LtcRemote(std::string hubAddress, String hubName, Color color)
    : LtcHub(hubAddress, hubName, color)
{

}
