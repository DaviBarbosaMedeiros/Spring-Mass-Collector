# LCD and Buttons

A interface física do Spring-Mass Collector é formada por um display LCD 16×2 com comunicação I2C e três botões.

O display apresenta o estado do sistema, enquanto os botões permitem navegar entre os modos e executar comandos.

## Display LCD

O módulo utiliza quatro conexões:

| Terminal | Conexão                             |
| -------- | ----------------------------------- |
| `VCC`    | alimentação compatível com o módulo |
| `GND`    | `GND`                               |
| `SDA`    | `GPIO21`                            |
| `SCL`    | `GPIO22`                            |

A comunicação I²C reduz a quantidade de GPIOs necessários, utilizando uma linha de dados e uma linha de sincronização.

O display pode apresentar informações como:

* posição medida;
* quantidade de amostras;
* estado da coleta;
* limite de armazenamento;
* modo atual;
* mensagens de transferência.

Exemplo:

```text
x:   0.25 cm
N:    120 RUN
```

## Botões

Os três botões são conectados aos seguintes pinos:

| Botão | Pino     |
| ----- | -------- |
| B1    | `GPIO25` |
| B2    | `GPIO33` |
| B3    | `GPIO32` |

Cada botão é conectado entre o GPIO correspondente e o `GND`.

O firmware utiliza:

```cpp
pinMode(BUTTON_1_PIN, INPUT_PULLUP);
pinMode(BUTTON_2_PIN, INPUT_PULLUP);
pinMode(BUTTON_3_PIN, INPUT_PULLUP);
```

Portanto:

| Estado            | Leitura |
| ----------------- | ------- |
| botão solto       | `HIGH`  |
| botão pressionado | `LOW`   |

## Função dos botões

A função de cada botão depende do modo ativo.

| Modo           | B1                | B2        | B3             |
| -------------- | ----------------- | --------- | -------------- |
| Menu principal | Calibração        | Coleta    | Transferência  |
| Calibração     | Recalibrar        | Confirmar | Zerar          |
| Coleta         | Pausar ou retomar | Reiniciar | Voltar         |
| Transferência  | Enviar dados      | Voltar    | Alterar limite |

O firmware utiliza debounce para evitar que um único pressionamento seja interpretado várias vezes.

!!! note "Interface contextual"
Os botões não possuem uma função fixa. O comando executado depende do modo atualmente exibido no LCD.
