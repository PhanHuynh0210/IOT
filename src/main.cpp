
#include "globals.h"


void setup() {
  Serial.begin(115200);

  xTaskCreatePinnedToCore(
    TaskDHT11EspNow,
    "DHT11_ESPNOW",
    4096,
    NULL,
    1,
    NULL,
    1
  );
}

void loop() {}