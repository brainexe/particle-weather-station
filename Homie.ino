
#include "DHT.h"

#define LED_PIN 1
#define DHT_PIN 3
#define DHT_TYPE DHT22

const int LOOP = 20 * 1000;

double temperature;
double humidity;
int i = 0;

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  dht.begin();

  pinMode(LED_PIN, OUTPUT);

  Particle.variable("humidity", humidity);
  Particle.variable("temperature", temperature);
  Particle.variable("loop", i);

  Particle.function("ledOn", ledOn);
  Particle.function("ledOff", ledOff);

  Particle.function("pinOn", pinOn);
  Particle.function("pinOff", pinOff);

  Particle.publish("booted");
}

void loop() {
  dht.read();

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  ledOn("");
  delay(1000);
  ledOff("");
  delay(LOOP - 1000);
}

int ledOff(String command) {
  digitalWrite(LED_PIN, LOW);

  return 1;
}

int ledOn(String command) {
  digitalWrite(LED_PIN, HIGH);

  return 1;
}

int pinOff(String command) {
  digitalWrite(4, LOW);

  return 1;
}

int pinOn(String command) {
  digitalWrite(4, HIGH);

  return 1;
}
