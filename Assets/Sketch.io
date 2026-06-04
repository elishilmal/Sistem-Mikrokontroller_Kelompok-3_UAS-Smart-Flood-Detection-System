#include <WiFi.h>
#include <PubSubClient.h>
#include <NewPing.h>

// ======================
// PIN CONFIG
// ======================
#define TRIGGER_PIN 15
#define ECHO_PIN 4

#define LED_MERAH 26
#define LED_HIJAU 27
#define LED_KUNING 14
#define LED_ORANYE 12

#define BUZZER_PIN 25

// ======================
// ULTRASONIC
// ======================
NewPing ultrasonic(TRIGGER_PIN, ECHO_PIN);

// ======================
// WIFI & MQTT
// ======================
const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "broker.emqx.io";
const char* mqtt_user = "mattx_b002245";
const char* mqtt_password = "12345";

const char* mqtt_topic_status = "pertandabanjir/status";
const char* mqtt_topic_jarak  = "pertandabanjir/jarak";

WiFiClient espClient;
PubSubClient client(espClient);

// ======================
// WIFI
// ======================
void setup_wifi() {

  Serial.println();
  Serial.print("Connecting WiFi ");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  unsigned long startAttempt = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - startAttempt < 10000) {

    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println();
    Serial.println("WiFi Connected");
    Serial.print("IP : ");
    Serial.println(WiFi.localIP());

  } else {

    Serial.println();
    Serial.println("WiFi Failed");
  }
}

// ======================
// MQTT CALLBACK
// ======================
void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message : ");

  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();
}

// ======================
// MQTT RECONNECT
// NON BLOCKING
// ======================
void reconnect() {

  if (!client.connected()) {

    Serial.println("Trying MQTT...");

    client.connect(
      "ESP32_BANJIR",
      mqtt_user,
      mqtt_password
    );

    if (client.connected()) {
      Serial.println("MQTT Connected");
    }
  }
}

// ======================
// SETUP
// ======================
void setup() {

  Serial.begin(115200);

  pinMode(LED_HIJAU, OUTPUT);
  pinMode(LED_KUNING, OUTPUT);
  pinMode(LED_ORANYE, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  digitalWrite(LED_HIJAU, LOW);
  digitalWrite(LED_KUNING, LOW);
  digitalWrite(LED_ORANYE, LOW);
  digitalWrite(LED_MERAH, LOW);

  digitalWrite(BUZZER_PIN, LOW);
}

// ======================
// LOOP
// ======================
void loop() {

  reconnect();

  if (client.connected()) {
    client.loop();
  }

  int jarak = ultrasonic.ping_cm();

  Serial.print("Jarak Air : ");
  Serial.print(jarak);
  Serial.println(" cm");

  // reset indikator
  digitalWrite(LED_HIJAU, LOW);
  digitalWrite(LED_KUNING, LOW);
  digitalWrite(LED_ORANYE, LOW);
  digitalWrite(LED_MERAH, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  String statusBanjir = "";

  // ======================
  // DARURAT
  // <= 10 cm
  // ======================
  if (jarak > 0 && jarak <= 10) {

    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    statusBanjir = "DARURAT";

    Serial.println("STATUS : DARURAT");
  }

  // ======================
  // SIAGA
  // 11 - 50 cm
  // ======================
  else if (jarak <= 50) {

    digitalWrite(LED_ORANYE, HIGH);

    digitalWrite(BUZZER_PIN, HIGH);
    delay(300);
    digitalWrite(BUZZER_PIN, LOW);

    statusBanjir = "SIAGA";

    Serial.println("STATUS : SIAGA");
  }

  // ======================
  // WASPADA
  // 51 - 100 cm
  // ======================
  else if (jarak <= 100) {

    digitalWrite(LED_KUNING, HIGH);

    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);

    statusBanjir = "WASPADA";

    Serial.println("STATUS : WASPADA");
  }

  // ======================
  // AMAN
  // >100 cm
  // ======================
  else {

    digitalWrite(LED_HIJAU, HIGH);

    statusBanjir = "AMAN";

    Serial.println("STATUS : AMAN");
  }

  // ======================
  // MQTT PUBLISH
  // ======================
  if (client.connected()) {

    client.publish(
      mqtt_topic_status,
      statusBanjir.c_str()
    );

    client.publish(
      mqtt_topic_jarak,
      String(jarak).c_str()
    );
  }

  Serial.println("-------------------");

  delay(1000);
}
