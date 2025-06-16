#include "pedido_api.h"
#include "network.h"
#include <ArduinoJson.h>

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("[API Cliente] Mensagem recebida da máquina:");

  char mensagem[200];
  memcpy(mensagem, payload, length);
  mensagem[length] = '\0'; // Finaliza string corretamente

  Serial.println(mensagem);
}

void setupPedidoAPI() {
  mqttClient.setCallback(callback);

  mqttClient.subscribe("maquina_8_3/compra/status_pedido");
  Serial.println("[API Cliente] Subscreveu ao tópico maquina_8_3/compra/status_pedido");
}

// Envia solicitação do pedido do cliente para máquina

void enviarPedido(int produto_id, int quantidade) {
  StaticJsonDocument<200> pedido;
  pedido["produto_id"] = produto_id;
  pedido["quantidade"] = quantidade;

  char jsonStr[128];
  serializeJson(pedido, jsonStr);

  mqttClient.publish("maquina_8_3/compra/pedido", jsonStr);
  Serial.print("[API Cliente] Pedido enviado: ");
  Serial.println(jsonStr);
}
