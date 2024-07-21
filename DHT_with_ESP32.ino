#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define BLYNK_TEMPLATE_ID "TMPL3l8X9dcVL"
#define BLYNK_TEMPLATE_NAME "DHT 11"
#define BLYNK_AUTH_TOKEN "KK2vsqCzKDRLI51aQpa05xqTDThR_cWx"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "eRRoR@4o4";
char pass[] = "1223334444";
#define DHTPIN 4 // GPIO pin
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup() {
Serial.begin(9600);
Serial.println(F("DHT11 test!"));
Blynk.begin(auth, ssid, pass);
dht.begin();
}
void loop() {
  Blynk.run();
delay(10);
float humidity = dht.readHumidity();
float temperature = dht.readTemperature();
float temperatureF = dht.readTemperature(true);
 if (isnan(humidity) || isnan(temperature) || isnan(temperatureF)) {
Serial.println(F("Failed to read from DHT sensor!"));
return;
Blynk.virtualWrite(V0,humidity);
Blynk.virtualWrite(V1,temperature);
}
float heatIndexF = dht.computeHeatIndex(temperatureF, humidity);
float heatIndexC = dht.computeHeatIndex(temperature, humidity, false);
Blynk.virtualWrite(V0,humidity);
Blynk.virtualWrite(V1,temperature);
Serial.print(F("Humidity: "));
Serial.print(humidity);
Serial.print(F("% Temperature: "));
Serial.print(temperature);
Serial.print(F("°C "));
Serial.print(F("Heat index: "));
Serial.print(heatIndexC);
Serial.println(F("°C "));
}

