#include "./utils/wifi_config.h"
#include "./utils/https_request.h"
#include "./utils/json_parser.h"
#include "./utils/data_storage.h"

#define GPIOPINOUT 0
#include <MatrixHardware_ESP32_V0.h>
#include <Arduino.h>
#include <SmartMatrix.h>

#define COLOR_DEPTH 24
const uint16_t kMatrixWidth = 64;             // Adjust for your display's width
const uint16_t kMatrixHeight = 32;            // Adjust for your display's height
const uint8_t kRefreshDepth = 36;
const uint8_t kDmaBufferRows = 4;
const uint8_t kPanelType = SM_PANELTYPE_HUB75_32ROW_MOD16SCAN;
const uint32_t kMatrixOptions = (SM_HUB75_OPTIONS_NONE);
const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(scrollingLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);

rgb24 textColor = {255, 255, 255};  // Default text color

unsigned long lastRequestTime = 0;
const unsigned long requestInterval = 30000;  // 30 seconds

void setup() {
  Serial.begin(115200);
  connectToWiFi();          // Initialize WiFi
  initializeStorage();      // Initialize data storage
  
  // Initialize display
  matrix.addLayer(&scrollingLayer);
  matrix.begin();
  matrix.setBrightness(80);      // Adjust brightness level as needed
  scrollingLayer.setMode(wrapForward);
  scrollingLayer.setColor(textColor);
  scrollingLayer.setSpeed(50);   // Adjust scrolling speed as desired
  scrollingLayer.setFont(font6x10); // Set font; change to desired size or style
  scrollingLayer.setOffsetFromTop((kMatrixHeight / 2) - 5);
  
  // Display initial message
  scrollingLayer.start("Welcome to the LED scrolling text display!", -1);
}

void displayText(const String &text) {
  scrollingLayer.stop();              // Stop any previous scrolling
  scrollingLayer.start(text.c_str(), -1);  // Start scrolling the new text, repeat indefinitely
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastRequestTime >= requestInterval) {
    lastRequestTime = currentTime;
    String jsonResponse = sendRequest();  // Make HTTPS request

    bool hasChanged = compareJsonResponses(jsonResponse);  // Compare responses

    if (hasChanged) {
      Serial.println("Response has changed!");

      String chain, currency, userName, wallet;
      float amount, valueUsd;

      bool hasParsed = parseJsonResponse(jsonResponse, chain, amount, currency, valueUsd, userName, wallet);

      if (hasParsed) {
        Serial.println("Chain: " + chain);
        Serial.println("Amount: " + String(amount));
        Serial.println("Currency: " + currency);
        Serial.println("Value in USD: " + String(valueUsd));
        Serial.println("User Name: " + userName);
        Serial.println("Wallet: " + wallet);

        // Display parsed data on the LED panel
        String displayMessage = "User: " + userName + " donated " + String(amount) + " " + currency + " (USD " + String(valueUsd) + ")";
        displayText(displayMessage);
      } else {
        Serial.println("Failed to parse JSON response.");
      }
    } else {
      Serial.println("No changes in the response.");
    }
  }
}

//#include "./utils/wifi_config.h"
//#include "./utils/https_request.h"
//#include "./utils/json_parser.h"
//#include "./utils/data_storage.h"
//#include "LEDTextDisplay.h"
//
//unsigned long lastRequestTime = 0;
//const unsigned long requestInterval = 30000;  // 30 seconds
//LEDTextDisplay display; //Create a display object for HUB75 32x64 board 
//
//void setup() {
//  Serial.begin(115200);
//  connectToWiFi();  // Initialize WiFi
//  initializeStorage(); // Initialize data storage
//  display.begin();
//  display.displayText("Welcome to the LED scrolling text display!");
//}
//
//void loop() {
//  unsigned long currentTime = millis();
//
//  if (currentTime - lastRequestTime >= requestInterval) {
//    lastRequestTime = currentTime;
//    String jsonResponse = sendRequest(); // Make HTTPS request
//
//    bool hasChanged = compareJsonResponses(jsonResponse);  // Compare responses
//
//    if (hasChanged) {
//      Serial.println("Response has changed!");
//
//      String chain, currency, userName, wallet;
//      float amount, valueUsd;
//
//      bool hasParsed = false;
//      hasParsed = parseJsonResponse(jsonResponse, chain, amount, currency, valueUsd, userName, wallet);
//
//      Serial.println("parse status");
//      Serial.println(hasParsed);
//
//      if (hasParsed) {
//        Serial.println("Chain: " + chain);
//        Serial.println("Amount: " + String(amount));
//        Serial.println("Currency: " + currency);
//        Serial.println("Value in USD: " + String(valueUsd));
//        Serial.println("User Name: " + userName);
//        Serial.println("Wallet: " + wallet);
//      } else {
//        Serial.println("Failed to parse JSON response.");
//      }
//    } else {
//      Serial.println("No changes in the response.");
//    }
//  }
//}
