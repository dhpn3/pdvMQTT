#include "network.h"

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void connectWiFi() {
  Serial.print("[WiFi] Conectando a ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n[WiFi] Conectado com sucesso!");
  Serial.print("[WiFi] IP: ");
  Serial.println(WiFi.localIP());
}

void initNetwork() {
  connectWiFi();
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
}

void ensureMqttConnection() {
  while (!mqttClient.connected()) {
    Serial.print("[MQTT] Conectando ao broker... ");
    String clientId = "ESP32Cliente-";
    clientId += String(random(0xffff), HEX);

    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("conectado!");
      // Aqui você pode adicionar subscrições se precisar
    } else {
      Serial.print("falhou (rc=");
      Serial.print(mqttClient.state());
      Serial.println("). Tentando novamente em 2 segundos...");
      delay(2000);
    }
  }
}
