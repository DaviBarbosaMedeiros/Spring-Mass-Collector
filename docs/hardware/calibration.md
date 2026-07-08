# Calibration

A calibração do **Spring-Mass Collector** define a posição inicial de referência usada durante a coleta de dados. Essa etapa é necessária porque o sensor infravermelho mede uma distância absoluta, enquanto o experimento massa-mola exige a análise do deslocamento da massa em relação a um ponto de referência.

Nesta seção, a palavra **calibração** se refere à calibração experimental feita pelo usuário antes da coleta, e não à curva de conversão tensão-distância do sensor.

---

## Objetivo da calibração

O objetivo da calibração é definir o zero experimental do sistema.

Durante essa etapa, o usuário posiciona a massa no ponto de referência desejado e o sistema registra a distância medida pelo sensor como posição inicial:

$$
x_0
$$

A partir desse valor, todas as medidas seguintes são convertidas em posição relativa.

---

## Distância absoluta e posição relativa

O sensor infravermelho fornece uma distância absoluta entre o sensor e a massa. Essa distância pode ser representada por:

$$
x(t)
$$

Porém, em um experimento massa-mola, geralmente o interesse está no deslocamento da massa em relação a uma posição inicial de referência.

Por isso, o sistema calcula:

$$
x_{rel}(t) = x(t) - x_0
$$

onde:

| Símbolo      | Descrição                                         |
| ------------ | ------------------------------------------------- |
| $x(t)$       | distância medida pelo sensor em cada instante     |
| $x_0$        | posição inicial registrada durante a calibração   |
| $x_{rel}(t)$ | posição relativa da massa em relação à referência |

Essa transformação permite analisar o movimento da massa em torno de uma posição de equilíbrio ou de outro ponto escolhido pelo usuário.

---

## Funcionamento no firmware

No modo de calibração, o firmware lê a distância atual medida pelo sensor e armazena esse valor como posição inicial.

Conceitualmente, a lógica é:

```cpp
initialPositionCm = data.distance_cm;
```

Depois da calibração, a posição relativa é calculada a partir da diferença entre a distância atual e a posição inicial:

```cpp
latestRelativePositionCm = latestDistanceCm - initialPositionCm;
```

Essa posição relativa é o valor armazenado durante a coleta.

---

## Modo de calibração

O modo de calibração é acessado a partir do menu principal.

Uma tela típica do menu é:

```text
1-Cal 2-Col
3-Transf
```

Ao pressionar **B1**, o sistema entra no modo de calibração e registra a posição inicial da massa.

Durante esse modo, o LCD pode mostrar uma tela semelhante a:

```text
Pos Inicial:
  10.25 cm
```

Esse valor representa a distância usada como referência para o cálculo da posição relativa.

---

## Função dos botões

No modo de calibração, os três botões possuem funções específicas:

| Botão | Função                                             |
| ----- | -------------------------------------------------- |
| B1    | recalibrar a posição inicial                       |
| B2    | confirmar e voltar ao modo Default                 |
| B3    | zerar a posição inicial e permanecer na calibração |

Essa configuração permite ajustar a referência experimental sem precisar reiniciar o sistema.

---

## Recalibração

A função de recalibração permite atualizar a posição inicial sem sair do modo de calibração.

Esse recurso é útil quando:

* a massa foi posicionada incorretamente;
* o sensor foi reajustado mecanicamente;
* a leitura inicial não ficou estável;
* o usuário deseja redefinir o ponto de referência.

Ao pressionar **B1**, o sistema realiza uma nova leitura do sensor e substitui o valor anterior de (x_0).

---

## Zerar posição inicial

O botão **B3** permite zerar a posição inicial e permanecer na tela de calibração.

Esse comportamento é útil porque o usuário pode limpar a referência anterior e realizar uma nova definição sem retornar ao menu principal.

Após zerar, o sistema permanece no modo de calibração aguardando uma nova ação do usuário.

---

## Procedimento recomendado

O procedimento recomendado para calibrar o sistema é:

```text
1. Posicionar a caixa em frente ao sistema massa-mola.
2. Ajustar a altura do sensor usando o extensor vertical.
3. Verificar o alinhamento entre sensor e massa.
4. Colocar a massa na posição de referência.
5. Acessar o modo de calibração pressionando B1.
6. Conferir a posição inicial exibida no LCD.
7. Recalibrar com B1, caso necessário.
8. Confirmar a calibração com B2.
9. Iniciar a coleta a partir do menu principal.
```

