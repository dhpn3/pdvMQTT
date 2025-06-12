#include <Arduino.h>
#include "network.h"

void setup() {
  Serial.begin(115200);

  // Inicializa Wi-Fi e configura cliente MQTT
  initNetwork();

  // Pode adicionar inicializações futuras aqui (ex: API de pedidos)
}

void loop() {
  // Garante reconexão MQTT, caso perca
  ensureMqttConnection();

  // Mantém comunicação MQTT funcionando
  mqttClient.loop();

  // Pode adicionar chamadas de tarefas (ex: verificar botões ou mensagens recebidas)
}


