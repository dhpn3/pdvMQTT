#ifndef PEDIDO_API_H
#define PEDIDO_API_H

#include <Arduino.h>

// Inicializa a API de pedidos (subscreve para receber status)
void setupPedidoAPI();

// Envia um pedido de compra (produto_id, quantidade)
void enviarPedido(int produto_id, int quantidade);

#endif
