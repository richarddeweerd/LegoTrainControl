
byte portLeft = (byte)PoweredUpRemoteHubPort::LEFT;
byte portRight = (byte)PoweredUpRemoteHubPort::RIGHT;

void hubPropertyChangeCallback(void *hub, HubPropertyReference hubProperty, uint8_t *pData)
{
    LtcHub *myHub = (LtcHub *)hub;

    if (hubProperty == HubPropertyReference::RSSI) {
        myHub->setRssi(myHub->parseRssi(pData));
        return;
    }

    if (hubProperty == HubPropertyReference::BATTERY_VOLTAGE) {
        myHub->setBatLevel(myHub->parseBatteryLevel(pData));
        return;
    }

    if (hubProperty == HubPropertyReference::BUTTON) {
        Serial.print(myHub->getHubName().c_str());
        Serial.print(": ");
        Serial.print("Button: ");
        Serial.println((byte)myHub->parseHubButton(pData), HEX);
        return;
    }

    if (hubProperty == HubPropertyReference::FW_VERSION) {
        myHub->setFwVersion(myHub->parseVersion(pData));
        return;
    }

    if (hubProperty == HubPropertyReference::HW_VERSION) {
        myHub->setHwVersion(myHub->parseVersion(pData));
        return;
    }
}

void remoteCallback(void *hub, byte portNumber, DeviceType deviceType, uint8_t *pData)
{
    Lpf2Hub *myRemoteHub = (Lpf2Hub *)hub;



    Serial.print("sensorMessage callback for port: ");
    //Serial.println(portNumber, DEC);
    if (deviceType == DeviceType::REMOTE_CONTROL_BUTTON) {
        ButtonState buttonState = myRemoteHub->parseRemoteButton(pData);
        Serial.print("Buttonstate: ");
        Serial.println((byte)buttonState, HEX);

        // Do the logic for left buttons of remote control and Train Hub 1
        if (portNumber == (byte)portLeft && buttonState == ButtonState::UP) {
            train1.incSpeed(true);
        } else if (portNumber == (byte)portLeft && buttonState == ButtonState::DOWN) {
            train1.incSpeed(false);
        } else if (portNumber == (byte)portLeft && buttonState == ButtonState::STOP) {
            train1.stop();
        }


        Serial.print("Current speed train 1:");
        //Serial.println(currentSpeedTrain1, DEC);

        // Do the logic for right buttons of remote control and Train Hub 2
        if (portNumber == (byte)portRight && buttonState == ButtonState::UP) {
            train2.incSpeed(true);
        } else if (portNumber == (byte)portRight && buttonState == ButtonState::DOWN) {
            train2.incSpeed(false);
        } else if (portNumber == (byte)portRight && buttonState == ButtonState::STOP) {
            train2.stop();
        }

        Serial.print("Current speed train 2:");
        //Serial.println(currentSpeedTrain2, DEC);
    }

}

void setHubCallbacks(LtcHub * hub)
{
    hub->activateHubPropertyUpdate(HubPropertyReference::BATTERY_VOLTAGE, hubPropertyChangeCallback);
    delay(50);
    hub->activateHubPropertyUpdate(HubPropertyReference::BUTTON, hubPropertyChangeCallback);
    delay(50);
    hub->activateHubPropertyUpdate(HubPropertyReference::RSSI, hubPropertyChangeCallback);

    // FW/HW version properties and battery type need a explicit request to get the values back because they does not change over time
    if (!hub->isFwVersionAvailable()) {
        hub->requestHubPropertyUpdate(HubPropertyReference::FW_VERSION, hubPropertyChangeCallback);
        delay(100);
    }
    if (!!hub->isHwVersionAvailable()) {
        hub->requestHubPropertyUpdate(HubPropertyReference::HW_VERSION, hubPropertyChangeCallback);
        delay(100);
    }
}

void setRemoteCallbacks(LtcHub * hub)
{
    hub->activatePortDevice(portLeft, remoteCallback);
    delay(50);
    hub->activatePortDevice(portRight, remoteCallback);
    delay(50);
}
