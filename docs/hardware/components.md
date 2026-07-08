# Components

Esta página apresenta os principais componentes utilizados no **Spring-Mass Collector** e a função de cada um dentro do sistema.

A lista descreve a versão atual do protótipo funcional. Alguns componentes podem ser modificados em versões futuras, mas a arquitetura geral do sistema permanece baseada em aquisição de distância, controle local, armazenamento e transferência dos dados.

---

## Visão geral dos componentes

O Spring-Mass Collector é formado por componentes eletrônicos, elementos de interface e partes estruturais impressas em 3D.

De forma geral, o sistema pode ser dividido em:

```text
Controle embarcado
        ↓
Medição de distância
        ↓
Interface local
        ↓
Armazenamento dos dados
        ↓
Transferência Bluetooth
        ↓
Estrutura física de suporte
```

---

## Componentes principais

| Componente                        | Função no sistema                                        |
| --------------------------------- | -------------------------------------------------------- |
| ESP32                             | unidade central de controle, processamento e comunicação |
| Sensor infravermelho de distância | mede a distância entre o sensor e a massa                |
| Display LCD 16x2 I2C              | exibe menus, estados e informações resumidas             |
| Botões físicos                    | permitem controlar os modos de operação                  |
| Comunicação Bluetooth             | envia os dados coletados para um dispositivo externo     |
| Estrutura 3D                      | organiza, protege e posiciona os componentes             |
| Extensor do sensor                | permite ajustar a altura do sensor em diferentes níveis  |
| Sistema de trava mecânica         | fixa o extensor na altura escolhida                      |
| Alimentação                       | fornece energia para a ESP32, sensor e display           |

---

## ESP32

A **ESP32** é o componente central do Spring-Mass Collector.

Ela é responsável por:

* executar o firmware;
* ler o sensor infravermelho;
* converter a leitura analógica em distância;
* calcular a posição relativa da massa;
* controlar o display LCD;
* interpretar os botões;
* armazenar os dados coletados;
* enviar os dados por Bluetooth.

A escolha da ESP32 é adequada para o projeto porque o microcontrolador possui Bluetooth integrado, entradas analógicas, boa capacidade de processamento e compatibilidade com a Arduino IDE.

<div class="grid cards" markdown>

* :material-chip:{ .lg .middle } **Microcontrolador**

  ---

  Executa o firmware e coordena todos os módulos do sistema.

* :material-bluetooth:{ .lg .middle } **Bluetooth integrado**

  ---

  Permite transferir os dados sem necessidade de conexão USB durante o experimento.

* :material-memory:{ .lg .middle } **Memória interna**

  ---

  Armazena temporariamente os dados de tempo e posição durante a coleta.

</div>

---

## Sensor infravermelho de distância

O sensor infravermelho é responsável pela medição da distância entre a caixa coletora e a massa oscilante.

O modelo utilizado no protótipo é o **GP2Y0A41SK0F**.

Esse sensor fornece uma saída analógica relacionada à distância do objeto detectado. A ESP32 lê essa tensão por meio do ADC e o firmware converte o valor medido em distância.

A leitura do sensor é usada posteriormente para calcular a posição relativa da massa.

```text
Sensor infravermelho
        ↓
Tensão analógica
        ↓
Leitura ADC na ESP32
        ↓
Distância estimada
        ↓
Posição relativa
```

A caracterização completa do sensor, incluindo a curva experimental de conversão entre tensão e distância, é apresentada na página **Distance Sensor**.

---

## Display LCD 16x2 I2C

O display **LCD 16x2 I2C** é utilizado como interface visual local.

Ele permite que o usuário acompanhe o estado do sistema sem depender de um computador ou celular durante a coleta.

O LCD pode exibir informações como:

* menu principal;
* modo atual;
* posição inicial calibrada;
* posição relativa atual;
* número de dados armazenados;
* estado da coleta;
* modo de transferência;
* aviso de memória cheia.

Exemplos de telas utilizadas no sistema:

```text
1-Cal 2-Col
3-Transf
```

```text
x:   0.25 cm
N:    120 RUN
```

```text
Modo Transfer
D: 120 M:5000
```

A comunicação por I2C reduz o número de conexões necessárias, facilitando a montagem interna da caixa.

---

## Botões físicos

O Spring-Mass Collector utiliza **três botões físicos** para controlar a navegação entre os modos de operação.

Cada botão assume uma função diferente dependendo do modo atual do sistema.

