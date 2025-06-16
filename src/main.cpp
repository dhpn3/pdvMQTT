#include <Arduino.h>
#include "network.h"
#include "pedido_api.h"

void setup() {
  Serial.begin(115200);
  initNetwork();
  setupPedidoAPI();
}

void loop() {
  ensureMqttConnection();
  mqttClient.loop();

  // Exemplo: envia um pedido a cada 15 segundos
  static unsigned long lastTime = 0;
  if (millis() - lastTime > 15000) {
    enviarPedido(3, 1); // Produto 3, quantidade 1
    lastTime = millis();
  }
}


