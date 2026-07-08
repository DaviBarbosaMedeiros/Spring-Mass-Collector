# Code Structure

O firmware do **Spring-Mass Collector** foi organizado em múltiplos arquivos para facilitar manutenção, leitura, depuração e expansão futura do sistema.

Em vez de concentrar toda a lógica em um único arquivo `.ino`, o projeto foi dividido em módulos. Cada módulo possui uma responsabilidade específica, como leitura do sensor, controle do LCD, armazenamento dos dados, interpretação dos botões, comunicação Bluetooth e execução das tarefas da ESP32.

---

## Organização geral

A estrutura do firmware pode ser organizada da seguinte forma:

```text
MassaMolaESP32/
├── MassaMolaESP32.ino
├── Globals.h
├── Globals.cpp
├── Sensor.h
├── Sensor.cpp
├── Storage.h
├── Storage.cpp
├── Display.h
├── Display.cpp
├── Buttons.h
├── Buttons.cpp
├── Modes.h
├── Modes.cpp
├── BluetoothComm.h
├── BluetoothComm.cpp
├── Tasks.h
└── Tasks.cpp
```

O arquivo principal `.ino` fica responsável pela inicialização geral do sistema, enquanto os arquivos `.h` e `.cpp` concentram as funcionalidades específicas.

---

## Função de cada módulo

| Módulo               | Função principal                                          |
| -------------------- | --------------------------------------------------------- |
| `MassaMolaESP32.ino` | inicializa o sistema e chama a criação das tarefas        |
| `Globals`            | armazena constantes, variáveis globais, estados e mutexes |
| `Sensor`             | lê o sensor infravermelho e converte tensão em distância  |
| `Storage`            | gerencia o buffer de dados e exportação em CSV            |
| `Display`            | controla as mensagens exibidas no LCD 16x2 I2C            |
| `Buttons`            | realiza a leitura dos botões com debounce                 |
| `Modes`              | implementa a máquina de estados do sistema                |
| `BluetoothComm`      | envia os dados por Bluetooth e Serial                     |
| `Tasks`              | cria e executa as tarefas FreeRTOS                        |

Essa divisão permite que alterações em uma parte do sistema sejam feitas sem modificar diretamente todo o firmware.

---

## Arquivo principal `.ino`

O arquivo principal do projeto é:

```text
MassaMolaESP32.ino
```

Ele deve conter apenas a estrutura geral de inicialização do sistema.

Sua função é:

* inicializar comunicação Serial;
* inicializar Bluetooth;
* configurar sensor;
* configurar LCD;
* configurar botões;
* inicializar armazenamento;
* criar mutexes;
* criar tarefas;
* manter o `loop()` livre ou com atraso mínimo.

Uma estrutura conceitual do arquivo principal é:

```cpp
#include "Globals.h"
#include "Sensor.h"
#include "Storage.h"
#include "Display.h"
#include "Buttons.h"
#include "Modes.h"
#include "BluetoothComm.h"
#include "Tasks.h"

void setup() {
  Serial.begin(115200);

  initGlobals();
  initSensor();
  initStorage();
  initDisplay();
  initButtons();
  initBluetooth();
  createTasks();
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}
```

O `loop()` não concentra a lógica principal do sistema, pois as funções principais são executadas por tarefas independentes.

!!! note "Uso do loop"
No projeto, o `loop()` deve permanecer simples. A aquisição, a interface, os botões e a transferência são controlados por tarefas separadas.

---

## Arquivos `.h` e `.cpp`

Cada módulo é dividido em dois arquivos:

```text
Modulo.h
Modulo.cpp
```

O arquivo `.h` contém declarações, tipos, constantes externas e protótipos de funções.

O arquivo `.cpp` contém a implementação das funções.

Por exemplo:

```text
Sensor.h
Sensor.cpp
```

No `Sensor.h`, são declaradas as funções disponíveis para outros módulos:

```cpp
#ifndef SENSOR_H
#define SENSOR_H

struct SensorData {
  float voltage;
  float distance_cm;
};

void initSensor();
SensorData readSensor();

#endif
```

No `Sensor.cpp`, essas funções são implementadas:

```cpp
#include "Sensor.h"
#include "Globals.h"

void initSensor() {
  analogReadResolution(12);
}

SensorData readSensor() {
  SensorData data;

  // leitura ADC
  // conversão para tensão
  // conversão para distância

  return data;
}
```

Essa separação deixa o código mais organizado e reduz dependências desnecessárias entre módulos.

---

## Módulo `Globals`

O módulo `Globals` concentra variáveis e constantes compartilhadas por diferentes partes do firmware.

Ele pode conter:

* pinos utilizados;
* constantes de configuração;
* modo atual do sistema;
* flags de controle;
* variáveis de calibração;
* variáveis de coleta;
* mutexes;
* parâmetros de armazenamento.

Exemplos de constantes globais:

