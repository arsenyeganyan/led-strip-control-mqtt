#pragma once

#include <PubSubClient.h>

void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void mqttSetup();
void mqttLoop();