# Circuit

Esta página descreve a organização elétrica do **Spring-Mass Collector**, incluindo a conexão entre ESP32, sensor infravermelho, display LCD 16x2 I2C, botões físicos e alimentação.

O circuito foi pensado para manter a montagem simples, de baixo custo e adequada ao uso em laboratório didático.

---

## Visão geral do circuito

O circuito do Spring-Mass Collector pode ser dividido em quatro blocos principais:

```text
Alimentação
     ↓
ESP32
 ├── Sensor infravermelho de distância
 ├── Display LCD 16x2 I2C
 ├── Três botões físicos
 └── Comunicação Bluetooth integrada
```

A ESP32 atua como unidade central. Ela recebe a leitura analógica do sensor, interpreta os botões, atualiza o LCD e transfere os dados por Bluetooth.

---

## Componentes conectados à ESP32

| Componente           | Tipo de conexão   | Função                            |
| -------------------- | ----------------- | --------------------------------- |
| Sensor infravermelho | entrada analógica | medir a distância até a massa     |
| LCD 16x2 I2C         | barramento I2C    | exibir menus e estados do sistema |
| Botão B1             | entrada digital   | comando dependente do modo atual  |
| Botão B2             | entrada digital   | comando dependente do modo atual  |
| Botão B3             | entrada digital   | comando dependente do modo atual  |
| Bluetooth            | interno da ESP32  | transferir os dados coletados     |

---

## Pinagem atual

A tabela abaixo resume os pinos utilizados no firmware atual.

| Elemento             | Pino na ESP32 | Observação                         |
| -------------------- | ------------: | ---------------------------------- |
| Sensor infravermelho |       GPIO 39 | entrada analógica                  |
| Botão B1             |       GPIO 25 | entrada digital com `INPUT_PULLUP` |
| Botão B2             |       GPIO 33 | entrada digital com `INPUT_PULLUP` |
| Botão B3             |       GPIO 32 | entrada digital com `INPUT_PULLUP` |
| LCD SDA              |       GPIO 21 | linha de dados I2C                 |
| LCD SCL              |       GPIO 22 | linha de clock I2C                 |
| Bluetooth            |       interno | comunicação Bluetooth Serial       |

!!! note "Pinos I2C"
Os pinos GPIO 21 e GPIO 22 são os pinos I2C frequentemente utilizados na ESP32 com a Arduino IDE. Caso a montagem utilize outros pinos, a configuração do barramento I2C deve ser ajustada no firmware.

---

## Alimentação do sistema

A alimentação deve fornecer energia para:

* ESP32;
* sensor infravermelho;
* display LCD 16x2 I2C;
* circuito dos botões.

A ESP32 pode ser alimentada pela porta USB durante testes e desenvolvimento. Para uso embarcado, pode ser utilizada uma fonte externa adequada, desde que respeite os limites elétricos da placa utilizada.

O sensor infravermelho e o LCD devem ser alimentados de acordo com suas especificações. A referência elétrica comum deve ser compartilhada entre todos os módulos.

```text
Fonte / USB
    ↓
ESP32
 ├── GND comum
 ├── Sensor infravermelho
 ├── LCD 16x2 I2C
 └── Botões
```

!!! warning "GND comum"
Todos os componentes devem compartilhar o mesmo GND. Sem uma referência comum, a leitura analógica do sensor e os sinais digitais dos botões podem ficar incorretos ou instáveis.

---

## Conexão do sensor infravermelho

O sensor infravermelho possui uma saída analógica proporcional à distância medida.

A conexão básica é:

| Sensor | ESP32                 |
| ------ | --------------------- |
| VCC    | alimentação do sensor |
| GND    | GND comum             |
| OUT    | GPIO 39               |

O pino de saída do sensor é lido pela entrada analógica da ESP32:

```cpp
const uint8_t SENSOR_PIN = 39;
```

A leitura bruta do ADC é posteriormente convertida em tensão e distância no firmware.

```text
Sensor OUT
    ↓
GPIO 39
    ↓
ADC da ESP32
    ↓
Conversão tensão-distância
```

!!! warning "Tensão no ADC"
A entrada analógica da ESP32 não deve receber tensão acima do limite permitido pela placa. Antes de conectar o sensor, verifique a tensão máxima de saída do modelo utilizado.

---

## Conexão do LCD 16x2 I2C

O LCD 16x2 utiliza um módulo adaptador I2C, reduzindo a quantidade de fios necessários.

A conexão típica é:

| LCD I2C | ESP32              |
| ------- | ------------------ |
| VCC     | alimentação do LCD |
| GND     | GND comum          |
| SDA     | GPIO 21            |
| SCL     | GPIO 22            |

O barramento I2C permite que a ESP32 envie informações ao display usando apenas duas linhas de comunicação:

```text
ESP32 GPIO 21  → SDA
ESP32 GPIO 22  → SCL
```

O LCD é usado apenas como interface local. Ele mostra menus, estados e informações resumidas, mas não interfere diretamente no armazenamento completo dos dados.

---

## Conexão dos botões

Os três botões são conectados entre o pino digital da ESP32 e o GND.

A ligação considerada é:

```text
GPIO ---- botão ---- GND
```

No firmware, os pinos são configurados como entradas com resistor interno de pull-up:

```cpp
pinMode(buttonPins[i], INPUT_PULLUP);
```

