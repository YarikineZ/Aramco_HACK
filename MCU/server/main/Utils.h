#pragma once

#include "Const.h"

String TCPClientCommunicate(String message) {
  WiFiClient client;

  if (!client.connect(HOST, PORT)) {
    return CONNECTION_FAIL;
  }

  if (client.connected()) {
    client.println(message);
  } else {
    client.stop();
    return CONNECTION_FAIL;
  }

  // read response assuming client sends single command trailing with '\n'
  String response;
  while (client.connected() || client.available())
  {
    if (client.available())
    {
      response = client.readStringUntil('\n');
      break;
    }
  }
  client.stop();

  return response;
}

bool register_part() {
  String response = TCPClientCommunicate(String(ID) + " " + "REGISTER" + " " + WiFi.localIP().toString());

  if (response == CONNECTION_FAIL) {
    return false;
  }

  return true;
}
