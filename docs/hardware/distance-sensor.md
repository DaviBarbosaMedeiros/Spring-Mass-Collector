# Distance Sensor

O **Spring-Mass Collector** utiliza um sensor infravermelho de distância para medir a posição da massa durante o experimento massa-mola. Essa leitura é a base do processo de aquisição de dados, pois permite transformar o movimento da massa em uma série temporal de posição.

Nesta seção são descritos o modelo do sensor, sua função no sistema, a leitura analógica pela ESP32 e a curva experimental usada para converter tensão em distância.

---

## Função do sensor no sistema

O sensor infravermelho mede a distância entre a caixa coletora e a massa oscilante.

Durante o experimento, essa distância é lida continuamente pela ESP32. A partir dessa medida, o firmware calcula a posição da massa e armazena os dados ao longo do tempo.

O fluxo básico de leitura é:

```text
Massa oscilante
        ↓
Sensor infravermelho mede a distância
        ↓
Sensor fornece uma tensão analógica
        ↓
ESP32 lê a tensão pelo ADC
        ↓
Firmware converte tensão em distância
```

A leitura fornecida pelo sensor representa uma **distância absoluta** entre o sensor e o alvo. A conversão dessa distância em deslocamento relativo será tratada na seção de calibração.

---

## Modelo utilizado

O sensor utilizado no projeto é o **GP2Y0A41SK0F**, um sensor infravermelho analógico de curta distância.

Esse sensor foi escolhido por combinar:

* baixo custo;
* saída analógica simples;
* fácil integração com a ESP32;
* dimensões compactas;
* uso adequado em medições de curta distância.

---

## Princípio de leitura

O sensor infravermelho emite luz infravermelha e detecta a reflexão proveniente do alvo. A eletrônica interna do sensor transforma essa resposta em uma tensão analógica relacionada à distância.

A relação entre tensão e distância não é linear. Em geral, objetos mais próximos produzem tensões maiores, enquanto objetos mais distantes produzem tensões menores.

```text
Objeto mais próximo  → tensão maior
Objeto mais distante → tensão menor
```

Por esse motivo, é necessário utilizar uma curva de calibração para converter a tensão medida em distância.

---

## Conexão com a ESP32

A saída analógica do sensor é conectada a uma entrada ADC da ESP32.

No firmware atual, o pino utilizado para a leitura do sensor é:

```cpp
const uint8_t SENSOR_PIN = 39;
```

A leitura é feita pelo conversor analógico-digital da ESP32. A resolução configurada é de 12 bits:

```cpp
analogReadResolution(12);
```

Com essa configuração, a leitura bruta do ADC varia aproximadamente entre:

```text
0 e 4095
```

---

## Conversão de ADC para tensão

O valor bruto lido pelo ADC é convertido para tensão usando a relação:

$$
V = \frac{ADC}{4095} \cdot V_{ref}
$$

onde:

| Símbolo   | Descrição                                |
| --------- | ---------------------------------------- |
| (V)       | tensão estimada na entrada analógica     |
| (ADC)     | valor bruto lido pela ESP32              |
| (V_{ref}) | tensão de referência adotada             |
| (4095)    | valor máximo para uma leitura de 12 bits |

No firmware, essa conversão pode ser representada por:

```cpp
voltage = adcMean * ADC_REF_VOLTAGE / ADC_MAX_VALUE;
```

com:

```cpp
ADC_REF_VOLTAGE = 3.3;
ADC_MAX_VALUE   = 4095.0;
```

!!! warning "Limite da entrada analógica"
A entrada analógica da ESP32 não deve receber tensão acima do limite permitido pelo microcontrolador. Antes de conectar o sensor, verifique se a tensão máxima de saída é compatível com a entrada ADC utilizada.

---

## Conversão de tensão para distância

Como a resposta do sensor não é linear, a distância é calculada a partir de uma curva experimental.

A função usada para representar a relação entre tensão e distância foi do tipo potência:

$$
d = A V^B
$$

onde:

| Símbolo | Descrição                        |
| ------- | -------------------------------- |
| (d)     | distância em centímetros         |
| (V)     | tensão medida na saída do sensor |
| (A)     | coeficiente de escala            |
| (B)     | expoente do ajuste               |

Para os dados experimentais utilizados, os coeficientes obtidos foram aproximadamente:

$$
A = 10.1727
$$

$$
B = -0.9965
$$

Assim, a equação de conversão adotada é:

$$
d = 10.1727 \cdot V^{-0.9965}
$$

No firmware, essa relação pode ser implementada como:

```cpp
distance_cm = 10.1727 * pow(voltage, -0.9965);
```

---

## Dados experimentais de calibração do sensor

A curva de conversão foi obtida a partir de pares experimentais de tensão e distância.

