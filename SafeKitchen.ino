#include <WiFi.h>
#include <WebSocketsClient.h>
#include <DHT.h>

WebSocketsClient webSocket;
 
const char *ssid     = "AndroidAP5916";
const char *password = "caaf59io67";

unsigned long messageInterval = 5000;
bool connected = false;
bool buttonFlag = false;
// define the DHT11 sensor pin
#define DHTPIN 25
#define sensor_llama 33
#define sensor_gas 32
#define pinBuzzer 26
#define pinLed 27
#define pinBoton 14
int llama = 0;
int gas = 0;
String alerta_llama = "";
String alerta_gas = "";

// initialize the DHT11 sensor
DHT dht(DHTPIN, DHT11);
 
#define DEBUG_SERIAL Serial
void prenderLed(int pin){
  digitalWrite(pin, HIGH);
}
void apagarLed(int pin){
  digitalWrite(pin, LOW);
}
void blink(int pin){
  prenderLed(pin);
  delay(1000);
  apagarLed(pin);
  delay(1000);
 }
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            DEBUG_SERIAL.printf("[WSc] Disconnected!\n");
            connected = false;
            break;
        case WStype_CONNECTED: {
            DEBUG_SERIAL.printf("[WSc] Connected to url: %s\n", payload);
            connected = true;
 
            // send message to server when Connected
            DEBUG_SERIAL.println("[WSc] SENT: Connected");
            webSocket.sendTXT("Connected");
        }
            break;
        case WStype_TEXT:
            DEBUG_SERIAL.printf("[WSc] RESPONSE: %s\n", payload);
            break;
        case WStype_BIN:
            DEBUG_SERIAL.printf("[WSc] get binary length: %u\n", length);
            break;
                case WStype_PING:
                        // pong will be send automatically
                        DEBUG_SERIAL.printf("[WSc] get ping\n");
                        break;
                case WStype_PONG:
                        // answer to a ping we send
                        DEBUG_SERIAL.printf("[WSc] get pong\n");
                        break;
    }
 
}
void IRAM_ATTR isr(){
  buttonFlag = true;
}
void setup() {
    DEBUG_SERIAL.begin(115200);
   
//  DEBUG_SERIAL.setDebugOutput(true);
 
    DEBUG_SERIAL.println();
    DEBUG_SERIAL.println();
    DEBUG_SERIAL.println();
 
    for(uint8_t t = 4; t > 0; t--) {
        DEBUG_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
        DEBUG_SERIAL.flush();
        delay(1000);
    }
 
    WiFi.begin(ssid, password);
 
    while ( WiFi.status() != WL_CONNECTED ) {
      delay ( 500 );
      Serial.print ( "." );
    }
    DEBUG_SERIAL.print("Local IP: "); DEBUG_SERIAL.println(WiFi.localIP());
    // server address, port and URL
    webSocket.begin("192.168.52.15", 1880, "/ws/proyecto");
 
    // event handler
    webSocket.onEvent(webSocketEvent);
    // initialize the DHT11 sensor
    dht.begin();
    pinMode(sensor_llama, INPUT);
    pinMode(sensor_gas, INPUT);
    pinMode(pinBoton, INPUT_PULLUP);
    attachInterrupt(pinBoton, isr, FALLING);
    pinMode(pinBuzzer, OUTPUT);
    pinMode(pinLed, OUTPUT);
}
 
unsigned long lastUpdate = millis();
 
 
void loop() {
  if(buttonFlag){
    digitalWrite(pinLed, HIGH);
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    llama = analogRead(sensor_llama);
    gas = analogRead(sensor_gas);
    llama = map(llama,0,1023,100,0);
    delay(500);
    // send sensor data to the WebSocket server
    DEBUG_SERIAL.print("Llama: ");
    DEBUG_SERIAL.println(llama);
    DEBUG_SERIAL.print("Gas: ");
    DEBUG_SERIAL.println(gas);
    DEBUG_SERIAL.print("Temperatura: ");
    DEBUG_SERIAL.println(temperature);
    DEBUG_SERIAL.print("Humedad: ");
    DEBUG_SERIAL.println(humidity);
    if(llama > 90){
      digitalWrite(pinBuzzer, HIGH);
    }
    else if(gas > 800){
      digitalWrite(pinBuzzer, HIGH);
    }
    else{
      digitalWrite(pinBuzzer, LOW);
    }
   
      webSocket.loop();
      if (connected && lastUpdate+messageInterval<millis()){
          DEBUG_SERIAL.println("[WSc] SENT: Simple js client message!!");
          String jsonString = "{";
          jsonString += "\"Llama\":";
          jsonString += String(llama);
          jsonString += ",";
          jsonString += "\"Gas\":";
          jsonString += String(gas);
          jsonString += ",";
          jsonString += "\"Temperature\":";
          jsonString += String(temperature);
          jsonString += ",";
          jsonString += "\"Humidity\":";
          jsonString += String(humidity);
          jsonString += "}";
          DEBUG_SERIAL.println(jsonString);
          webSocket.sendTXT(jsonString);
          lastUpdate = millis();
          blink(pinLed);
          blink(pinLed);
      }
  }
  else{
    digitalWrite(pinLed, LOW);
  }
 
}
