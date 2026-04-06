
#include "globals.h"

void setup()
{
  Serial.begin(115200);

  // Tạo semaphore và queue trước khi tạo task
  tempLowSem  = xSemaphoreCreateBinary();
  tempMidSem  = xSemaphoreCreateBinary();
  tempHighSem = xSemaphoreCreateBinary();

  humLowSem  = xSemaphoreCreateBinary();
  humMidSem  = xSemaphoreCreateBinary();
  humHighSem = xSemaphoreCreateBinary();

  lcdQueue = xQueueCreate(1, sizeof(Sensordata));
<<<<<<< HEAD


  // InitWiFi();
=======
  coreIOTQueue = xQueueCreate(1, sizeof(Sensordata));


  xTaskCreate(TaskWiFi,   "TaskWiFi",    4096, NULL, 5, 0);
  xTaskCreate(coreiot_task,   "coreiot_task",    4096, NULL, 4, 0);

>>>>>>> origin/Huynh

  xTaskCreate(TaskDHT11,   "TaskDHT11",    4096, NULL, 3, NULL);
  // xTaskCreate(TaskDHT20,   "DHT20",    4096, NULL, 3, NULL);
  xTaskCreate(TaskBlink,"TaskBlink", 4096, NULL, 2, NULL);
  xTaskCreate(TaskNeoPixel,"NeoPixel", 4096, NULL, 2, NULL);
  xTaskCreate(TaskLCD,     "LCD",      4096, NULL, 1, NULL);

<<<<<<< HEAD
  // initMQTT();  
=======
>>>>>>> origin/Huynh
}

void loop()
{
<<<<<<< HEAD
  // if (!Wifi_reconnect())
  // {
  //   return;
  // }
  // reconnectMQTT();
=======
>>>>>>> origin/Huynh
}