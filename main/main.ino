#include "./utils/wifi_config.h"
#include "./utils/https_request.h"
#include "./utils/json_parser.h"
#include "./utils/data_storage.h"

unsigned long lastRequestTime = 0;
const unsigned long requestInterval = 30000;  // 30 seconds

void setup() {
  Serial.begin(115200);
  connectToWiFi();  // Initialize WiFi
  initializeStorage(); // Initialize data storage
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastRequestTime >= requestInterval) {
    lastRequestTime = currentTime;
    String jsonResponse = sendRequest(); // Make HTTPS request

    // Serial.println("JSON RESPONSE");
    // Serial.println(jsonResponse);
    bool hasChanged = compareJsonResponses(jsonResponse);  // Compare responses

    if (hasChanged) {
      Serial.println("Response has changed!");

      String chain, currency, userName, wallet;
      float amount, valueUsd;

      bool hasParsed = false;
      hasParsed = parseJsonResponse(jsonResponse, chain, amount, currency, valueUsd, userName, wallet);

      Serial.println("parse status");
      Serial.println(hasParsed);

      if (hasParsed) {
        Serial.println("Chain: " + chain);
        Serial.println("Amount: " + String(amount));
        Serial.println("Currency: " + currency);
        Serial.println("Value in USD: " + String(valueUsd));
        Serial.println("User Name: " + userName);
        Serial.println("Wallet: " + wallet);
      } else {
        Serial.println("Failed to parse JSON response.");
      }
    } else {
      Serial.println("No changes in the response.");
    }
  }
}