| Modo          | B1             | B2                | B3                      |
| ------------- | -------------- | ----------------- | ----------------------- |
| Default       | Calibração     | Coleta            | Transferência           |
| Calibração    | Recalibrar     | Confirmar         | Zerar posição inicial   |
| Coleta        | Pausar/retomar | Resetar coleta    | Voltar ao Default       |
| Transferência | Enviar dados   | Voltar ao Default | Alterar limite de dados |

No firmware atual, os pinos associados aos botões são:

```cpp
const uint8_t buttonPins[BUTTON_QTD] = {
  25,
  33,
  32
};
```

A ligação considerada é:

```text
GPIO ---- botão ---- GND
```

Com essa configuração, os pinos são configurados como `INPUT_PULLUP`, de modo que o botão solto corresponde a `HIGH` e o botão pressionado corresponde a `LOW`.

---

## Estrutura 3D

A estrutura 3D tem a função de organizar os componentes e transformar o circuito eletrônico em um equipamento utilizável durante o experimento.

Ela inclui:

* região inclinada para o display LCD 16x2;
* abertura para os três botões físicos;
* espaço interno para acomodação da ESP32 e conexões;
* extensor vertical para o sensor infravermelho;
* sistema de trava mecânica para ajuste da altura do sensor.

A região do display possui inclinação de aproximadamente **30 graus**, melhorando a visualização da tela durante a operação.

O extensor do sensor permite posicionamento em até **três níveis de altura**, ajudando a alinhar o sensor com a massa oscilante.

O sistema de trava mecânica é destravado ao pressionar simultaneamente as laterais do mecanismo. Ao soltar as laterais, o extensor volta a ser fixado na posição escolhida.

---

## Comunicação Bluetooth

A comunicação Bluetooth permite transferir os dados armazenados para um dispositivo externo.

No firmware, a comunicação é feita por Bluetooth Serial:

```cpp
BluetoothSerial SerialBT;
```

O dispositivo aparece no celular com o nome:

```text
MassaMolaEsp32
```

Durante a transferência, os dados são enviados em formato CSV:

```text
t_ms,pos_cm
25,0.0123
50,0.0181
75,0.0204
END
```

O arquivo deve ser salvo preferencialmente com a extensão `.csv`, facilitando a importação em programas de análise.

---

## Alimentação

O sistema precisa de uma alimentação capaz de fornecer energia para:

* ESP32;
* sensor infravermelho;
* display LCD 16x2 I2C;
* demais elementos conectados ao circuito.

A alimentação deve ser estável para evitar ruídos na leitura do sensor e falhas durante a transferência dos dados.

Antes de ligar o sistema, é necessário verificar a tensão de operação dos componentes e garantir que as conexões estejam corretas.

!!! warning "Atenção à alimentação"
Conexões incorretas ou tensões inadequadas podem danificar a ESP32, o sensor infravermelho ou o display LCD.

---

## Integração dos componentes

A função de cada componente não é isolada. O sistema depende da integração entre eletrônica, estrutura física e firmware.

| Etapa                       | Componentes envolvidos                            |
| --------------------------- | ------------------------------------------------- |
| Medição da distância        | sensor infravermelho e entrada analógica da ESP32 |
| Conversão da leitura        | ESP32 e firmware                                  |
| Controle do usuário         | botões físicos e máquina de estados               |
| Exibição local              | display LCD 16x2 I2C                              |
| Armazenamento               | memória da ESP32                                  |
| Transferência               | Bluetooth Serial                                  |
| Posicionamento experimental | estrutura 3D e extensor do sensor                 |

Essa integração permite que o Spring-Mass Collector funcione como um equipamento embarcado completo para aquisição de dados em experimentos massa-mola.

---

## Organização funcional

O conjunto de componentes pode ser organizado da seguinte forma:

```text
Spring-Mass Collector
├── Controle
│   └── ESP32
│
├── Medição
│   └── Sensor infravermelho de distância
│
├── Interface
│   ├── LCD 16x2 I2C
│   └── Três botões físicos
│
├── Comunicação
│   └── Bluetooth Serial
│
└── Estrutura física
    ├── Caixa 3D
    ├── Suporte inclinado do LCD
    ├── Extensor vertical do sensor
    └── Trava mecânica lateral
```

---

## Resumo

Os componentes do Spring-Mass Collector foram escolhidos para permitir uma solução de baixo custo, simples de operar e adequada para laboratório didático.

A ESP32 centraliza o controle do sistema, o sensor infravermelho realiza a medição da distância, o LCD e os botões formam a interface local, o Bluetooth permite transferir os dados e a estrutura 3D organiza fisicamente o conjunto.

Essa combinação permite transformar um experimento massa-mola visual em um procedimento quantitativo de aquisição de dados.