```cpp
const uint8_t SENSOR_PIN = 39;

const uint8_t BUTTON_QTD = 3;

const uint8_t buttonPins[BUTTON_QTD] = {
  25,
  33,
  32
};
```

Exemplo de enumeração dos modos:

```cpp
enum SystemMode {
  MODE_DEFAULT,
  MODE_CALIBRATION,
  MODE_COLLECTION,
  MODE_TRANSFER
};
```

Exemplos de variáveis de estado:

```cpp
SystemMode currentMode;

bool collectionActive;
bool collectionPaused;
bool calibrated;

float initialPositionCm;
float latestDistanceCm;
float latestRelativePositionCm;
```

O módulo `Globals` deve ser usado com cuidado, pois variáveis globais podem ser acessadas por diferentes tarefas. Por isso, o uso de mutexes é importante.

---

## Módulo `Sensor`

O módulo `Sensor` é responsável pela leitura do sensor infravermelho.

Suas funções principais são:

* configurar a leitura analógica;
* realizar múltiplas leituras ADC;
* calcular uma média representativa;
* converter ADC para tensão;
* converter tensão para distância;
* retornar os dados do sensor.

O sensor fornece uma tensão analógica, que é convertida em distância por:

$$
d = 10.1727 \cdot V^{-0.9965}
$$

Uma função conceitual de leitura pode retornar:

```cpp
struct SensorData {
  float voltage;
  float distance_cm;
};
```

O uso de uma `struct` permite retornar mais de uma informação da mesma leitura, como tensão e distância.

---

## Módulo `Storage`

O módulo `Storage` gerencia o armazenamento dos dados coletados.

Cada ponto experimental pode ser representado por:

```cpp
struct DataPoint {
  uint32_t time_ms;
  float position_cm;
};
```

O buffer principal pode ser definido como:

```cpp
DataPoint dataBuffer[DATA_BUFFER_CAPACITY];
```

As funções do módulo podem incluir:

```cpp
void resetDataBuffer();
bool addDataPoint(uint32_t time_ms, float position_cm);
bool getDataPoint(size_t index, DataPoint &point);
DataPoint getLatestDataPoint();
size_t getDataCount();
bool isDataBufferFull();
void printDataCSV();
```

Esse módulo isola a lógica de armazenamento, evitando que outras partes do firmware manipulem diretamente o vetor de dados.

---

## Módulo `Display`

O módulo `Display` controla o LCD 16x2 I2C.

Ele deve conter funções responsáveis por exibir:

* tela inicial;
* menu principal;
* tela de calibração;
* tela de coleta;
* tela de transferência;
* tela de memória cheia;
* tela de envio dos dados.

Exemplos de funções:

```cpp
void initDisplay();
void showDefaultScreen();
void showCalibrationScreen(float initialPositionCm);
void showCollectionScreen(float positionCm, size_t dataCount, bool paused);
void showTransferScreen(size_t dataCount, size_t maxDataPoints);
void showMemoryFullScreen();
void showTransferInProgressScreen();
```

O LCD deve ser atualizado com frequência menor do que a coleta dos dados, pois sua escrita é relativamente lenta.

---

## Módulo `Buttons`

O módulo `Buttons` é responsável pela leitura dos três botões físicos.

Ele deve:

* configurar os pinos como `INPUT_PULLUP`;
* ler o estado físico dos botões;
* aplicar debounce;
* detectar cliques válidos;
* fornecer eventos para a máquina de estados.

A lógica elétrica adotada é:

| Estado físico     | Leitura lógica |
| ----------------- | -------------- |
| botão solto       | `HIGH`         |
| botão pressionado | `LOW`          |

O debounce evita que um único clique seja interpretado como vários comandos.

Uma estrutura conceitual de eventos pode ser:

```cpp
enum ButtonEvent {
  BUTTON_NONE,
  BUTTON_1_PRESSED,
  BUTTON_2_PRESSED,
  BUTTON_3_PRESSED
};
```

O botão apenas gera o evento. A função do botão depende do modo atual e é interpretada pelo módulo `Modes`.

---

## Módulo `Modes`

O módulo `Modes` implementa a máquina de estados do sistema.

Ele interpreta os eventos dos botões de acordo com o modo atual.

As funções principais podem ser:

```cpp
void handleDefaultMode();
void handleCalibrationMode();
void handleCollectionMode();
void handleTransferMode();
void updateMode();
```

A lógica geral é:

```text
Ler evento de botão
        ↓
Verificar modo atual
        ↓
Executar ação correspondente
        ↓
Atualizar estado do sistema
        ↓
Atualizar tela, se necessário
```

Exemplo de interpretação:

| Modo          | B1             | B2                | B3                    |
| ------------- | -------------- | ----------------- | --------------------- |
| Default       | Calibração     | Coleta            | Transferência         |
| Calibração    | Recalibrar     | Confirmar         | Zerar posição inicial |
| Coleta        | Pausar/retomar | Resetar coleta    | Voltar ao Default     |
| Transferência | Enviar dados   | Voltar ao Default | Alterar limite        |

