# Spring-Mass Collector

## Um sistema didático e de baixo custo para aquisição, exibição e transferência de dados de posição em experimentos massa-mola amortecidos.

<figure markdown>
  ![Protótipo funcional do Spring-Mass Collector](assets/images/5.1.1-Setup_Superior.png){ width="850" }
  <figcaption>Protótipo funcional do Spring-Mass Collector utilizado para aquisição de dados em experimentos massa-mola.</figcaption>
</figure>

---

O **Spring-Mass Collector** é um sistema embarcado de aquisição de dados desenvolvido para experimentos massa-mola não estáticos. O projeto utiliza uma ESP32, um sensor infravermelho de distância, um display LCD 16x2 I2C, botões de controle e comunicação Bluetooth para medir, armazenar, exibir e transferir dados experimentais de posição.

A proposta do sistema é substituir métodos manuais de medição, como gravações em vídeo com réguas posicionadas ao fundo do experimento, por uma solução automática, portátil e reprodutível. Após uma calibração inicial, a distância medida pelo sensor é convertida em deslocamento relativo da massa em relação à posição de equilíbrio.

Os dados coletados são armazenados no formato `t_ms,pos_cm` e podem ser transferidos por Bluetooth para um dispositivo externo. Nos testes do projeto, foi utilizado o aplicativo **Serial Bluetooth Terminal**, mas os dados também podem ser recebidos por outros terminais Bluetooth compatíveis.

---

## Principais recursos

<div class="grid cards" markdown>

* :material-ruler-square:{ .lg .middle } **Medição de posição**

  ---

  Mede a distância entre o sensor infravermelho e a massa oscilante durante o experimento.

* :material-crosshairs-gps:{ .lg .middle } **Calibração inicial**

  ---

  Define a posição de referência para calcular o deslocamento relativo da massa.

* :material-chart-line:{ .lg .middle } **Coleta automática**

  ---

  Registra dados de tempo e posição sem necessidade de análise manual quadro a quadro.

* :material-monitor:{ .lg .middle } **Interface local**

  ---

  Utiliza display LCD 16x2 I2C e botões físicos para controlar os modos de operação.

* :material-bluetooth:{ .lg .middle } **Transferência Bluetooth**

  ---

  Envia os dados armazenados para um celular ou computador por meio de comunicação Bluetooth.

* :material-school-outline:{ .lg .middle } **Uso didático**

  ---

  Apoia o ensino experimental de oscilações, sensores, aquisição de dados e análise computacional.

</div>

---

## Visão geral do sistema

O funcionamento da caixa coletora pode ser resumido em cinco etapas:

```text
Calibrar posição inicial
        ↓
Medir distância atual
        ↓
Calcular posição relativa
        ↓
Armazenar tempo e posição
        ↓
Transferir dados por Bluetooth
```

O dado experimental principal produzido pelo sistema é uma série temporal no formato:

```text
t_ms,pos_cm
```

em que `t_ms` representa o tempo em milissegundos e `pos_cm` representa a posição relativa da massa em centímetros.

Esses dados podem ser usados posteriormente para construir gráficos de posição em função do tempo e realizar análises associadas ao movimento oscilatório amortecido.

---

## Estrutura da documentação

<div class="grid cards" markdown>

-   :material-rocket-launch-outline:{ .lg .middle } **[Getting Started](getting-started/overview.md)**

    ---

    Introdução ao funcionamento do sistema e primeiros passos de uso.

-   :material-waveform:{ .lg .middle } **[Theory](theory/spring-mass-system.md)**

    ---

    Modelo físico do sistema massa-mola, oscilador amortecido e análise dos dados.

-   :material-chip:{ .lg .middle } **[Hardware](hardware/overview.md)**

    ---

    Componentes eletrônicos, sensor infravermelho, LCD, botões e conexões.

-   :material-cube-outline:{ .lg .middle } **[Mechanical Design](mechanical-design/overview.md)**

    ---

    Estrutura física, caixa 3D, montagem e integração mecânica do sistema.

-   :material-code-braces:{ .lg .middle } **[Software](software/overview.md)**

    ---

    Arquitetura do firmware, modos de operação, armazenamento e Bluetooth.

-   :material-flask-outline:{ .lg .middle } **[Experiments](experiments/overview.md)**

    ---

    Procedimentos de coleta, transferência e análise experimental dos dados.

</div>

---

## Relevância do projeto

O Spring-Mass Collector foi desenvolvido para tornar experimentos massa-mola mais acessíveis, quantitativos e reprodutíveis em ambientes didáticos. A utilização de uma ESP32 permite integrar leitura de sensores, interface local e comunicação sem fio em uma plataforma de baixo custo.

Entre os principais pontos de relevância estão:

* redução do custo de instrumentação experimental;
* substituição de métodos manuais de medição;
* coleta automática de dados de posição;
* apoio ao ensino de oscilações amortecidas;
* possibilidade de reprodução em laboratórios didáticos;
* uso de tecnologias acessíveis, como ESP32, Arduino IDE e comunicação Bluetooth.

---

## Próximos passos

Para entender o funcionamento geral da caixa coletora, comece pela seção **Getting Started**. Em seguida, consulte as páginas de **Mechanical Design**, **Electronic** e **Software** para compreender como a estrutura física, circuito e sistema lógico foram organizados.