Assim, o comportamento elétrico é:

| Estado do botão | Leitura lógica |
| --------------- | -------------- |
| solto           | HIGH           |
| pressionado     | LOW            |

Essa configuração simplifica o circuito, pois evita a necessidade de resistores externos de pull-up.

---

## Pinos dos botões

No firmware atual, os botões são definidos por:

```cpp
const uint8_t buttonPins[BUTTON_QTD] = {
  25,
  33,
  32
};
```

A associação funcional é:

| Botão |    Pino | Função geral                 |
| ----- | ------: | ---------------------------- |
| B1    | GPIO 25 | primeira opção do modo atual |
| B2    | GPIO 33 | segunda opção do modo atual  |
| B3    | GPIO 32 | terceira opção do modo atual |

A função exata de cada botão depende do modo de operação ativo.

---

## Representação simplificada do circuito

A estrutura elétrica pode ser representada de forma simplificada como:

```text
                         ┌─────────────────────┐
                         │        ESP32        │
                         │                     │
Sensor OUT ─────────────▶│ GPIO 39 / ADC       │
                         │                     │
Botão B1 ───────────────▶│ GPIO 25             │
Botão B2 ───────────────▶│ GPIO 33             │
Botão B3 ───────────────▶│ GPIO 32             │
                         │                     │
LCD SDA ◀───────────────▶│ GPIO 21 / SDA       │
LCD SCL ◀───────────────▶│ GPIO 22 / SCL       │
                         │                     │
Bluetooth Serial         │ Interno             │
                         └─────────────────────┘
```

Todos os módulos devem compartilhar o mesmo GND.

---

## Organização dos sinais

| Tipo de sinal | Elemento             | Direção                     |
| ------------- | -------------------- | --------------------------- |
| Analógico     | sensor infravermelho | sensor → ESP32              |
| Digital       | botões               | usuário → ESP32             |
| I2C           | LCD 16x2             | ESP32 → LCD                 |
| Bluetooth     | comunicação sem fio  | ESP32 → dispositivo externo |

A separação entre esses sinais facilita a organização do circuito e a identificação de possíveis problemas durante testes.

---

## Cuidados com ruído

A leitura do sensor infravermelho pode ser afetada por ruídos elétricos e instabilidade na alimentação.

Para melhorar a estabilidade do circuito, recomenda-se:

* manter conexões curtas sempre que possível;
* evitar fios soltos na entrada analógica;
* garantir alimentação estável;
* manter GND comum entre todos os módulos;
* evitar mau contato nos conectores;
* fixar bem o sensor na estrutura 3D;
* organizar os fios dentro da caixa para reduzir interferências mecânicas.

---

## Relação entre circuito e firmware

O firmware depende diretamente da pinagem definida no circuito. Se algum pino for alterado fisicamente, a constante correspondente no código também deve ser atualizada.

Exemplo para o sensor:

```cpp
const uint8_t SENSOR_PIN = 39;
```

Exemplo para os botões:

```cpp
const uint8_t buttonPins[BUTTON_QTD] = {
  25,
  33,
  32
};
```

Se o LCD for conectado a pinos I2C diferentes dos padrões, a inicialização do barramento também deve ser ajustada.

---

## Testes recomendados

Antes de usar o circuito no experimento completo, recomenda-se testar cada módulo separadamente.

| Teste            | Objetivo                                        |
| ---------------- | ----------------------------------------------- |
| ESP32 ligada     | verificar alimentação e inicialização           |
| LCD              | verificar endereço I2C e exibição das mensagens |
| Botões           | verificar leitura `HIGH` e `LOW`                |
| Sensor           | verificar variação da leitura com a distância   |
| Bluetooth        | verificar pareamento e envio de texto           |
| Sistema completo | verificar integração entre modos                |

Esse processo facilita a identificação de erros de montagem antes da realização da coleta experimental.

---

## Possíveis problemas

| Problema                   | Possível causa                                   | Ação recomendada                                 |
| -------------------------- | ------------------------------------------------ | ------------------------------------------------ |
| LCD não acende             | alimentação incorreta ou mau contato             | verificar VCC, GND e conexão I2C                 |
| LCD acende sem texto       | endereço I2C incorreto ou falha de inicialização | verificar endereço do módulo e código            |
| botão não responde         | ligação incorreta ou pino errado                 | verificar GPIO, GND e `INPUT_PULLUP`             |
| botão aciona sozinho       | mau contato ou ruído                             | verificar conexão e debounce                     |
| leitura do sensor instável | ruído, desalinhamento ou alimentação instável    | revisar alimentação, fixação e posição do sensor |
| Bluetooth não aparece      | ESP32 não inicializou Bluetooth                  | reiniciar o sistema e verificar firmware         |

---

## Resumo

O circuito do Spring-Mass Collector conecta a ESP32 aos módulos necessários para aquisição, controle local e transferência de dados.

```text
ESP32
├── GPIO 39 → sensor infravermelho
├── GPIO 25 → botão B1
├── GPIO 33 → botão B2
├── GPIO 32 → botão B3
├── GPIO 21 → SDA do LCD
├── GPIO 22 → SCL do LCD
└── Bluetooth interno → transferência dos dados
```

A organização correta das conexões é essencial para garantir leituras estáveis, funcionamento adequado dos botões, exibição correta das telas e transferência confiável dos dados.