Essa estrutura evita que a lógica dos botões fique espalhada por todo o firmware.

---

## Módulo `BluetoothComm`

O módulo `BluetoothComm` controla a comunicação Bluetooth e o envio dos dados.

Ele pode conter:

```cpp
void initBluetooth();
void sendDataBluetooth();
void sendDataSerial();
void sendDataAll();
```

A transferência envia os dados no formato CSV:

```text
t_ms,pos_cm
25,0.0123
50,0.0181
75,0.0204
END
```

O cabeçalho identifica as colunas, enquanto `END` indica o final da transmissão.

Esse módulo pode enviar os dados tanto por Bluetooth quanto pela Serial USB, o que facilita testes durante o desenvolvimento.

---

## Módulo `Tasks`

O módulo `Tasks` cria e organiza as tarefas executadas pela ESP32.

As principais tarefas são:

| Tarefa          | Função                                      |
| --------------- | ------------------------------------------- |
| `TaskSensor`    | leitura do sensor e armazenamento dos dados |
| `TaskButtons`   | leitura dos botões e geração de eventos     |
| `TaskModes`     | execução da máquina de estados              |
| `TaskDisplay`   | atualização do LCD                          |
| `TaskBluetooth` | envio dos dados por Bluetooth               |

A criação das tarefas pode ser feita usando funções do FreeRTOS, como:

```cpp
xTaskCreatePinnedToCore();
```

Essa função permite escolher em qual núcleo da ESP32 cada tarefa será executada.

---

## Organização entre os núcleos

Uma organização possível é:

```text
Core 1
└── TaskSensor
    ├── lê sensor
    ├── calcula posição relativa
    └── armazena dados

Core 0
├── TaskButtons
├── TaskModes
├── TaskDisplay
└── TaskBluetooth
```

Essa divisão separa a aquisição do sensor das tarefas de interface e comunicação.

A coleta precisa ser regular. O LCD e o Bluetooth podem ser mais lentos. Por isso, manter a aquisição em uma tarefa própria ajuda a preservar a qualidade temporal dos dados.

---

## Fluxo de dependências

Os módulos possuem dependências entre si. De forma simplificada:

```text
MassaMolaESP32.ino
        ↓
Globals
        ↓
Tasks
 ├── Sensor
 ├── Buttons
 ├── Modes
 ├── Display
 ├── Storage
 └── BluetoothComm
```

O módulo `Globals` é compartilhado por vários outros módulos, pois contém variáveis de estado, constantes e mutexes.

O módulo `Storage` é usado tanto pela tarefa de aquisição quanto pela tarefa de transferência.

O módulo `Display` é usado para apresentar estados definidos pelo módulo `Modes`.

---

## Inclusão dos arquivos

No Arduino IDE, os arquivos `.h` e `.cpp` devem estar na mesma pasta do arquivo principal `.ino`.

O nome da pasta deve ser igual ao nome do arquivo principal.

Exemplo:

```text
MassaMolaESP32/
└── MassaMolaESP32.ino
```

Dentro da mesma pasta, ficam os demais arquivos:

```text
MassaMolaESP32/
├── MassaMolaESP32.ino
├── Globals.h
├── Globals.cpp
├── Sensor.h
├── Sensor.cpp
└── ...
```

No arquivo `.ino`, os módulos são incluídos com:

```cpp
#include "Globals.h"
#include "Sensor.h"
#include "Storage.h"
#include "Display.h"
#include "Buttons.h"
#include "Modes.h"
#include "BluetoothComm.h"
#include "Tasks.h"
```

O Arduino IDE compila automaticamente os arquivos `.cpp` que estão na mesma pasta do sketch.

---

## Vantagens da estrutura modular

A estrutura modular traz várias vantagens:

| Vantagem     | Descrição                                               |
| ------------ | ------------------------------------------------------- |
| Organização  | cada arquivo possui uma responsabilidade clara          |
| Manutenção   | erros são mais fáceis de localizar                      |
| Expansão     | novos recursos podem ser adicionados com menor impacto  |
| Reutilização | módulos podem ser reaproveitados em outros projetos     |
| Documentação | cada parte do firmware pode ser explicada separadamente |
| Testes       | módulos podem ser avaliados de forma mais isolada       |

Essa organização é especialmente importante em um projeto com sensor, LCD, botões, Bluetooth, armazenamento e múltiplas tarefas.

---

## Resumo

A estrutura do código do Spring-Mass Collector segue uma organização modular:

```text
Firmware
├── .ino principal
├── Globals
├── Sensor
├── Storage
├── Display
├── Buttons
├── Modes
├── BluetoothComm
└── Tasks
```

Essa separação permite que o firmware seja mais legível, mais fácil de modificar e mais adequado para documentação técnica.

Com essa estrutura, o projeto deixa de ser apenas um sketch simples de Arduino e passa a ter uma organização mais próxima de um sistema embarcado completo.
