// TelemetryBroadcastModule.h
#pragma once

#include "modules/SinglePortModule.h"
#include "mesh/MeshService.h"
#include "mesh/Position.h"
#include "mesh/Hardware.h"

class TelemetryBroadcastModule : public SinglePortModule {
public:
    TelemetryBroadcastModule();
    void setup() override;
    void loop() override;

private:
    unsigned long lastSend;
};