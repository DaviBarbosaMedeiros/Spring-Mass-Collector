# Quick Start

Esta página apresenta um guia rápido para utilizar o **Spring-Mass Collector** durante um experimento massa-mola amortecido.

O objetivo é mostrar o fluxo básico de operação: ligar o sistema, calibrar a posição inicial, iniciar a coleta, transferir os dados e salvá-los para análise posterior.

---

## Visão geral do uso

O uso típico do sistema segue a sequência:

```text
Ligar o dispositivo
        ↓
Calibrar a posição inicial
        ↓
Iniciar a coleta de dados
        ↓
Pausar, resetar ou finalizar a coleta
        ↓
Entrar no modo de transferência
        ↓
Receber os dados por Bluetooth
        ↓
Salvar os dados em arquivo .txt
```

!!! note "Antes de iniciar"
Verifique se o sensor infravermelho está corretamente alinhado com a massa e se a caixa está posicionada de forma estável em relação ao sistema massa-mola.

---

## 1. Ligar o sistema

Ao ligar o Spring-Mass Collector, a ESP32 inicializa os módulos principais do sistema:

* leitura do sensor infravermelho;
* display LCD 16x2 I2C;
* botões físicos;
* armazenamento dos dados;
* comunicação Bluetooth.

Durante a inicialização, o LCD pode mostrar uma mensagem semelhante a:

```text
Massa-Mola
Inicializando
```

Após a inicialização, o sistema entra no modo padrão, exibindo o menu principal.

---

## 2. Acessar o menu principal

No modo padrão, o LCD apresenta as opções principais de operação.

Uma tela típica do menu é:

```text
1-Cal 2-Col
3-Transf
```

Nesse estado, cada botão acessa uma função principal:

| Botão | Função                          |
| ----- | ------------------------------- |
| B1    | entrar no modo de calibração    |
| B2    | entrar no modo de coleta        |
| B3    | entrar no modo de transferência |

O modo padrão não realiza coleta nem transferência. Ele apenas aguarda a escolha do usuário.

---

## 3. Calibrar a posição inicial

Antes de iniciar a coleta, é necessário calibrar a posição inicial da massa.

Para isso:

1. posicione a massa na posição de referência desejada;
2. pressione **B1** no menu principal;
3. aguarde a leitura da posição inicial;
4. confirme a calibração.

Durante a calibração, o sistema registra a distância atual medida pelo sensor como posição inicial:

```text
x₀
```

A partir desse valor, a posição relativa será calculada por:

$$
x_{rel}(t) = x(t) - x_0
$$

onde (x(t)) é a distância medida em cada instante e (x_0) é a posição inicial definida na calibração.

!!! warning "Calibração"
A calibração deve ser feita com a massa parada na posição de referência. Uma calibração feita com a massa em movimento pode deslocar incorretamente o zero experimental.

---

## 4. Iniciar a coleta

Após confirmar a calibração, volte ao menu principal e pressione **B2** para iniciar a coleta.

Ao entrar no modo de coleta, o sistema:

* limpa os dados anteriores;
* inicia a contagem de tempo;
* começa a medir a posição da massa;
* armazena os dados no formato `t_ms,pos_cm`.

Durante a coleta, o LCD pode mostrar informações como:

```text
x:   0.25 cm
N:    120 RUN
```

onde:

| Campo | Significado                  |
| ----- | ---------------------------- |
| `x`   | posição relativa atual       |
| `N`   | número de pontos armazenados |
| `RUN` | coleta em andamento          |

---

## 5. Controlar a coleta

Durante o modo de coleta, os botões permitem controlar o experimento.

| Botão | Função                                |
| ----- | ------------------------------------- |
| B1    | pausar ou retomar a coleta            |
| B2    | resetar os dados e reiniciar a coleta |
| B3    | voltar ao menu principal              |

Quando a coleta está pausada, o sistema interrompe temporariamente o armazenamento de novos pontos. Quando retomada, a aquisição volta a registrar novos dados.

!!! note "Exibição no LCD"
O LCD mostra apenas uma visualização resumida do experimento. A taxa de atualização da tela não representa necessariamente a taxa real de armazenamento dos dados.

