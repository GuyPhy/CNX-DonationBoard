#include "../utils/wifi_config.h"
#include "../utils/https_request.h"
#include "../utils/json_parser.h"
#include "../utils/data_storage.h"

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
    String jsonResponse = sendRequest();  // Make HTTPS request
    bool hasChanged = compareJsonResponses(jsonResponse);  // Compare responses

    if (hasChanged) {
      Serial.println("Response has changed!");
    } else {
      Serial.println("No changes in the response.");
    }
  }
}
