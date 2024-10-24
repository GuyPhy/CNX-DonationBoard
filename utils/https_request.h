#ifndef HTTPS_REQUEST_H
#define HTTPS_REQUEST_H

#include <WiFiClientSecure.h>

String sendRequest() {
  const char* host = "mainnet.serve.giveth.io";
  const int httpsPort = 443;

  WiFiClientSecure client;
  client.setInsecure();  // Use this for insecure connection (skip certificate validation)

  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection failed!");
    return "";
  }

  // Create the HTTPS request
  String postData = "{\"operationName\":\"DonationsByProjectId\",\"variables\":{\"projectId\":14410,\"take\":10,\"skip\":0,\"orderBy\":{\"field\":\"CreationDate\",\"direction\":\"DESC\"},\"status\":\"verified\"},\"query\":\"fragment DonationCoreFields ...\"}";
  String request = String("POST ") + "/graphql HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Content-Type: application/json\r\n" +
                   "Content-Length: " + postData.length() + "\r\n" +
                   "Connection: close\r\n\r\n" + postData;

  client.print(request);

  // Read response
  String response = "";
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }

  while (client.available()) {
    response += client.readString();
  }

  client.stop();
  return response;
}

#endif
