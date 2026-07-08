# LCD and Buttons

A interface local do **Spring-Mass Collector** é formada por um display **LCD 16x2 I2C** e três botões físicos. Esses elementos permitem que o usuário controle o sistema sem depender de computador durante a execução do experimento.

O LCD apresenta menus, estados e informações resumidas da coleta, enquanto os botões permitem navegar entre os modos de operação, calibrar a posição inicial, iniciar ou interromper a coleta e transferir os dados.

---

## Função da interface local

A interface local foi projetada para tornar o uso do equipamento simples durante atividades experimentais.

Ela permite que o usuário:

* visualize o modo atual do sistema;
* calibre a posição inicial da massa;
* acompanhe a posição relativa durante a coleta;
* veja a quantidade de dados armazenados;
* identifique quando a memória está cheia;
* acesse o modo de transferência;
* envie os dados por Bluetooth;
* altere o limite máximo de dados coletados.

O fluxo básico de interação é:

```text
Usuário pressiona um botão
        ↓
Firmware interpreta o comando
        ↓
Modo de operação é atualizado
        ↓
LCD mostra o novo estado do sistema
```

---

## Display LCD 16x2 I2C

O display utilizado é um **LCD 16x2 com interface I2C**.

A notação 16x2 indica que o display possui:

```text
16 colunas
2 linhas
```

Isso significa que a quantidade de informação exibida ao mesmo tempo é limitada. Por isso, as mensagens do sistema devem ser curtas, diretas e organizadas.

A interface I2C reduz a quantidade de conexões necessárias entre o display e a ESP32, facilitando a montagem interna da caixa.

---

## Função do LCD no sistema

O LCD não é usado para exibir todos os dados coletados. Sua função é apresentar apenas informações essenciais para orientar o usuário durante o experimento.

Ele pode mostrar:

| Informação             | Exemplo          |
| ---------------------- | ---------------- |
| menu principal         | `1-Cal 2-Col`    |
| modo atual             | `Modo Transfer`  |
| posição inicial        | `Pos Inicial:`   |
| posição relativa       | `x: 0.25 cm`     |
| número de pontos       | `N: 120`         |
| estado da coleta       | `RUN` ou `PAUSE` |
| limite de dados        | `M:5000`         |
| aviso de memória cheia | `MEMORIA CHEIA`  |
| status de envio        | `Transferindo`   |

Essa escolha mantém a interface simples e evita excesso de informação na tela.

---

## Telas principais

O sistema utiliza diferentes telas de acordo com o modo de operação.

### Menu principal

```text
1-Cal 2-Col
3-Transf
```

Essa tela aparece no modo **Default** e permite acessar as três funções principais do sistema.

---

### Modo de calibração

```text
Pos Inicial:
  10.25 cm
```

Essa tela mostra a posição inicial registrada durante a calibração.

---

### Modo de coleta

```text
x:   0.25 cm
N:    120 RUN
```

Essa tela mostra a posição relativa atual, a quantidade de pontos armazenados e o estado da coleta.

---

### Modo de transferência

```text
Modo Transfer
D: 120 M:5000
```

Essa tela mostra a quantidade de dados armazenados e o limite máximo configurado.

---

### Transferência em andamento

```text
Transferindo
Aguarde...
```

Essa tela informa que o sistema está enviando os dados por Bluetooth e Serial.

---

### Memória cheia

```text
MEMORIA CHEIA
```

Essa tela aparece quando o número máximo de pontos configurado é atingido.

---

## Atualização do LCD

O LCD é mais lento do que a rotina de aquisição de dados. Por isso, ele não deve ser atualizado na mesma frequência em que o sensor é lido.

Durante a coleta, o sistema pode armazenar dados em intervalos curtos, enquanto o LCD é atualizado com menor frequência.

Exemplo:

```text
Sensor armazena dados a cada 25 ms
LCD atualiza a cada 100 ms
```

Essa separação evita que a escrita no LCD prejudique a regularidade da coleta.

!!! note "Exibição e armazenamento"
O LCD mostra apenas uma parte resumida das informações. Todos os pontos coletados continuam sendo armazenados internamente, mesmo que não sejam exibidos na tela.

---

## Botões físicos

O Spring-Mass Collector utiliza três botões físicos para controlar todos os modos de operação.

No firmware atual, os pinos associados aos botões são:

```cpp
const uint8_t buttonPins[BUTTON_QTD] = {
  25,
  33,
  32
};
```

A ligação considerada para cada botão é:

```text
GPIO ---- botão ---- GND
```

Com essa configuração, os pinos são configurados como entrada com resistor interno de pull-up:

```cpp
INPUT_PULLUP
```

Assim, o comportamento lógico é:

| Estado do botão | Leitura na ESP32 |
| --------------- | ---------------- |
| solto           | HIGH             |
| pressionado     | LOW              |

---

## Debounce dos botões

Botões mecânicos podem gerar oscilações rápidas no sinal elétrico durante um único pressionamento. Esse efeito é chamado de **bounce**.

Sem tratamento adequado, um único clique poderia ser interpretado como vários comandos.

Para evitar esse problema, o firmware utiliza debounce por tempo. O intervalo adotado é:

```cpp
BUTTON_DEBOUNCE_MS = 50;
```

Isso significa que o sistema aguarda um pequeno intervalo antes de aceitar uma nova mudança de estado do botão.

