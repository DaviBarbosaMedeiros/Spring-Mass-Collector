# Hardware Overview

O hardware do **Spring-Mass Collector** foi projetado para integrar aquisição de dados, interface local, estrutura física de suporte e comunicação sem fio em um único equipamento didático.

O sistema utiliza uma **ESP32** como unidade de controle, um **sensor infravermelho de distância** para medir a posição da massa, um **display LCD 16x2 I2C** para apresentar informações ao usuário, três botões físicos para navegação entre os modos de operação e comunicação Bluetooth para transferência dos dados coletados.

Além da parte eletrônica, o projeto inclui uma caixa desenvolvida em modelagem 3D, responsável por organizar os componentes, proteger a eletrônica e posicionar corretamente o display e o sensor durante o experimento.

---

## Estrutura geral

O hardware pode ser entendido como a integração entre três partes principais:

| Parte               | Função                                                                    |
| ------------------- | ------------------------------------------------------------------------- |
| Unidade de controle | executa o firmware, processa as leituras e controla os modos de operação  |
| Sistema de medição  | realiza a leitura da distância entre o sensor e a massa                   |
| Interface física    | permite visualização, controle manual e posicionamento mecânico do sensor |

O fluxo físico e lógico do sistema pode ser resumido da seguinte forma:

```text
Sensor infravermelho
        ↓
Entrada analógica da ESP32
        ↓
Processamento da posição
        ↓
Armazenamento dos dados
        ↓
LCD 16x2 I2C e botões
        ↓
Transferência por Bluetooth
```

---

## Estrutura 3D da caixa

A estrutura física do Spring-Mass Collector foi desenvolvida para acomodar os componentes eletrônicos e facilitar o uso do equipamento durante o experimento.

<figure markdown>
  ![Estrutura 3D do Spring-Mass Collector](../assets/images/fig6.png){ width="750" }
  <figcaption>Render da estrutura 3D do Spring-Mass Collector, com região inclinada para o LCD 16x2 e extensor vertical para posicionamento do sensor.</figcaption>
</figure>

A caixa possui uma região frontal destinada ao display LCD 16x2. Essa região é inclinada em aproximadamente **30 graus**, permitindo melhor visualização da tela durante a operação do sistema.

A estrutura também possui aberturas para os botões físicos, posicionados de forma acessível ao usuário. Esses botões permitem controlar os modos de calibração, coleta e transferência sem a necessidade de conexão com um computador.

Outro elemento importante é o extensor vertical para o sensor infravermelho. Esse extensor permite ajustar a altura do sensor em até **três níveis**, adaptando o posicionamento do sistema de medição à geometria do experimento massa-mola.

O ajuste do extensor utiliza um sistema de trava mecânica. Para destravar o conjunto, o usuário pressiona simultaneamente as laterais do mecanismo, liberando o movimento vertical. Ao soltar as laterais, a trava volta a fixar o extensor na posição escolhida.

Esse mecanismo permite:

* ajustar a altura do sensor;
* manter o sensor estável durante a coleta;
* adaptar a caixa a diferentes configurações experimentais;
* facilitar a montagem e desmontagem do sistema;
* reduzir a necessidade de suportes externos.

---

## ESP32

A **ESP32** é o núcleo eletrônico do Spring-Mass Collector. Ela executa o firmware responsável pela leitura do sensor, controle do LCD, interpretação dos botões, armazenamento dos dados e comunicação Bluetooth.

A escolha da ESP32 é adequada para o projeto porque o microcontrolador possui recursos importantes para sistemas embarcados de aquisição de dados:

* entradas analógicas para leitura do sensor;
* comunicação Bluetooth integrada;
* capacidade de executar múltiplas tarefas;
* memória suficiente para armazenar milhares de amostras;
* compatibilidade com a Arduino IDE;
* baixo custo e ampla disponibilidade.

No sistema, a ESP32 atua como a unidade central que conecta o módulo de medição, a interface local e a transferência dos dados.

---

## Sensor infravermelho de distância

O sensor infravermelho é responsável por medir a distância entre a caixa coletora e a massa oscilante.

Durante o experimento, o sensor fornece um sinal analógico relacionado à distância medida. Esse sinal é lido pela ESP32 e convertido em uma estimativa de distância em centímetros.

A leitura feita pelo sensor representa inicialmente uma distância absoluta. Após a calibração, essa distância é convertida em posição relativa da massa em relação ao ponto de referência definido pelo usuário.

```text
Distância medida pelo sensor
        ↓
Conversão para centímetros
        ↓
Comparação com a posição inicial
        ↓
Cálculo da posição relativa
```

