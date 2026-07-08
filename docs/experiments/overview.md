# Experiments Overview

A seção de experimentos descreve como utilizar o **Spring-Mass Collector** para coletar, transferir e analisar dados em um sistema massa-mola amortecido.

O objetivo é apresentar um procedimento experimental organizado, desde a montagem do sistema até a obtenção dos dados no formato `.csv` para análise externa.

---

## Objetivo experimental

O objetivo principal do experimento é medir a posição de uma massa oscilante em função do tempo.

O Spring-Mass Collector fornece uma série temporal da posição relativa:

$$
x_{rel}(t)
$$

Essa série pode ser usada para estudar o comportamento de um oscilador amortecido, observando características como:

* período de oscilação;
* frequência;
* amplitude;
* decaimento da amplitude;
* comportamento transiente;
* comparação entre dados experimentais e modelo teórico.

---

## Sistema experimental

O experimento é composto por:

```text
Sistema massa-mola
        ↓
Massa oscilante
        ↓
Sensor infravermelho
        ↓
Spring-Mass Collector
        ↓
Arquivo .csv
        ↓
Análise externa
```

O sensor infravermelho mede a distância entre a caixa coletora e a massa. Após a calibração inicial, o sistema converte essa distância em posição relativa e armazena os dados como pares de tempo e posição.

---

## Papel do Spring-Mass Collector

Durante o experimento, o Spring-Mass Collector realiza quatro funções principais:

| Etapa         | Função                                      |
| ------------- | ------------------------------------------- |
| Calibração    | define a posição inicial de referência      |
| Coleta        | mede e armazena a posição relativa da massa |
| Exibição      | mostra informações resumidas no LCD         |
| Transferência | envia os dados por Bluetooth em formato CSV |

O sistema não realiza automaticamente a análise física dos dados. Sua função é fornecer uma aquisição organizada, permitindo que o usuário faça a análise posteriormente em outro software.

---

## Dado coletado

O dado final produzido pelo sistema possui o formato:

```text
t_ms,pos_cm
```

onde:

| Coluna   | Unidade | Descrição                                |
| -------- | ------- | ---------------------------------------- |
| `t_ms`   | ms      | tempo decorrido desde o início da coleta |
| `pos_cm` | cm      | posição relativa da massa                |

Um exemplo de arquivo gerado é:

```text
t_ms,pos_cm
25,0.0123
50,0.0181
75,0.0204
100,0.0195
END
```

A palavra `END` indica o final da transmissão. Para análise em softwares externos, essa linha pode ser removida caso a ferramenta utilizada não aceite esse marcador.

---

## Fluxo geral do experimento

Um experimento típico com o Spring-Mass Collector segue a sequência:

```text
1. Montar o sistema massa-mola.
2. Posicionar a caixa coletora.
3. Ajustar a altura do sensor.
4. Calibrar a posição inicial.
5. Iniciar a coleta.
6. Colocar a massa em oscilação.
7. Finalizar ou aguardar o fim da coleta.
8. Transferir os dados por Bluetooth.
9. Salvar o arquivo .csv.
10. Analisar os dados externamente.
```

Essa sequência transforma o experimento massa-mola em um processo quantitativo de aquisição de dados.

---

## Posicionamento da caixa

A caixa deve ser posicionada de modo que o sensor infravermelho fique alinhado com a massa oscilante.

Durante o posicionamento, verifique:

* se o sensor aponta diretamente para a massa;
* se a massa permanece dentro da faixa útil de leitura;
* se a caixa está estável sobre a bancada;
* se o extensor do sensor está travado;
* se não há obstáculos entre sensor e massa;
* se a superfície detectada reflete adequadamente o infravermelho.

A qualidade do alinhamento influencia diretamente a qualidade dos dados coletados.

!!! warning "Estabilidade do sensor"
Se a caixa ou o sensor se moverem durante a coleta, a variação medida pode não representar apenas o movimento da massa. Antes de iniciar o experimento, verifique se a estrutura está firme.

---

## Calibração antes da coleta

Antes de iniciar a coleta, o usuário deve calibrar a posição inicial.

A calibração define o valor:

$$
x_0
$$

Esse valor é usado para calcular a posição relativa:

$$
x_{rel}(t) = x(t) - x_0
$$

A calibração deve ser feita com a massa parada na posição de referência. Normalmente, essa posição corresponde ao equilíbrio do sistema massa-mola, mas o usuário pode escolher outro ponto dependendo do objetivo experimental.

---

## Coleta dos dados

Durante a coleta, o sistema armazena pares de tempo e posição.

O tempo é contado a partir do início da aquisição, enquanto a posição corresponde ao deslocamento relativo em relação à posição calibrada.

O LCD mostra apenas informações resumidas, como:

```text
x:   0.25 cm
N:    120 RUN
```

onde `x` é a posição relativa atual, `N` é o número de pontos armazenados e `RUN` indica que a coleta está em andamento.

---

## Transferência dos dados

Após a coleta, os dados são transferidos por Bluetooth.

Nos testes do projeto, foi utilizado o aplicativo **Serial Bluetooth Terminal**. O arquivo deve ser salvo preferencialmente com extensão:

```text
.csv
```

Esse formato facilita a importação dos dados em ferramentas como Python, Excel, MATLAB, Mathematica, Origin ou softwares equivalentes.

---

## Análise posterior

Depois de salvos, os dados podem ser usados para construir gráficos de posição em função do tempo.

O gráfico principal é:

```text
posição relativa × tempo
```

A partir desse gráfico, é possível comparar os dados experimentais com modelos de oscilação amortecida, como:

$$
x(t) = A e^{-\gamma t}\cos(\omega_d t + \phi)
$$

O ajuste do modelo permite estimar parâmetros como amplitude, frequência angular, fase inicial e coeficiente de amortecimento.

---

## Organização da seção

Esta seção está dividida em quatro páginas:

| Página          | Conteúdo                                   |
| --------------- | ------------------------------------------ |
| Data Collection | procedimento de aquisição dos dados        |
| Data Transfer   | envio e salvamento dos dados coletados     |
| Results         | organização e interpretação dos resultados |
| Overview        | visão geral do processo experimental       |

---

## Resumo

O experimento com o Spring-Mass Collector consiste em medir a posição relativa de uma massa oscilante ao longo do tempo.

```text
Experimento
├── Montagem do sistema massa-mola
├── Posicionamento do sensor
├── Calibração da posição inicial
├── Coleta de tempo e posição
├── Transferência Bluetooth
└── Análise dos dados em arquivo .csv
```

Com esse procedimento, o sistema massa-mola deixa de ser apenas uma observação visual e passa a gerar dados quantitativos para análise física.
