#include "TaskDHT20.h"

<<<<<<< HEAD
#define MY_SCL 11
#define MY_SDA 12
#define LED_PIN 48

QueueHandle_t delayQueue;

DHT20 dht20;

void TaskBlinkLED(void *pvParameters){
    TickType_t delayTime = pdMS_TO_TICKS(1000);

    while (true){
        xQueueReceive(delayQueue, &delayTime, 0);
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        vTaskDelay(delayTime);
    }
    
    
}

void TaskTemp(void *pvParameters)
{
    Wire.begin(MY_SCL, MY_SDA);
    dht20.begin();
    pinMode(LED_PIN, OUTPUT);

    delayQueue = xQueueCreate(1, sizeof(TickType_t));

    xTaskCreate(TaskBlinkLED, "TaskBlinkLED", 2048, NULL, 1, NULL);
=======
#define LED_PIN 48


DHT20 dht20;


void TaskDHT20(void *pvParameters)
{
   Sensordata data;
    
    tempLowSem  = xSemaphoreCreateBinary();
    tempMidSem  = xSemaphoreCreateBinary();
    tempHighSem = xSemaphoreCreateBinary();

    humLowSem  = xSemaphoreCreateBinary();
    humMidSem  = xSemaphoreCreateBinary();
    humHighSem = xSemaphoreCreateBinary();

    lcdQueue = xQueueCreate(1, sizeof(Sensordata));
>>>>>>> origin/Huynh

    while (true)
    {
        if (dht20.read() == DHT20_OK)
        {
<<<<<<< HEAD
            float t = dht20.getTemperature();
            Serial.println(t);

            TickType_t delayValue;

            if (t < 30)
            {
                delayValue = pdMS_TO_TICKS(1000);
            }
            else if (t < 35)
            {
                delayValue = pdMS_TO_TICKS(500);
            }
            else
            {
                delayValue = pdMS_TO_TICKS(200);
            }

            xQueueOverwrite(delayQueue, &delayValue);
=======
            data.temp = dht20.getTemperature();
            data.humi = dht20.getHumidity();

            Serial.print("DHT20 OK: ");
            Serial.print(data.temp);
            Serial.print("C ");
            Serial.print(data.humi);
            Serial.println("%");

            if (data.temp < 30){
                xSemaphoreGive(tempLowSem);
            }
            else if (data.temp < 35){
                xSemaphoreGive(tempMidSem);
            }
            else{
                xSemaphoreGive(tempHighSem);
            }

            // task2
            if (data.humi < 30){
                xSemaphoreGive(humLowSem);
            }
            else if (data.humi < 35){
                xSemaphoreGive(humMidSem);
            }
            else{
                xSemaphoreGive(humHighSem);
            }

            // Task 3
            xQueueOverwrite(lcdQueue, &data);
>>>>>>> origin/Huynh
        }

        vTaskDelay(pdMS_TO_TICKS(3000)); 
    }
}