A posição de referência normalmente corresponde à posição de equilíbrio da massa, mas pode ser escolhida de acordo com o objetivo do experimento.

---

## Exemplo de cálculo

Considere que a posição inicial registrada durante a calibração seja:

$$
x_0 = 10.00 \ \text{cm}
$$

Se, durante a coleta, o sensor medir:

$$
x(t) = 11.50 \ \text{cm}
$$

então a posição relativa será:

$$
x_{rel}(t) = 11.50 - 10.00
$$

$$
x_{rel}(t) = 1.50 \ \text{cm}
$$

Se em outro instante o sensor medir:

$$
x(t) = 9.30 \ \text{cm}
$$

então:

$$
x_{rel}(t) = 9.30 - 10.00
$$

$$
x_{rel}(t) = -0.70 \ \text{cm}
$$

Assim, o sistema registra deslocamentos positivos e negativos em relação à referência definida pelo usuário.

---

## Interpretação do sinal

O sinal da posição relativa depende da posição do sensor e da direção do movimento da massa.

Se a massa se afasta do sensor em relação à posição inicial, o valor de (x_{rel}(t)) tende a aumentar. Se a massa se aproxima do sensor, o valor de (x_{rel}(t)) tende a diminuir.

A interpretação física do sinal deve considerar a montagem experimental adotada.

```text
massa se afasta do sensor      → posição relativa positiva
massa se aproxima do sensor    → posição relativa negativa
```

Essa convenção é consequência direta da definição:

$$
x_{rel}(t) = x(t) - x_0
$$

---

## Cuidados durante a calibração

A qualidade da calibração influencia diretamente todos os dados coletados depois.

Antes de confirmar a posição inicial, verifique:

* se a massa está parada;
* se o sensor está alinhado com a massa;
* se a caixa está firme;
* se o extensor do sensor está travado;
* se a distância está dentro da faixa útil do sensor;
* se não há obstáculos entre o sensor e o alvo.

!!! warning "Calibração com a massa em movimento"
A calibração deve ser feita com a massa parada na posição de referência. Se a massa estiver oscilando, o sistema pode registrar um valor incorreto para (x_0).

---

## Relação com a coleta de dados

A calibração deve ser feita antes da coleta porque o buffer de dados armazena a posição relativa da massa, e não apenas a distância absoluta medida pelo sensor.

Durante a coleta, cada ponto armazenado possui a forma:

```text
t_ms,pos_cm
```

onde `pos_cm` corresponde a:

$$
x_{rel}(t)
$$

Portanto, uma calibração incorreta desloca toda a série temporal coletada.

---

## Quando recalibrar

A recalibração é recomendada sempre que houver mudança na montagem experimental.

Algumas situações comuns são:

| Situação                  | Motivo para recalibrar                |
| ------------------------- | ------------------------------------- |
| caixa reposicionada       | muda a distância entre sensor e massa |
| altura do sensor alterada | pode mudar o alinhamento de leitura   |
| massa trocada             | pode alterar a superfície detectada   |
| mola reposicionada        | pode mudar a posição de equilíbrio    |
| leitura inicial instável  | pode gerar erro no zero experimental  |
| novo experimento iniciado | garante uma referência atualizada     |

Em atividades didáticas, recomenda-se recalibrar antes de cada nova coleta experimental.

---

## Diferença entre calibração do sensor e calibração inicial

No projeto existem duas etapas diferentes de calibração:

| Calibração           | Função                                    |
| -------------------- | ----------------------------------------- |
| Calibração do sensor | define a relação entre tensão e distância |
| Calibração inicial   | define o zero experimental (x_0)          |

A calibração do sensor está associada à equação:

$$
d = 10.1727 \cdot V^{-0.9965}
$$

Ela transforma a tensão analógica em distância.

A calibração inicial está associada à equação:

$$
x_{rel}(t) = x(t) - x_0
$$

Ela transforma a distância medida em deslocamento relativo.

---

## Resumo

A calibração inicial define a referência usada para interpretar os dados do experimento massa-mola.

O processo pode ser resumido como:

```text
Usuário posiciona a massa na referência
        ↓
Sensor mede a distância atual
        ↓
Sistema registra essa distância como x₀
        ↓
Coleta usa x₀ para calcular a posição relativa
        ↓
Dados são armazenados como tempo e posição
```

Com essa etapa, o Spring-Mass Collector transforma uma medida absoluta de distância em um dado físico mais adequado para o estudo de oscilações amortecidas.
