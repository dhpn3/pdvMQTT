#include <WiFi.h>
#include <PubSubClient.h>

// Dados da rede Wi-Fi
const char* ssid = "SUA_REDE_WIFI";
const char* password = "SUA_SENHA_WIFI";

// Endereço do broker MQTT (test.mosquitto.org é um público)
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando-se a: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // Aguarda conexão
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado com sucesso!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect_mqtt() {
  // Tenta conectar até conseguir
  while (!client.connected()) {
    Serial.print("Conectando ao broker MQTT...");
    String clientId = "ESP32Cliente-";
    clientId += String(random(0xffff), HEX); // ID único

    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado ao MQTT!");
      // Aqui você pode subscrever a tópicos, se quiser
    } else {
      Serial.print("Falha. Código: ");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 2 segundos...");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883); // Porta padrão do MQTT
}

void loop() {
  if (!client.connected()) {
    reconnect_mqtt();
  }
  client.loop(); // Mantém a conexão ativa
}