---

## 6. Memória cheia

O sistema possui um limite máximo de pontos que podem ser armazenados durante uma coleta.

Quando esse limite é atingido, a coleta é interrompida automaticamente e o LCD pode mostrar:

```text
MEMORIA CHEIA
```

Nesse caso, o usuário pode:

* transferir os dados armazenados;
* resetar a coleta;
* alterar o limite máximo de dados no modo de transferência;
* iniciar uma nova coleta.

!!! warning "Dados armazenados"
Ao resetar a coleta, os dados anteriores são apagados da memória. Transfira os dados antes de reiniciar caso deseje preservá-los.

---

## 7. Entrar no modo de transferência

Após finalizar a coleta, volte ao menu principal e pressione **B3** para entrar no modo de transferência.

Nesse modo, o LCD pode mostrar:

```text
Modo Transfer
D: 120 M:5000
```

onde:

| Campo | Significado                        |
| ----- | ---------------------------------- |
| `D`   | quantidade de dados armazenados    |
| `M`   | limite máximo de dados configurado |

No modo de transferência:

| Botão | Função                                 |
| ----- | -------------------------------------- |
| B1    | enviar os dados por Bluetooth e Serial |
| B2    | voltar ao menu principal               |
| B3    | alterar a quantidade máxima de dados   |

---

## 8. Conectar ao Bluetooth

Para receber os dados em um dispositivo externo, utilize um aplicativo ou programa de terminal Bluetooth.

Nos testes do projeto, foi utilizado o aplicativo **Serial Bluetooth Terminal**.

O procedimento básico é:

1. ativar o Bluetooth no celular ou computador;
2. abrir o aplicativo de terminal Bluetooth;
3. procurar pelo dispositivo da ESP32;
4. conectar ao dispositivo;
5. iniciar a transferência pela caixa coletora.

O nome do dispositivo Bluetooth pode aparecer como:

```text
MassaMolaESP32
```

!!! note "Terminal Bluetooth"
O Serial Bluetooth Terminal foi utilizado como aplicativo de referência durante os testes, mas outros terminais Bluetooth compatíveis também podem ser utilizados.

---

## 9. Transferir os dados

Com o terminal Bluetooth conectado, pressione **B1** no modo de transferência.

O sistema envia os dados em formato textual:

```text
t_ms,pos_cm
25,0.0123
50,0.0181
75,0.0204
100,0.0195
END
```

A primeira linha indica o cabeçalho dos dados. As linhas seguintes contêm os pares de tempo e posição. A palavra `END` indica o final da transmissão.

---

## 10. Salvar os dados

Após receber os dados no terminal Bluetooth, salve a saída em um arquivo `.txt`.

Um nome de arquivo recomendado é:

```text
spring_mass_data.txt
```

Esse arquivo pode ser importado posteriormente em ferramentas de análise, como:

* Python;
* Excel;
* MATLAB;
* Mathematica;
* Origin;
* softwares equivalentes de análise de dados.

---

## 11. Analisar os dados

O arquivo transferido contém uma série temporal da posição relativa da massa:

$$
x_{rel}(t)
$$

A partir dessa série, é possível construir um gráfico de posição em função do tempo e comparar os dados experimentais com modelos de oscilação amortecida.

Um modelo típico para esse tipo de sistema é:

$$
x(t) = A e^{-\gamma t}\cos(\omega_d t + \phi)
$$

O Spring-Mass Collector não realiza automaticamente o ajuste do modelo. Sua função principal é coletar e transferir os dados de forma organizada para análise externa.

---

## Resumo rápido

```text
1. Ligue o sistema.
2. No menu principal, pressione B1 para calibrar.
3. Posicione a massa no ponto de referência.
4. Confirme a calibração.
5. Pressione B2 para iniciar a coleta.
6. Controle a coleta com os botões.
7. Pressione B3 para acessar a transferência.
8. Conecte ao Bluetooth pelo terminal.
9. Pressione B1 para enviar os dados.
10. Salve os dados recebidos em .txt.
```

Após seguir esses passos, os dados estarão prontos para análise experimental.
