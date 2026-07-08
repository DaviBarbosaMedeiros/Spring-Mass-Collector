# Data Storage

O armazenamento de dados no **Spring-Mass Collector** é responsável por guardar temporariamente os pontos coletados durante o experimento. Cada ponto contém o tempo decorrido desde o início da coleta e a posição relativa da massa em centímetros.

Essa etapa permite que a coleta seja realizada primeiro e a transferência seja feita depois, sem exigir que o dispositivo Bluetooth esteja conectado durante todo o experimento.

---

## Função do armazenamento

Durante a coleta, o sistema mede continuamente a posição da massa. Cada medida precisa ser registrada para que o movimento possa ser analisado posteriormente.

O fluxo geral é:

```text
Sensor mede a distância
        ↓
Firmware calcula a posição relativa
        ↓
Tempo atual da coleta é registrado
        ↓
Ponto experimental é armazenado
        ↓
Dados ficam disponíveis para transferência
```

O armazenamento permite construir uma série temporal da posição:

$$
x_{rel}(t)
$$

Essa série é a base para a análise do movimento massa-mola.

---

## Estrutura de um ponto experimental

Cada ponto armazenado contém duas informações principais:

| Campo         | Unidade | Descrição                                |
| ------------- | ------- | ---------------------------------------- |
| `time_ms`     | ms      | tempo decorrido desde o início da coleta |
| `position_cm` | cm      | posição relativa da massa                |

No firmware, essa estrutura pode ser representada por:

```cpp
struct DataPoint {
  uint32_t time_ms;
  float position_cm;
};
```

O campo `time_ms` registra o tempo em milissegundos. O campo `position_cm` registra a posição relativa calculada a partir da calibração inicial.

---

## Posição relativa armazenada

O valor armazenado em `position_cm` não corresponde diretamente à distância absoluta medida pelo sensor.

Antes de ser armazenada, a distância medida é convertida em posição relativa:

$$
x_{rel}(t) = x(t) - x_0
$$

onde:

| Símbolo      | Descrição                                     |
| ------------ | --------------------------------------------- |
| $x(t)$       | distância medida pelo sensor em cada instante |
| $x_0$        | posição inicial definida na calibração        |
| $x_{rel}(t)$ | posição relativa armazenada                   |

Assim, os dados salvos já estão no formato adequado para análise do movimento da massa em relação à posição de referência.

---

## Buffer de dados

Os dados são armazenados em um vetor na memória RAM da ESP32.

Conceitualmente, o buffer pode ser representado como:

```cpp
DataPoint dataBuffer[DATA_BUFFER_CAPACITY];
```

Cada posição do vetor armazena um ponto experimental.

```text
dataBuffer[0]  → primeiro ponto coletado
dataBuffer[1]  → segundo ponto coletado
dataBuffer[2]  → terceiro ponto coletado
...
```

O número de pontos armazenados é controlado por uma variável de contagem, como:

```cpp
dataCount
```

Essa variável indica quantos pontos válidos existem no buffer.

---

## Capacidade do buffer

A capacidade física do buffer é definida no firmware por uma constante.

Um exemplo de definição é:

```cpp
DATA_BUFFER_CAPACITY = 5000;
```

Isso significa que o vetor possui espaço reservado para até 5000 pontos experimentais.

Como cada ponto possui aproximadamente:

```text
uint32_t time_ms    → 4 bytes
float position_cm   → 4 bytes
```

cada ponto ocupa cerca de:

$$
4 + 4 = 8 \ \text{bytes}
$$

Para 5000 pontos, o uso aproximado de memória é:

$$
5000 \times 8 = 40000 \ \text{bytes}
$$

ou aproximadamente:

$$
40 \ \text{kB}
$$

Esse valor é aceitável para a ESP32 e permite armazenar uma quantidade suficiente de dados para experimentos didáticos.

---

## Limite máximo configurável

Além da capacidade física do buffer, o sistema possui um limite máximo configurável de pontos por coleta.

Esse limite pode ser alterado pelo usuário no modo de transferência, usando o botão **B3**.

Um ciclo possível de configuração é:

