# Microcontroller

O Spring-Mass Collector utiliza uma placa **ESP32 DevKit de 30 pinos**, baseada no módulo ESP-WROOM-32.

A ESP32 concentra o processamento do sistema e é responsável por:

* ler o sensor de distância;
* interpretar os botões;
* atualizar o display;
* armazenar as amostras;
* executar os modos de operação;
* transmitir os dados por Bluetooth.

## Pinos utilizados

| Função              | Pino     |
| ------------------- | -------- |
| Sensor de distância | `GPIO39` |
| Botão B1            | `GPIO25` |
| Botão B2            | `GPIO33` |
| Botão B3            | `GPIO32` |
| Display SDA         | `GPIO21` |
| Display SCL         | `GPIO22` |
| Referência elétrica | `GND`    |

O `GPIO39` é utilizado como entrada analógica. Os botões utilizam entradas digitais com resistores internos de pull-up, enquanto o display se comunica pelo barramento I²C.

## Conversor analógico-digital

A leitura do sensor utiliza o conversor analógico-digital da ESP32 com resolução de 12 bits:

```cpp
analogReadResolution(12);
```

Assim, a leitura pode variar entre:

```text
0 e 4095
```

A tensão correspondente é calculada por:

$$
V=
\frac{
\mathrm{ADC}\cdot 3.3
}{
4095
}
$$

## Alimentação e programação

A placa pode ser alimentada e programada pela conexão USB acessível pela abertura lateral da caixa.

Essa conexão permite:

* carregar o firmware;
* alimentar o equipamento;
* acompanhar mensagens pela comunicação serial;
* realizar testes antes do fechamento da caixa.

!!! warning "Níveis de tensão"
Os GPIOs da ESP32 operam com níveis lógicos de 3,3 V e não devem receber diretamente sinais digitais de 5 V.