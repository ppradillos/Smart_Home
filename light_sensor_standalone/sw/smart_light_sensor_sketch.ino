#include <ESP8266WiFi.h>

// Debug mode on (!0)/ off (0)
#define DEBUG_SERIAL_ENABLED 1

#if DEBUG_SERIAL_ENABLED
// print logs via serial port
#define DEBUG_PRINT(x)    Serial.print(x);
#define DEBUG_PRINTLN(x)  Serial.println(x);
#else
// print logs via WiFi-based protocol
#define DEBUG_PRINT(x) 
#define DEBUG_PRINTLN(x) 
#endif

// Set WiFi credentials --> Modify these values according to your local network
#define WIFI_SSID "YOUR WIFI SSID"
#define WIFI_PASS "YOUR WIFI PASSWORD"

// 10-bit ADC values. Light sensor part
const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0
int sensorValue = 0;  // value read from the pot

// LED value
int led_value = LOW;

/* Start up code */
void setup() {
#if DEBUG_SERIAL_ENABLED
  // Add a 5000ms delay to give time for the IDE to display serial port log.
  delay(5000);
  
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
#endif

  // Initialize the LED_BUILTIN pin as an output
  pinMode(LED_BUILTIN, OUTPUT);

  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Connecting to WiFi...
  DEBUG_PRINT("Connecting to ");
  DEBUG_PRINT(WIFI_SSID);

  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    DEBUG_PRINT(".");
  }

  // Connected to WiFi.
  DEBUG_PRINTLN();
  DEBUG_PRINT("Connected! IP address: ");
  DEBUG_PRINTLN(WiFi.localIP());
}

/* Main Function */
void loop() {
  // read the analog in value from the light sensor
  sensorValue = analogRead(analogInPin);
 
  // print the readings in the Serial Monitor
  DEBUG_PRINT("light sensor, digital value = ");
  DEBUG_PRINTLN(sensorValue);
  
  // 1000 ms delay between read outs
  delay(1000);

  // read the LED value and toggle its current status
  led_value = digitalRead(LED_BUILTIN);
  digitalWrite(LED_BUILTIN, !led_value);
}