Na descrição geral do projeto, o componente pode ser chamado de **sensor infravermelho de distância**. Nas seções específicas de calibração e caracterização, o modelo utilizado e a curva de conversão são apresentados com mais detalhes.

---

## Entrada analógica da ESP32

A saída do sensor infravermelho é conectada a uma entrada analógica da ESP32.

No firmware atual, o pino usado para leitura do sensor é:

```cpp
const uint8_t SENSOR_PIN = 39;
```

A leitura analógica é feita pelo conversor ADC da ESP32. Com resolução de 12 bits, os valores lidos ficam na faixa aproximada:

```text
0 a 4095
```

Depois da leitura, o valor do ADC é convertido para tensão e, em seguida, para distância por meio de uma curva de calibração experimental.

A estabilidade dessa leitura depende de fatores como alimentação, ruído elétrico, alinhamento do sensor e distância entre o sensor e a massa.

---

## Display LCD 16x2 I2C

O display **LCD 16x2 I2C** é a interface visual local do sistema.

Ele mostra informações essenciais durante a operação, como:

* menu principal;
* modo atual;
* posição inicial calibrada;
* posição relativa durante a coleta;
* número de pontos armazenados;
* estado da coleta;
* status da transferência;
* aviso de memória cheia.

Exemplos de telas exibidas pelo sistema são:

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

A comunicação I2C reduz a quantidade de conexões necessárias entre a ESP32 e o display, simplificando a montagem interna da caixa.

Como o LCD é mais lento do que a rotina de aquisição, ele é usado apenas para exibir informações resumidas. Todos os dados coletados são armazenados internamente, mesmo que apenas parte das informações seja mostrada na tela.

---

## Botões físicos

O sistema utiliza três botões físicos para controlar a operação da caixa.

No firmware, os pinos associados aos botões são definidos como:

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

Com essa configuração, os pinos são configurados como:

```cpp
INPUT_PULLUP
```

Assim, o comportamento lógico dos botões é:

| Estado físico     | Leitura lógica |
| ----------------- | -------------- |
| botão solto       | HIGH           |
| botão pressionado | LOW            |

Cada botão possui uma função diferente dependendo do modo atual do sistema. Por isso, a interpretação dos botões é feita pelo firmware a partir da máquina de estados.

---

## Comunicação Bluetooth

A transferência dos dados é feita por Bluetooth.

No firmware, a comunicação utiliza Bluetooth Serial:

```cpp
BluetoothSerial SerialBT;
```

O dispositivo pode aparecer no celular ou computador com o nome:

```text
MassaMolaESP32
```

Durante a transferência, os dados são enviados em formato textual:

```text
t_ms,pos_cm
25,0.0123
50,0.0181
75,0.0204
END
```

Esse formato permite que os dados sejam recebidos por aplicativos de terminal Bluetooth, salvos em arquivo `.txt` e posteriormente importados em ferramentas de análise.

---

## Alimentação

A alimentação do sistema deve fornecer energia suficiente para a ESP32, o sensor infravermelho e o display LCD 16x2 I2C.

A escolha da alimentação deve considerar:

* tensão adequada para cada componente;
* estabilidade durante a coleta;
* corrente suficiente para o funcionamento do conjunto;
* segurança das conexões;
* praticidade para uso em laboratório didático.

!!! warning "Atenção"
Antes de ligar o sistema, verifique as tensões de operação dos componentes. Conexões incorretas podem danificar a ESP32, o sensor ou o display.

---

## Integração entre hardware e estrutura física

A caixa 3D não atua apenas como proteção para os componentes. Ela também faz parte da funcionalidade do sistema, pois define a posição do display, dos botões e do sensor em relação ao experimento.

A inclinação do LCD melhora a leitura durante a operação. A posição dos botões facilita a navegação pelos modos. O extensor vertical permite ajustar a altura do sensor e manter o alinhamento com a massa oscilante.

Essa integração entre eletrônica e mecânica é essencial para que o Spring-Mass Collector funcione como um equipamento de aquisição de dados, e não apenas como um circuito montado em bancada.

---

## Resumo do hardware

O hardware do Spring-Mass Collector é formado por:

```text
ESP32
├── Sensor infravermelho de distância
├── Display LCD 16x2 I2C
├── Três botões físicos
├── Comunicação Bluetooth
└── Estrutura 3D
    ├── Região inclinada para o LCD
    ├── Aberturas para botões
    └── Extensor vertical do sensor com trava mecânica
```

A combinação desses elementos permite medir a posição da massa, exibir o estado do experimento, armazenar os dados coletados e transferi-los para análise externa.
