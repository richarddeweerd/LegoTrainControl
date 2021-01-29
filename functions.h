#include "Lpf2Hub.h"

void printVersion(Version ver)

{
    Serial.print(ver.Major);
    Serial.print("-");
    Serial.print(ver.Minor);
    Serial.print("-");
    Serial.print(ver.Bugfix);
    Serial.print(" Build: ");
    Serial.println(ver.Build);
}
