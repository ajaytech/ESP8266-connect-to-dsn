#include <ESP8266WiFi.h>
 
 //Your wifi name
const char* ssid     = "someWifiName";
//Your wifi pwd
const char* password = "SomeWifiPwd";
 
const char* host = "www.pubsub.pubnub.com";
 
void setup() {
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
 
int value = 0;
 
void loop() {
  delay(5000);
  ++value;
 
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
 //Replace the keys with your PubNub Publish and Subscribe Keys
  String url = "http://pubsub.pubnub.com/publish/pub-c-dbe2d3c6-446e-4f4e-ab73-a2a6907f653c/sub-c-7d1d2c40-16f9-11e7-b284-02ee2ddab7fe/0/esphello/0/%22Hello%20World%22";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the serveg
  client.print(String("GET ") + url  + " HTTP/1.1\r\n" +
               "Host: " + host + "r\n" +
               "Connection: Keep-Alive\r\n\r\n");
  delay(10);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}

