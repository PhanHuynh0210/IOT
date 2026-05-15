#ifndef GLOBALS_H
#define GLOBALS_H

#define delay_time 7000

// include libraries
#include <Wire.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <DHTesp.h>
#include <PubSubClient.h>
#include <Arduino.h>
///
#include "../src/device/TaskDHT11EspNow.h"

// ===== DHT11 config =====
#ifndef DHT11_PIN
#define DHT11_PIN 23
#endif

// ===== ESP-NOW config =====
// IMPORTANT: set this to your BTL-IOT (gateway) WiFi MAC address.
// You can read the MAC on the gateway via Serial: WiFi.macAddress().
#ifndef ESPNOW_PEER_MAC 
#define ESPNOW_PEER_MAC {0x98, 0xA3, 0x16, 0xC0, 0x1A, 0x48}
#endif

// Must match the AP channel that the gateway connects to.
// If gateway is connected to WiFi, sensor must use the same channel for ESP-NOW.
#ifndef ESPNOW_WIFI_CHANNEL
#define ESPNOW_WIFI_CHANNEL 3
#endif

typedef struct __attribute__((packed)) {
  uint32_t magic;      // 0xB71E10T0
  uint8_t  sensorId;   // custom id
  float    temp;
  float    humi;
  uint32_t uptimeMs;   // sender millis()
} EspNowDht20Packet;

#endif