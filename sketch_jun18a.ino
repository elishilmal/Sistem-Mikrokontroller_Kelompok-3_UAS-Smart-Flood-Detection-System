#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define WATER_SENSOR 34

#define TRIG_PIN 5
#define ECHO_PIN 18

#define BUZZER_PIN 26

#define LED_HIJAU 15
#define LED_KUNING 2
#define LED_MERAH 4

LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "ahmad";
const char* password = "12345671";

const char* mqtt_server = "floodflood.cloud.shiftr.io";
const int mqtt_port = 1883;

const char* mqtt_user = "floodflood";
const char* mqtt_pass = "banjirr";

WiFiClient espClient;
PubSubClient client(espClient);
void connectWiFi() {

  WiFi.begin(ssid, password);

  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
}

void reconnectMQTT() {

  while (!client.connected()) {

    Serial.print("Connecting MQTT...");

    String clientId = "flood1_flood";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {

      Serial.println("Connected");

    } else {

      Serial.print("Failed : ");
      Serial.println(client.state());

      delay(3000);

    }
  }
}

void sirineDarurat() {

  for (int i = 2500; i <= 5000; i += 250) {
    tone(BUZZER_PIN, i);
    delay(20);
  }

  for (int i = 5000; i >= 2500; i -= 250) {
    tone(BUZZER_PIN, i);
    delay(20);
  }

  noTone(BUZZER_PIN);
}

// =================================
// Baca Ultrasonic
// =================================
float bacaJarak() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return 999; // jika tidak ada pantulan
  }

  return duration * 0.0343 / 2;
}

void setup() {

  Serial.begin(115200);
  connectWiFi();

client.setServer(mqtt_server, mqtt_port);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(LED_HIJAU, OUTPUT);
  pinMode(LED_KUNING, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Flood Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {

if (WiFi.status() != WL_CONNECTED) {

  connectWiFi();

}

if (!client.connected()) {
    reconnectMQTT();
}

client.loop();

  int waterValue = analogRead(WATER_SENSOR);
  float distance = bacaJarak();

  String statusLCD = "";
  String statusMQTT = "";

  // ==============================
  // Level dari Ultrasonic
  // ==============================

  int levelUltrasonic = 0;

  if (distance <= 10)
    levelUltrasonic = 3;
  else if (distance <= 50)
    levelUltrasonic = 2;
  else if (distance <= 100)
    levelUltrasonic = 1;
  else
    levelUltrasonic = 0;

  // ==============================
  // Level dari Water Sensor
  // ==============================

  int levelWater = 0;

  if (waterValue > 2500)
    levelWater = 3;
  else if (waterValue > 1500)
    levelWater = 2;
  else if (waterValue > 500)
    levelWater = 1;
  else
    levelWater = 0;

  // Ambil level tertinggi
  int level = max(levelUltrasonic, levelWater);

  // Reset output
  digitalWrite(LED_HIJAU, LOW);
  digitalWrite(LED_KUNING, LOW);
  digitalWrite(LED_MERAH, LOW);

  noTone(BUZZER_PIN);

  // ==============================
  // DARURAT
  // ==============================

  if (level == 3) {

    statusLCD = "DARURAT";
    statusMQTT = "critical";

    for (int i = 0; i < 3; i++) {

      digitalWrite(LED_HIJAU, HIGH);
      digitalWrite(LED_KUNING, HIGH);
      digitalWrite(LED_MERAH, HIGH);

      tone(BUZZER_PIN, 4000);
      delay(100);

      digitalWrite(LED_HIJAU, LOW);
      digitalWrite(LED_KUNING, LOW);
      digitalWrite(LED_MERAH, LOW);

      noTone(BUZZER_PIN);
      delay(100);
    }

    sirineDarurat();
  }

  // ==============================
  // SIAGA
  // ==============================

  else if (level == 2) {

    statusLCD = "SIAGA";
    statusMQTT = "danger";

    digitalWrite(LED_MERAH, HIGH);

    tone(BUZZER_PIN, 3500);
    delay(250);

    digitalWrite(LED_MERAH, LOW);

    noTone(BUZZER_PIN);
    delay(250);
  }

  // ==============================
  // WASPADA
  // ==============================

  else if (level == 1) {

    statusLCD = "WASPADA";
    statusMQTT = "warning";

    digitalWrite(LED_KUNING, HIGH);

    tone(BUZZER_PIN, 2200);
    delay(400);

    digitalWrite(LED_KUNING, LOW);

    noTone(BUZZER_PIN);
    delay(400);
  }

  // ==============================
  // AMAN
  // ==============================

  else {

    statusLCD = "AMAN";
    statusMQTT = "safe";

    digitalWrite(LED_HIJAU, HIGH);
  }

  // ==============================
  // Serial Monitor
  // ==============================

  Serial.print("Water : ");
  Serial.print(waterValue);

  Serial.print(" | Distance : ");
  Serial.print(distance);

  Serial.print(" cm | Status : ");
  Serial.println(statusLCD);


String payload = "{";

payload += "\"status\":\"" + statusMQTT + "\",";
payload += "\"distance\":" + String(distance,1) + ",";
payload += "\"water\":" + String(waterValue) + ",";
payload += "\"device_id\":\"ESP32-01\",";
payload += "\"uptime\":" + String(millis()/1000) + ",";
payload += "\"wifi_rssi\":" + String(WiFi.RSSI());

payload += "}";

client.publish("floodmonitor/sensor", payload.c_str());

Serial.println(payload);
  // ==============================
  // LCD
  // ==============================

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(statusLCD);

  lcd.setCursor(0, 1);
  lcd.print("D:");
  lcd.print(distance, 1);

  lcd.print(" W:");
  lcd.print(waterValue);

unsigned long lastHeartbeat = 0;

if (millis() - lastHeartbeat > 10000) {

  lastHeartbeat = millis();

  String hb = "{";

  hb += "\"device_id\":\"ESP32-01\",";
  hb += "\"uptime\":" + String(millis()/1000);

  hb += "}";

  client.publish("floodmonitor/heartbeat", hb.c_str());
}

  delay(100);
}