| Tensão (V) | Distância (cm) |
| ---------: | -------------: |
|       0.70 |             14 |
|       0.77 |             13 |
|       0.85 |             12 |
|       0.93 |             11 |
|       1.03 |             10 |
|       1.16 |              9 |
|       1.29 |              8 |
|       1.49 |              7 |
|       1.73 |              6 |
|       2.01 |              5 |
|       2.46 |              4 |

Esses dados foram usados para ajustar a função:

$$
d = A V^B
$$

O objetivo desse ajuste é permitir que o firmware converta automaticamente a tensão medida pelo sensor em uma estimativa de distância em centímetros.

---

## Interpretação da curva

A equação ajustada mostra que a distância diminui quando a tensão aumenta. Isso é coerente com o comportamento esperado do sensor infravermelho.

A forma aproximada da equação,

$$
d = 10.1727 \cdot V^{-0.9965}
$$

indica uma relação próxima de uma dependência inversa entre distância e tensão.

Como a curva é não linear, a sensibilidade do sensor não é uniforme em toda a faixa de medição. Pequenas variações de tensão podem representar variações diferentes de distância dependendo da região de operação.

Por isso, é importante manter o experimento dentro de uma faixa em que:

* a resposta do sensor seja estável;
* a massa permaneça dentro da região útil de leitura;
* a oscilação não leve o alvo para fora da faixa calibrada;
* o ruído não seja dominante em relação à variação medida.

---

## Filtragem da leitura

A leitura analógica pode apresentar ruídos causados por variações elétricas, instabilidade da alimentação, reflexões do alvo ou pequenas vibrações mecânicas.

Para reduzir esse efeito, o firmware pode realizar múltiplas leituras antes de calcular a distância final.

O procedimento geral é:

```text
Realizar várias leituras ADC
        ↓
Calcular uma média representativa
        ↓
Converter ADC médio em tensão
        ↓
Converter tensão em distância
```

Essa filtragem melhora a estabilidade da medida e reduz oscilações rápidas que não representam necessariamente o movimento real da massa.

---

## Posicionamento do sensor

O sensor deve ser alinhado com a trajetória da massa oscilante. Um alinhamento inadequado pode gerar leituras instáveis ou representar uma distância diferente daquela que se deseja medir.

A estrutura 3D do Spring-Mass Collector possui um extensor vertical para o sensor, permitindo ajustar sua altura em até três níveis. Esse recurso facilita o alinhamento entre o sensor e a massa.

Durante a montagem experimental, recomenda-se verificar:

* se o sensor está apontado diretamente para a massa;
* se a massa permanece dentro da faixa de leitura durante toda a oscilação;
* se não há obstáculos entre o sensor e o alvo;
* se a superfície detectada reflete adequadamente o infravermelho;
* se a caixa está firme e não se move durante a coleta;
* se a trava mecânica do extensor está corretamente encaixada.

!!! note "Ajuste mecânico"
O extensor vertical permite adaptar a altura do sensor à configuração do experimento. Para destravar o mecanismo, as laterais devem ser pressionadas simultaneamente; ao soltar, o extensor volta a ser fixado na posição escolhida.

---

## Limitações experimentais

Alguns fatores podem afetar a qualidade da medição:

| Fator                             | Possível efeito               |
| --------------------------------- | ----------------------------- |
| Alvo desalinhado                  | leitura instável ou incorreta |
| Superfície muito reflexiva        | variações bruscas na leitura  |
| Superfície escura ou irregular    | redução da resposta do sensor |
| Vibração da caixa                 | ruído adicional na medida     |
| Distância fora da faixa calibrada | perda de confiabilidade       |
| Alimentação instável              | variação na tensão lida       |

Essas limitações devem ser consideradas durante a montagem do experimento e na interpretação dos dados coletados.

---

## Saída do módulo de medição

Após a leitura e conversão, o módulo do sensor fornece a distância estimada em centímetros.

De forma conceitual, a saída pode ser representada como:

```text
distance_cm
```

Esse valor ainda representa a distância absoluta entre o sensor e a massa. Na etapa seguinte, o sistema utiliza a posição inicial definida pelo usuário para calcular o deslocamento relativo:

$$
x_{rel}(t) = x(t) - x_0
$$

Esse cálculo será descrito na seção de calibração.

---

## Resumo

O sensor infravermelho é o elemento responsável por transformar o movimento da massa em um sinal elétrico mensurável pela ESP32.

O processo completo de medição é:

```text
Distância física
        ↓
Tensão analógica do sensor
        ↓
Leitura ADC da ESP32
        ↓
Conversão ADC → tensão
        ↓
Conversão tensão → distância
```

Com a curva experimental,

$$
d = 10.1727 \cdot V^{-0.9965}
$$

o firmware consegue estimar a distância da massa em centímetros e fornecer esse valor para as etapas de calibração, coleta e armazenamento dos dados.
