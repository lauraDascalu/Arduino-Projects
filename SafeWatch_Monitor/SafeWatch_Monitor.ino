#include <WiFiNINA.h>
#include <PDM.h>
#include <Arduino_LSM6DSOX.h>
#include <ArduinoMqttClient.h>
#include <mbed.h>

using namespace mbed;
using namespace rtos;
using namespace std::chrono_literals;

// Threads
Thread temp_thread;
Thread sound_thread;
Thread mqtt_thread;

// WiFi credentials
char ssid[] = "My hotspot";
char pass[] = "Parola123";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "broker.hivemq.com";
int port = 1883;

const char* temp_topic = "temperature";
const char* bool_topic = "bool_status";
const char* led_topic = "led_status";

// Mutex for shared resources
Mutex mqttMutex;

static const char channels = 1;
static const int frequency = 16000;
short sampleBuffer[512];
volatile int samplesRead;

void changeLEDColor(String color);
void onPDMdata();
void check_sound();
void check_temperature();
void mqtt_polling();

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  if (!IMU.accelerationAvailable() || !IMU.gyroscopeAvailable()) {
    Serial.println("Failed to detect sensors!");
    while (1);
  }

  PDM.onReceive(onPDMdata);
  PDM.setGain(30);
  if (!PDM.begin(channels, frequency)) {
    Serial.println("Failed to start PDM!");
    while (1);
  }

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);

  // Start threads
  temp_thread.start(callback(check_temperature));
  sound_thread.start(callback(check_sound));
  mqtt_thread.start(callback(mqtt_polling));
}

void loop() {
  // The loop function is not used when using threads
}

void check_temperature() {
  const unsigned long tempDetectionInterval = 1000;
  unsigned long lastTempCheck = 0;

  while (true) {
    if (millis() - lastTempCheck >= tempDetectionInterval) {
      int temperature_deg = 0;
      IMU.readTemperature(temperature_deg);

      mqttMutex.lock();
      mqttClient.beginMessage(temp_topic);
      mqttClient.print(temperature_deg);
      mqttClient.endMessage();
      mqttMutex.unlock();

      lastTempCheck = millis(); 
    }

    ThisThread::sleep_for(100ms); 
  }
}

void check_sound() {
  const unsigned long soundDetectionInterval = 1000; 
  unsigned long lastSoundCheck = 0;

  while (true) {
    if (millis() - lastSoundCheck >= soundDetectionInterval) {
      if (samplesRead) {
        bool loudSoundDetected = false;

        for (int i = 0; i < samplesRead; i++) {
          if (sampleBuffer[i] > 10000 || sampleBuffer[i] <= -10000) 
          {
            loudSoundDetected = true;  
          }
        }

        mqttMutex.lock();
        if (loudSoundDetected) {
          changeLEDColor("red");
          mqttClient.beginMessage(led_topic);
          mqttClient.print("Loud Sound!");
          mqttClient.endMessage();
          mqttClient.beginMessage(bool_topic);
          mqttClient.print(1);
          mqttClient.endMessage();
        } else {
          changeLEDColor("blue");
          mqttClient.beginMessage(led_topic);
          mqttClient.print("Quiet");
          mqttClient.endMessage();
          mqttClient.beginMessage(bool_topic);
          mqttClient.print(0);
          mqttClient.endMessage();
        }
        mqttMutex.unlock();

        samplesRead = 0;
      }
      lastSoundCheck = millis();
    }
    ThisThread::sleep_for(100ms);
  }
}

void mqtt_polling() {
  while (true) {
    mqttMutex.lock();
    mqttClient.poll();
    mqttMutex.unlock();
    ThisThread::sleep_for(100ms); 
  }
}

void changeLEDColor(String color) {
  if (color == "red") {
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, LOW);
  } else if (color == "blue") {
    digitalWrite(LEDB, HIGH);
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, LOW);
  }
}

void onPDMdata() {
  // Query the number of available bytes
  int bytesAvailable = PDM.available();

  // Read into the sample buffer
  PDM.read(sampleBuffer, bytesAvailable);

  // 16-bit, 2 bytes per sample
  samplesRead = bytesAvailable / 2;
}
