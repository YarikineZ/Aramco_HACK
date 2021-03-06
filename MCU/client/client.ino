#define SOUND_PIN  35 //microphone pins must be set to 32 and higher to work with WIFI
#define NOISE_PIN  32 

#include <WiFi.h>

const char* ssid     = "ESP8266";
const char* password = "1234567890";
const uint8_t ID = 5;
const char* host = "192.168.4.1";
int soundValue = 0;
int noiseValue = 0;

void setup()
{
    pinMode(SOUND_PIN, INPUT);
    pinMode(NOISE_PIN, INPUT);
  
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void senddata()
{
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    // We now create a URI for the request
    String url = "/api/login";
    url += "?id=";
    url += String(ID);
    url += "&time=";
    url += String(millis(), DEC);
    url += "&noise=";
    url += String(noiseValue);

    //Serial.print("Requesting URL: ");
    //Serial.println(url);

    // This will send the request to the server
    client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
                 
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
       }
    }
 }

void loop()
{
    soundValue = analogRead(SOUND_PIN);     // считываем показания микрофона
    noiseValue = analogRead(NOISE_PIN);     // считываем показания уровня шума
    //Serial.println(noiseValue);
     if (noiseValue > 200){
     Serial.println(noiseValue);
     senddata();}
}
