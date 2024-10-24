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

#endif
