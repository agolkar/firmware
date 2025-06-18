// TelemetryBroadcastModule.cpp
#include "TelemetryBroadcastModule.h"
#include "mesh/Logging.h"
#include <string>

TelemetryBroadcastModule::TelemetryBroadcastModule()
    : SinglePortModule(PRIVATE_APP), lastSend(0) {}

void TelemetryBroadcastModule::setup() {
    LOGi("TelemetryBroadcastModule setup");
    lastSend = millis();
}

void TelemetryBroadcastModule::loop() {
    if (millis() - lastSend >= 30000) {
        lastSend = millis();

        Position pos = MeshService::getInstance().getPosition();
        float rssi = MeshService::getInstance().getRadioRSSI();
        float snr = MeshService::getInstance().getRadioSNR();
        float temp = Hardware::getInternalTempC();
        int battery = Hardware::batteryLevel();

        std::string message = "ID:" + std::to_string(Hardware::getDeviceId());
        message += " RSSI:" + std::to_string(rssi);
        message += " SNR:" + std::to_string(snr);
        message += " GPS:" + std::to_string(pos.latitude) + "," + std::to_string(pos.longitude);
        message += " ALT:" + std::to_string(pos.altitude);
        message += " TEMP:" + std::to_string(temp);
        message += " BAT:" + std::to_string(battery);

        PacketPtr packet = allocPacket();
        packet->payload.assign(message.begin(), message.end());
        sendToMesh(packet);

        LOGi("Sent telemetry broadcast: %s", message.c_str());
    }
}
