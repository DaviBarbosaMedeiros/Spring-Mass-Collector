# Distance Sensor

O Spring-Mass Collector utiliza o sensor infravermelho analógico **Sharp GP2Y0A41SK0F** para medir a distância entre a caixa e o disco refletor.

O sensor apresenta uma faixa nominal aproximada de 4 cm a 30 cm.

## Conexões

| Terminal | Conexão  |
| -------- | -------- |
| `VCC`    | `VIN/5V` |
| `GND`    | `GND`    |
| `VOUT`   | `GPIO39` |

O terminal `VOUT` fornece uma tensão analógica que varia de forma não linear com a distância.

## Conversão para distância

Após a leitura do ADC, a tensão é convertida em distância por meio da curva de calibração experimental:

$$
d=
10.1727
V^{-0.9965}
$$

onde:

| Grandeza | Descrição                 | Unidade       |
| -------- | ------------------------- | ------------- |
| $d$      | distância calculada       | $\mathrm{cm}$ |
| $V$      | tensão de saída do sensor | $\mathrm{V}$  |

No firmware:

```cpp
distance_cm = 10.1727 * pow(voltage, -0.9965);
```

Durante a calibração, uma distância inicial é armazenada. A posição relativa é então calculada por:

$$
x_{\mathrm{rel}}(t)=
x_{\mathrm{med}}(t)-x_0
$$

## Condições de medição

Para obter leituras mais estáveis:

* mantenha o disco refletor centralizado;
* evite inclinações do disco;
* mantenha a distância dentro da faixa útil;
* reduza movimentos laterais;
* mantenha o sensor firmemente fixado.

!!! warning "Resposta não linear"
A tensão não deve ser convertida em distância por uma relação linear. A curva de calibração deve ser utilizada em todas as leituras.