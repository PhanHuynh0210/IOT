#include "globals.h" 

#define SENSOR_ID 2
#define ESPNOW_MAGIC 0xB71E10F0 

static uint8_t peerMac[] = ESPNOW_PEER_MAC;

static DHTesp dht;
static esp_now_peer_info_t peerInfo;

static bool initEspNowSender()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(false); 

  esp_wifi_set_channel(ESPNOW_WIFI_CHANNEL, WIFI_SECOND_CHAN_NONE);

  if (esp_now_init() != ESP_OK) {
    Serial.println("[ESPNOW] init failed");
    return false;
  }

  memcpy(peerInfo.peer_addr, peerMac, 6);
  peerInfo.channel = 0;   
  peerInfo.encrypt = false;
  peerInfo.ifidx = WIFI_IF_STA; 

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("[ESPNOW] add peer failed");
    return false;
  }

  Serial.println("[ESPNOW] sender ready");
  return true;
}
void TaskDHT11EspNow(void *pvParameters)
{
  (void)pvParameters;

  dht.setup(DHT11_PIN, DHTesp::DHT11);

  if (!initEspNowSender()) {
    Serial.println("[ESPNOW] init error → stop task");
    vTaskDelete(NULL);
    return;
  }

  EspNowDht20Packet pkt{};
  pkt.magic = ESPNOW_MAGIC;
  pkt.sensorId = SENSOR_ID;

  for (;;)
  {
    pkt.uptimeMs = millis();

    TempAndHumidity values = dht.getTempAndHumidity();

    if (dht.getStatus() == DHTesp::ERROR_NONE) {
      pkt.temp = values.temperature;
      pkt.humi = values.humidity;

      Serial.printf("[DHT11] OK: t=%.2f h=%.2f\n", pkt.temp, pkt.humi);
    } else {
      pkt.temp = NAN;
      pkt.humi = NAN;

      Serial.printf("[DHT11] read failed: %d\n", (int)dht.getStatus());
    }

    esp_err_t r = esp_now_send(peerMac, (uint8_t*)&pkt, sizeof(pkt));

    if (r == ESP_OK) {
      Serial.printf("[ESPNOW] sent → id=%u t=%.2f h=%.2f\n",
                    pkt.sensorId, pkt.temp, pkt.humi);
    } else {
      Serial.printf("[ESPNOW] send failed: %d\n", (int)r);
    }

    vTaskDelay(pdMS_TO_TICKS(delay_time)); 
  }
}