O fluxo de leitura pode ser representado como:

```text
Botão pressionado
        ↓
Firmware detecta mudança
        ↓
Espera intervalo de debounce
        ↓
Confirma se o estado permanece válido
        ↓
Gera evento de botão
```

---

## Interpretação dos botões

Os botões não possuem uma função fixa em todo o sistema. A função de cada botão depende do modo atual.

Isso permite controlar várias ações usando apenas três botões.

| Modo          | B1             | B2                | B3                      |
| ------------- | -------------- | ----------------- | ----------------------- |
| Default       | Calibração     | Coleta            | Transferência           |
| Calibração    | Recalibrar     | Confirmar         | Zerar posição inicial   |
| Coleta        | Pausar/retomar | Resetar coleta    | Voltar ao Default       |
| Transferência | Enviar dados   | Voltar ao Default | Alterar limite de dados |

Essa organização reduz a quantidade de componentes físicos e mantém a operação simples.

---

## Botões no modo Default

No modo **Default**, os botões funcionam como seleção de menu.

```text
1-Cal 2-Col
3-Transf
```

| Botão | Ação                           |
| ----- | ------------------------------ |
| B1    | entra no modo de calibração    |
| B2    | entra no modo de coleta        |
| B3    | entra no modo de transferência |

Esse é o ponto inicial de navegação do sistema.

---

## Botões no modo de calibração

No modo de **Calibração**, os botões são usados para definir ou ajustar a posição inicial.

| Botão | Ação                                             |
| ----- | ------------------------------------------------ |
| B1    | realiza nova calibração                          |
| B2    | confirma a calibração e retorna ao modo Default  |
| B3    | zera a posição inicial e permanece na calibração |

Esse comportamento permite corrigir a referência experimental antes de iniciar a coleta.

---

## Botões no modo de coleta

No modo de **Coleta**, os botões controlam a aquisição dos dados.

| Botão | Ação                                      |
| ----- | ----------------------------------------- |
| B1    | pausa ou retoma a coleta                  |
| B2    | apaga os dados atuais e reinicia a coleta |
| B3    | volta ao modo Default                     |

A função de pausa permite interromper temporariamente o armazenamento sem apagar os dados já coletados.

A função de reset reinicia a aquisição a partir de um novo tempo inicial.

!!! warning "Reset da coleta"
Ao pressionar B2 no modo de coleta, os dados armazenados anteriormente são apagados. Transfira os dados antes de reiniciar caso queira preservá-los.

---

## Botões no modo de transferência

No modo de **Transferência**, os botões controlam o envio e a configuração do limite de dados.

| Botão | Ação                                  |
| ----- | ------------------------------------- |
| B1    | envia os dados por Bluetooth e Serial |
| B2    | retorna ao modo Default               |
| B3    | altera a quantidade máxima de dados   |

O botão B3 permite alternar entre diferentes limites de coleta, por exemplo:

```text
500 → 1000 → 2000 → 3000 → 5000 → 500
```

Esse recurso permite ajustar a duração da aquisição conforme a necessidade do experimento.

---

## Organização da interface na caixa

A estrutura 3D do Spring-Mass Collector foi projetada para acomodar a interface local de forma prática.

O display LCD 16x2 fica em uma região inclinada de aproximadamente **30 graus**, melhorando a visualização durante o uso.

Os botões ficam posicionados na parte frontal da caixa, permitindo acesso direto às funções principais sem interferir na montagem experimental.

Essa disposição facilita:

* leitura do LCD;
* navegação pelos menus;
* operação durante a coleta;
* uso em bancada didática;
* acesso rápido aos comandos principais.

---

## Relação entre interface e firmware

A interface física depende diretamente da máquina de estados implementada no firmware.

O LCD mostra o estado atual do sistema, enquanto os botões geram eventos interpretados de acordo com esse estado.

```text
Botões
  ↓
Eventos de entrada
  ↓
Máquina de estados
  ↓
Atualização das variáveis internas
  ↓
Atualização do LCD
```

Essa separação é importante porque o botão apenas informa que foi pressionado. Quem define o significado do botão é o modo atual.

Por exemplo:

```text
B1 no modo Default       → entrar em calibração
B1 no modo Calibração   → recalibrar
B1 no modo Coleta       → pausar ou retomar
B1 no modo Transferência→ enviar dados
```

---

## Cuidados de uso

Durante a operação, recomenda-se:

* pressionar os botões com firmeza, mas sem força excessiva;
* aguardar a atualização da tela após cada comando;
* verificar se o LCD mostra o modo esperado;
* evitar pressionar vários botões ao mesmo tempo;
* não reiniciar a coleta antes de transferir dados importantes;
* confirmar a calibração antes de iniciar a aquisição.

Esses cuidados ajudam a evitar erros de operação durante o experimento.

---

## Resumo

A interface local do Spring-Mass Collector é composta por:

```text
Interface local
├── LCD 16x2 I2C
│   ├── mostra menus
│   ├── informa estado da coleta
│   ├── exibe quantidade de dados
│   └── indica transferência ou memória cheia
│
└── Três botões físicos
    ├── navegam entre modos
    ├── controlam calibração
    ├── controlam coleta
    └── iniciam transferência
```

Essa interface permite controlar todo o sistema de forma simples, sem depender de computador durante a realização do experimento.