```text
500 → 1000 → 2000 → 3000 → 5000 → 500
```

Essa configuração não altera o tamanho físico do vetor reservado em memória. Ela apenas define quantos pontos o sistema deve coletar antes de interromper automaticamente a aquisição.

---

## Capacidade física e limite lógico

É importante distinguir dois conceitos:

| Conceito          | Significado                                               |
| ----------------- | --------------------------------------------------------- |
| capacidade física | tamanho máximo do vetor reservado na memória              |
| limite lógico     | quantidade máxima de pontos escolhida para a coleta atual |

Por exemplo, se a capacidade física for:

```cpp
DATA_BUFFER_CAPACITY = 5000;
```

mas o usuário escolher:

```text
M = 1000
```

então a coleta será interrompida ao atingir 1000 pontos, mesmo que o vetor tenha espaço para até 5000.

Essa diferença permite realizar experimentos mais curtos sem modificar o firmware.

---

## Inicialização de uma nova coleta

Ao iniciar uma nova coleta, o sistema precisa limpar os dados anteriores e reiniciar a contagem de tempo.

Conceitualmente, a lógica é:

```cpp
resetDataBuffer();
collectionActive = true;
collectionPaused = false;
collectionStartMs = millis();
```

A função `resetDataBuffer()` limpa o estado do armazenamento, enquanto `collectionStartMs` define o instante inicial da nova aquisição.

Depois disso, os tempos armazenados passam a ser calculados em relação ao início da coleta.

---

## Registro do tempo

O tempo de cada ponto é calculado a partir da diferença entre o tempo atual do sistema e o instante inicial da coleta.

Conceitualmente:

```cpp
time_ms = millis() - collectionStartMs;
```

Assim, o primeiro ponto da coleta possui tempo próximo de zero ou do primeiro intervalo de amostragem, e os pontos seguintes representam o avanço temporal do experimento.

O formato final armazenado é:

```text
tempo desde o início da coleta, posição relativa
```

---

## Adição de novos pontos

Durante a coleta, a tarefa de aquisição chama uma função para adicionar novos pontos ao buffer.

Uma função conceitual pode ser:

```cpp
bool addDataPoint(uint32_t time_ms, float position_cm);
```

Essa função deve:

```text
1. Verificar se ainda existe espaço no buffer.
2. Armazenar o tempo.
3. Armazenar a posição.
4. Incrementar o contador de dados.
5. Informar se a gravação foi bem-sucedida.
```

Esse processo evita manipulação direta do vetor por diferentes partes do firmware.

---

## Memória cheia

Quando o número de pontos armazenados atinge o limite configurado, o sistema interrompe a coleta automaticamente.

O comportamento esperado é:

```text
dataCount atinge maxDataPoints
        ↓
sistema marca o buffer como cheio
        ↓
coleta é interrompida
        ↓
LCD mostra MEMORIA CHEIA
```

No firmware, a interrupção da coleta pode ser representada por:

```cpp
collectionPaused = true;
collectionActive = false;
```

Esse procedimento impede que o sistema tente gravar dados além do limite permitido.

!!! warning "Memória cheia"
Quando a memória atinge o limite configurado, a coleta é interrompida. Para preservar os dados, transfira o conteúdo armazenado antes de resetar a coleta.

---

## Leitura dos dados armazenados

Durante a transferência, o sistema precisa acessar os pontos armazenados no buffer.

Uma função conceitual para recuperar um ponto pode ser:

```cpp
bool getDataPoint(size_t index, DataPoint &point);
```

Essa função permite acessar um ponto específico sem expor diretamente o vetor global a outros módulos.

O envio dos dados percorre o buffer desde o primeiro ponto até o último ponto válido:

```text
dataBuffer[0]
dataBuffer[1]
dataBuffer[2]
...
dataBuffer[dataCount - 1]
```

---

## Último ponto coletado

O sistema também pode acessar o último ponto armazenado para atualizar o LCD durante a coleta.

Uma função conceitual pode ser:

```cpp
DataPoint getLatestDataPoint();
```

Esse recurso permite mostrar na tela a posição mais recente e a quantidade de pontos armazenados:

