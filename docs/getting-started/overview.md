# Overview

O **Spring-Mass Collector** é uma caixa coletora de dados desenvolvida para medir, exibir, armazenar e transferir dados de posição em experimentos massa-mola amortecidos.

O sistema foi projetado para substituir métodos manuais de medição, como gravações em vídeo com uma régua posicionada ao fundo do experimento, por uma solução automática baseada em sensor infravermelho, ESP32, interface local e comunicação Bluetooth.

---

## Objetivo

O objetivo principal do Spring-Mass Collector é facilitar a aquisição de dados em experimentos massa-mola não estáticos.

Em um experimento tradicional, a posição da massa pode ser obtida manualmente a partir de vídeos, marcações em régua e análise quadro a quadro. Embora esse método seja possível, ele pode ser demorado, pouco prático e sujeito a erros de leitura.

O Spring-Mass Collector automatiza esse processo ao medir a posição da massa ao longo do tempo e armazenar os dados em um formato simples para análise posterior.

---

## Problema experimental

Em sistemas massa-mola amortecidos, a massa permanece em movimento durante a coleta. Isso dificulta a medição direta da posição em função do tempo.

Um procedimento manual típico pode ser representado como:

```text
Gravar o experimento
        ↓
Usar uma régua como referência visual
        ↓
Analisar o vídeo quadro a quadro
        ↓
Anotar manualmente a posição da massa
        ↓
Montar uma tabela tempo × posição
```

Esse processo apresenta algumas limitações:

* exige análise manual dos dados;
* depende da qualidade da gravação;
* pode introduzir erro de paralaxe;
* exige bom posicionamento da câmera;
* torna a repetição do experimento mais lenta;
* dificulta o uso em atividades didáticas com muitos alunos.

O Spring-Mass Collector busca reduzir essas dificuldades por meio de uma aquisição automática e direta da posição.

---

## Solução proposta

A solução proposta é uma caixa coletora de dados baseada em ESP32, sensor infravermelho de distância, display LCD 16x2 I2C, botões físicos e comunicação Bluetooth.

A lógica geral do sistema é:

```text
Sensor infravermelho mede a distância
        ↓
ESP32 processa a leitura
        ↓
Posição relativa é calculada
        ↓
Dados são armazenados em memória
        ↓
Informações resumidas aparecem no LCD
        ↓
Dados são transferidos por Bluetooth
```

A partir da calibração inicial, o sistema deixa de trabalhar apenas com a distância absoluta entre o sensor e a massa. Em vez disso, passa a registrar o deslocamento relativo da massa em relação a uma posição inicial de referência.

---

## Dado experimental gerado

O principal dado produzido pelo sistema é uma série temporal de posição.

O formato de saída utilizado é:

```text
t_ms,pos_cm
```

onde:

| Campo    | Descrição                                       |
| -------- | ----------------------------------------------- |
| `t_ms`   | tempo em milissegundos desde o início da coleta |
| `pos_cm` | posição relativa da massa em centímetros        |

Um exemplo de saída é:

```text
t_ms,pos_cm
25,0.0123
50,0.0181
75,0.0204
100,0.0195
END
```

Esse formato pode ser salvo em arquivo `.txt` e depois importado em ferramentas como Python, Excel, MATLAB, Mathematica, Origin ou outros softwares de análise de dados.

---

## Módulos principais

O Spring-Mass Collector pode ser dividido em dois módulos principais:

<div class="grid cards" markdown>

* :material-cube-outline:{ .lg .middle } **Módulo estrutural**

  ---

  Inclui a caixa física, a estrutura de montagem, a ESP32, o sensor infravermelho, o display LCD 16x2 I2C, os botões e a organização dos componentes eletrônicos.

* :material-state-machine:{ .lg .middle } **Módulo lógico**

  ---

  Inclui os modos de operação do firmware: menu principal, calibração, coleta e transferência dos dados.

</div>

Essa divisão ajuda a separar o desenvolvimento físico do equipamento da lógica implementada no firmware.

---

## Interface de operação

O sistema foi pensado para ser usado de forma simples em laboratório didático. O usuário interage com a caixa por meio de:

* três botões físicos;
* um display LCD 16x2 I2C;
* conexão Bluetooth com dispositivo externo.

Os botões controlam os modos de operação, enquanto o LCD apresenta informações sobre o estado atual da caixa, como modo ativo, posição medida, quantidade de dados armazenados e status da coleta.

---

## Modos de operação

O firmware é organizado em modos de funcionamento. Cada modo define o comportamento da caixa e a função de cada botão.

| Modo          | Função principal                         |
| ------------- | ---------------------------------------- |
| Default       | apresenta o menu principal               |
| Calibração    | define a posição inicial de referência   |
| Coleta        | mede e armazena os dados de posição      |
| Transferência | envia os dados armazenados por Bluetooth |

Essa estrutura permite que o sistema funcione como uma máquina de estados, tornando o firmware mais organizado e facilitando futuras modificações.

---

## Transferência dos dados

Após a coleta, os dados podem ser transferidos por Bluetooth para um dispositivo externo.

Nos testes do projeto, foi utilizado o aplicativo **Serial Bluetooth Terminal**, que permite receber os dados enviados pela ESP32 e salvá-los em arquivo `.txt`.

!!! note "Aplicativo de terminal Bluetooth"
O Serial Bluetooth Terminal foi utilizado como aplicativo de referência durante os testes, mas o sistema pode ser usado com outros terminais Bluetooth compatíveis.

A transferência dos dados é feita em formato textual, o que facilita a leitura, o armazenamento e a importação dos dados em diferentes ferramentas de análise.

---

## Aplicação didática

O Spring-Mass Collector foi desenvolvido para apoiar o ensino experimental de oscilações amortecidas.

Com os dados coletados, é possível estudar:

* posição em função do tempo;
* período de oscilação;
* frequência;
* amplitude;
* decaimento da amplitude;
* comportamento amortecido;
* comparação entre modelo teórico e dados experimentais.

Além da física do sistema massa-mola, o projeto também permite discutir conceitos de instrumentação, sensores, calibração, aquisição de dados, programação embarcada e análise computacional.

---

## Próxima etapa

A próxima página apresenta uma explicação direta do funcionamento interno do sistema, desde a leitura do sensor infravermelho até o envio dos dados por Bluetooth.
