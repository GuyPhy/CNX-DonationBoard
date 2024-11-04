#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <ArduinoJson.h>

bool compareJsonResponses(String newResponse) {
  static String lastResponse = "";  // Stores the previous response

  if (newResponse != lastResponse) {
    lastResponse = newResponse;
    return true;  // The response has changed
  }

  return false;  // No change in the response
}

bool parseJsonResponse(String jsonResponse, String &chain, float &amount, String &currency, float &valueUsd, String &userName, String &wallet) {
  StaticJsonDocument<1024> doc;
  DeserializationError error = deserializeJson(doc, jsonResponse);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return false;
  }

  chain = doc["chain"].as<String>();
  amount = doc["amount"].as<float>();
  currency = doc["currency"].as<String>();
  valueUsd = doc["valueUsd"].as<float>();
  userName = doc["user"]["name"].as<String>();
  wallet = doc["user"]["wallet"].as<String>();

  return true;
}

#endif