```text
x:   0.25 cm
N:    120 RUN
```

O LCD usa essa informação apenas como visualização resumida. Todos os pontos continuam salvos no buffer.

---

## Formato de exportação

Durante a transferência, os dados são enviados no formato CSV.

O cabeçalho é:

```text
t_ms,pos_cm
```

Cada linha seguinte contém um par de tempo e posição:

```text
25,0.0123
50,0.0181
75,0.0204
100,0.0195
```

Ao final da transmissão, o sistema envia:

```text
END
```

Um exemplo completo é:

```text
t_ms,pos_cm
25,0.0123
50,0.0181
75,0.0204
100,0.0195
END
```

Recomenda-se salvar o arquivo recebido com extensão `.csv`.

---

## Funções do módulo Storage

O módulo `Storage` concentra as operações relacionadas ao armazenamento dos dados.

As principais funções podem ser:

```cpp
void resetDataBuffer();
bool addDataPoint(uint32_t time_ms, float position_cm);
bool getDataPoint(size_t index, DataPoint &point);
DataPoint getLatestDataPoint();
size_t getDataCount();
bool isDataBufferFull();
void printDataCSV();
```

Cada função possui uma responsabilidade específica:

| Função                 | Responsabilidade                         |
| ---------------------- | ---------------------------------------- |
| `resetDataBuffer()`    | limpa o buffer e reinicia a contagem     |
| `addDataPoint()`       | adiciona um novo ponto experimental      |
| `getDataPoint()`       | recupera um ponto específico             |
| `getLatestDataPoint()` | retorna o ponto mais recente             |
| `getDataCount()`       | informa quantos pontos estão armazenados |
| `isDataBufferFull()`   | verifica se o limite foi atingido        |
| `printDataCSV()`       | exporta os dados no formato CSV          |

Essa separação melhora a organização do firmware e reduz o risco de erros no acesso ao buffer.

---

## Proteção com mutex

Como o sistema utiliza tarefas simultâneas, o buffer pode ser acessado por mais de uma tarefa.

Por exemplo:

```text
TaskSensor      → escreve novos dados
TaskDisplay     → lê o último dado
TaskBluetooth   → lê todos os dados para transferência
```

Para evitar conflitos, o acesso ao buffer deve ser protegido por um mutex.

O mutex associado ao armazenamento pode ser chamado de:

```text
dataMutex
```

Ele protege variáveis como:

```text
dataBuffer
dataCount
dataBufferFull
maxDataPoints
```

Essa proteção evita que uma tarefa leia dados enquanto outra está modificando o buffer.

---

## Separação entre armazenamento e exibição

O armazenamento dos dados é independente da exibição no LCD.

Durante a coleta, o sistema pode armazenar todos os pontos em intervalos regulares, enquanto o LCD mostra apenas algumas atualizações resumidas.

```text
Buffer de dados  → armazena todos os pontos
LCD              → exibe apenas uma visualização resumida
```

Essa separação é importante porque o LCD é mais lento do que a rotina de aquisição.

Se o display fosse atualizado a cada ponto, a regularidade da coleta poderia ser prejudicada.

---

## Preservação dos dados antes do reset

Os dados permanecem armazenados até que o buffer seja reiniciado ou uma nova coleta seja iniciada.

Antes de resetar a coleta, recomenda-se transferir os dados por Bluetooth e salvá-los em arquivo `.csv`.

!!! warning "Reset da coleta"
Ao reiniciar a coleta, os dados anteriores podem ser apagados. Transfira e salve os dados antes de executar um reset caso eles sejam necessários para análise.

---

## Resumo

O armazenamento de dados do Spring-Mass Collector é baseado em um buffer na memória RAM da ESP32.

```text
Data Storage
├── Armazena pares tempo-posição
├── Usa a estrutura DataPoint
├── Controla a quantidade de dados coletados
├── Interrompe a coleta ao atingir o limite
├── Permite recuperar dados para o LCD
├── Permite exportar dados em CSV
└── Protege o acesso com dataMutex
```

Essa estrutura permite que o sistema realize uma coleta estável, mantenha os dados organizados e transfira posteriormente a série temporal para análise externa.
