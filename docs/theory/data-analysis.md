# Data Analysis

A análise dos dados transforma as medições de tempo e posição registradas pelo Spring-Mass Collector em informações físicas sobre o movimento do sistema massa-mola.

A partir dos dados experimentais, podem ser determinados:

* posição de equilíbrio;
* amplitude;
* período;
* frequência;
* frequência angular;
* taxa de amortecimento;
* constante de tempo;
* coeficiente de amortecimento;
* constante elástica;
* velocidade;
* aceleração;
* erros experimentais;
* diferenças entre os modelos teóricos e o comportamento real.

O procedimento de análise deve preservar os dados originais, identificar possíveis problemas de medição e utilizar métodos compatíveis com a precisão do equipamento.

---

## Estrutura dos dados

O Spring-Mass Collector armazena pares formados pelo tempo de aquisição e pela posição relativa da massa.

Os dados são transmitidos no seguinte formato:

```text
t_ms,pos_cm
0,0.0152
25,0.2841
50,0.5318
75,0.7463
100,0.9127
END
```

As colunas representam:

| Coluna   | Descrição                                   | Unidade       |
| -------- | ------------------------------------------- | ------------- |
| `t_ms`   | tempo transcorrido desde o início da coleta | $\mathrm{ms}$ |
| `pos_cm` | posição relativa ao ponto de calibração     | $\mathrm{cm}$ |

A linha `END` indica o final da transmissão e não representa uma medição. Ela deve ser removida antes dos cálculos.

Mais detalhes sobre o formato podem ser encontrados em [Data Storage](../software/data-storage.md) e [Bluetooth Transfer](../software/bluetooth-transfer.md).

---

## Preservação dos dados originais

Antes de iniciar o tratamento, recomenda-se manter uma cópia do arquivo exatamente como foi recebido.

A análise deve ser realizada em uma segunda cópia do arquivo ou em uma nova planilha.

!!! warning "Dados brutos"
Os dados originais não devem ser sobrescritos. Caso uma filtragem, correção ou exclusão seja aplicada, o procedimento utilizado deve ser registrado para que a análise possa ser reproduzida.

Uma organização recomendada é:

```text
experimento_01_bruto.csv
experimento_01_tratado.xlsx
experimento_01_resultados.pdf
```

Também é importante registrar:

* massa utilizada;
* mola utilizada;
* data do experimento;
* intervalo de amostragem;
* posição inicial;
* quantidade máxima de pontos;
* observações sobre o movimento;
* possíveis oscilações laterais;
* alterações realizadas durante o tratamento.

---

## Importação dos dados no Excel

O Excel é uma alternativa acessível para visualizar e tratar os dados coletados.

É preferível importar o arquivo por meio da ferramenta de importação de texto ou CSV, em vez de simplesmente abrir o arquivo com um clique duplo.

Durante a importação, devem ser verificadas as seguintes configurações:

* separador de colunas: vírgula;
* primeira linha utilizada como cabeçalho;
* coluna `t_ms` interpretada como número inteiro;
* coluna `pos_cm` interpretada como número decimal;
* linha `END` removida;
* codificação do texto reconhecida corretamente.

### Separador decimal

O firmware utiliza ponto como separador decimal:

```text
0.0152
```

Em sistemas configurados para o padrão brasileiro, o Excel pode esperar uma vírgula decimal:

```text
0,0152
```

Nesse caso, a coluna de posição pode ser interpretada como texto.

Esse problema pode ser resolvido durante a importação, selecionando uma configuração regional que reconheça o ponto decimal, ou posteriormente convertendo a coluna para valores numéricos.

!!! note "Verificação da importação"
Após importar o arquivo, confirme que o Excel consegue realizar operações matemáticas com os valores da coluna `pos_cm`. Caso os dados ainda sejam tratados como texto, a conversão não foi realizada corretamente.

---

## Organização inicial da planilha

Uma organização simples pode ser feita com as seguintes colunas:

| Coluna | Conteúdo                      |
| ------ | ----------------------------- |
| A      | tempo em milissegundos        |
| B      | posição em centímetros        |
| C      | tempo em segundos             |
| D      | posição corrigida             |
| E      | amplitude dos picos           |
| F      | posição calculada pelo modelo |
| G      | resíduos                      |

Exemplo:

| $t_{\mathrm{ms}}$ | $x_{\mathrm{cm}}$ | $t_{\mathrm{s}}$ | $x_{\mathrm{corr}}$ |
| ----------------: | ----------------: | ---------------: | ------------------: |
|               $0$ |          $0.0152$ |          $0.000$ |            $0.0152$ |
|              $25$ |          $0.2841$ |          $0.025$ |            $0.2841$ |
|              $50$ |          $0.5318$ |          $0.050$ |            $0.5318$ |
|              $75$ |          $0.7463$ |          $0.075$ |            $0.7463$ |

---

## Conversão do tempo

Os dados são registrados em milissegundos. Para a análise física, é conveniente converter o tempo para segundos.

Se o primeiro valor estiver na célula `A2`, utilize:

```excel
=(A2-$A$2)/1000
```

Matematicamente:

$$
t_i=
\frac{
t_{\mathrm{ms},i}-t_{\mathrm{ms},0}
}{
1000
}
$$

onde:

* `t_i` é o tempo em segundos;
* `t_ms,i` é o tempo registrado na linha analisada;
* `t_ms,0` é o primeiro valor de tempo.

A subtração do primeiro valor redefine o instante inicial como zero.

---

## Conversão da posição

O firmware registra a posição em centímetros.

Para converter a posição para metros:

$$
x_{\mathrm{m}}=
\frac{x_{\mathrm{cm}}}{100}
$$

No Excel, considerando a posição em `B2`:

```excel
=B2/100
```

A utilização de metros é recomendada quando os resultados forem empregados em equações do Sistema Internacional.

Gráficos destinados apenas à visualização podem continuar utilizando centímetros, desde que a unidade seja indicada no eixo.

---

## Posição relativa e posição de equilíbrio

O Spring-Mass Collector calcula a posição relativa por:

$$
x_{\mathrm{rel}}(t)=
x_{\mathrm{med}}(t)-x_0
$$

O termo `x_0` corresponde à posição registrada durante a calibração.

Quando a calibração é realizada com a massa em equilíbrio, espera-se que a posição relativa igual a zero corresponda aproximadamente à posição de equilíbrio.

Na prática, pode existir um pequeno deslocamento residual causado por:

* movimento da massa durante a calibração;
* ruído do sensor;
* alteração da posição da estrutura;
* desalinhamento do disco refletor;
* variações na leitura inicial;
* deformações do suporte.

Nesse caso, pode-se definir uma posição de equilíbrio experimental `x_c` e corrigir os dados:

$$
x_{\mathrm{corr}}(t)=
x_{\mathrm{rel}}(t)-x_c
$$

No Excel, se `x_c` estiver armazenado em `H2`:

```excel
=B2-$H$2
```

A posição de equilíbrio pode ser estimada por:

* média dos dados após o movimento praticamente cessar;
* média entre máximos positivos e negativos;
* ajuste do modelo amortecido com deslocamento constante;
* média de vários ciclos completos.

---

## Sinal da posição

Dependendo da orientação do sensor, o aumento da distância medida pode corresponder a um deslocamento positivo ou negativo em relação ao eixo adotado.

A inversão do sinal pode ser realizada por:

$$
x_{\mathrm{novo}}(t)=
-x_{\mathrm{medido}}(t)
$$

No Excel:

```excel
=-B2
```

A inversão do sinal não altera:

* período;
* frequência;
* módulo da amplitude;
* taxa de amortecimento;
* constante de tempo.

Ela altera apenas a orientação do eixo e a fase da oscilação.

---

## Gráfico de posição em função do tempo

O primeiro gráfico deve representar a posição em função do tempo:

$$
x=x(t)
$$

No Excel, recomenda-se utilizar um gráfico de dispersão.

O eixo horizontal deve representar o tempo e o eixo vertical deve representar a posição.

```text
Eixo horizontal: Tempo, t (s)
Eixo vertical: Posição relativa, x (cm)
```

O gráfico permite observar:

* presença de oscilações;
* redução da amplitude;
* deslocamento da posição de equilíbrio;
* irregularidades na medição;
* pontos discrepantes;
* início e término do movimento;
* oscilações laterais;
* perda de leitura do sensor.

!!! tip "Tipo de gráfico"
O gráfico de dispersão é mais adequado do que o gráfico de linhas baseado em categorias, pois trata os valores de tempo como coordenadas numéricas reais.

---

## Intervalo de amostragem

O intervalo entre duas amostras consecutivas é:

$$
\Delta t_i=
t_{i+1}-t_i
$$

No Excel, considerando os tempos em segundos nas células `C2` e `C3`:

```excel
=C3-C2
```

Quando o intervalo é aproximadamente constante, pode-se utilizar o valor médio:

$$
\overline{\Delta t}=
\frac{1}{N-1}
\sum_{i=1}^{N-1}
\Delta t_i
$$

A frequência de amostragem é:

$$
f_s=
\frac{1}{\overline{\Delta t}}
$$

Para um intervalo de 25 ms:

$$
\Delta t=
0.025\ \mathrm{s}
$$

Logo:

$$
f_s=\frac{1}{0.025}=40 \mathrm{Hz}
$$

Isso significa que são registradas aproximadamente 40 amostras por segundo.

---

## Frequência de Nyquist

A frequência de Nyquist é dada por:

$$
f_N=
\frac{f_s}{2}
$$

Para uma frequência de amostragem de 40 Hz:

$$
f_N=
20\ \mathrm{Hz}
$$

O movimento massa-mola deve possuir frequência significativamente menor que esse limite para ser representado adequadamente.

!!! warning "Aliasing"
Quando a frequência do movimento se aproxima ou ultrapassa metade da frequência de amostragem, o sinal registrado pode apresentar uma frequência aparente diferente da real. Esse fenômeno é denominado aliasing.

Mesmo quando o intervalo de amostragem é configurado como constante, devem ser utilizados os valores de tempo realmente armazenados.

---

## Identificação da amplitude

A amplitude corresponde à distância máxima entre a posição de equilíbrio e um extremo da oscilação.

Para um sinal centrado em zero:

$$
A_n=
\left\lvert x_n\right\rvert
$$

Caso a posição de equilíbrio seja `x_c`:

$$
A_n=
\left\lvert x_n-x_c\right\rvert
$$

Para determinar as amplitudes:

1. construa o gráfico de posição em função do tempo;
2. identifique máximos de mesmo sentido;
3. registre o tempo e a posição de cada máximo;
4. subtraia a posição de equilíbrio;
5. utilize o módulo do resultado.

Uma tabela auxiliar pode ser organizada assim:

| Pico | Tempo | Posição |              Amplitude |
| ---: | ----: | ------: | ---------------------: |
|  $1$ | $t_1$ |   $x_1$ | $\lvert x_1-x_c\rvert$ |
|  $2$ | $t_2$ |   $x_2$ | $\lvert x_2-x_c\rvert$ |
|  $3$ | $t_3$ |   $x_3$ | $\lvert x_3-x_c\rvert$ |

É importante utilizar máximos de mesmo sentido. Um máximo positivo e o mínimo negativo seguinte estão separados por aproximadamente meio período.

---

## Determinação do período

O período amortecido pode ser determinado pela diferença entre os tempos de dois máximos consecutivos de mesmo sentido:

$$
T_{d,n}=
t_{n+1}-t_n
$$

Como os dados experimentais apresentam ruído, é preferível utilizar vários ciclos:

$$
T_d=
\frac{
t_{n+N}-t_n
}{
N
}
$$

Por exemplo, se o primeiro pico está em `D2` e o quinto em `D6`, existem quatro períodos entre eles:

```excel
=(D6-D2)/4
```

Também pode ser calculada a média dos períodos individuais:

$$
\overline{T_d}=
\frac{1}{N}
\sum_{n=1}^{N}
T_{d,n}
$$

O uso de vários ciclos reduz a influência da incerteza na identificação dos picos.

---

## Frequência e frequência angular

Depois de determinar o período:

$$
f_d=
\frac{1}{T_d}
$$

A frequência angular é:

$$
\omega_d=
2\pi f_d
$$

Também pode ser calculada diretamente por:

$$
\omega_d=
\frac{2\pi}{T_d}
$$

No Excel, se o período estiver em `H3`, a frequência é:

```excel
=1/H3
```

A frequência angular é:

```excel
=2*PI()/H3
```

| Grandeza              | Símbolo    | Unidade               |
| --------------------- | ---------- | --------------------- |
| Período amortecido    | $T_d$      | $\mathrm{s}$          |
| Frequência amortecida | $f_d$      | $\mathrm{Hz}$         |
| Frequência angular    | $\omega_d$ | $\mathrm{rad,s^{-1}}$ |

---

## Determinação da constante elástica

Se o amortecimento for fraco, a frequência amortecida pode ser aproximada pela frequência natural:

$$
\omega_d\approx\omega_0
$$

Nesse caso:

$$
k\approx
m\omega_d^2
$$

Também pode ser utilizada a relação:

$$
k\approx
\frac{
4\pi^2m
}{
T_d^2
}
$$

Quando a taxa de amortecimento é conhecida:

$$
\omega_0^2=
\omega_d^2+\gamma^2
$$

Logo:

$$
k=
m\left(
\omega_d^2+\gamma^2
\right)
$$

Quando a massa da mola não puder ser desprezada:

$$
m_{\mathrm{ef}}=
m+\frac{m_s}{3}
$$

Nesse caso:

$$
k=
m_{\mathrm{ef}}
\left(
\omega_d^2+\gamma^2
\right)
$$

---

## Análise do amortecimento pelos picos

No regime subamortecido, a amplitude diminui aproximadamente segundo:

$$
A(t)=
A_0e^{-\gamma t}
$$

Considere dois picos de mesmo sentido:

$$
A_n=
A_0e^{-\gamma t_n}
$$

e:

$$
A_{n+N}=
A_0e^{-\gamma t_{n+N}}
$$

A taxa de amortecimento pode ser determinada por:

$$
\gamma=
\frac{
\ln\left(
A_n/A_{n+N}
\right)
}{
t_{n+N}-t_n
}
$$

No Excel, se as amplitudes estiverem em `E2` e `E6`, e os tempos em `D2` e `D6`:

```excel
=LN(E2/E6)/(D6-D2)
```

As amplitudes utilizadas devem ser positivas.

---

## Decremento logarítmico

O decremento logarítmico entre picos separados por N períodos é:

$$
\delta=
\frac{1}{N}
\ln\left(
\frac{A_n}{A_{n+N}}
\right)
$$

Para picos consecutivos:

$$
\delta=
\ln\left(
\frac{A_n}{A_{n+1}}
\right)
$$

A taxa de amortecimento é:

$$
\gamma=
\frac{\delta}{T_d}
$$

A constante de tempo é:

$$
\tau=
\frac{1}{\gamma}
$$

Se a massa for conhecida:

$$
b=
2m\gamma
$$

A razão de amortecimento é:

$$
\zeta=
\frac{\gamma}{\omega_0}
$$

O fator de qualidade é:

$$
Q=
\frac{\omega_0}{2\gamma}
$$

---

## Linearização da envoltória

A equação da amplitude é:

$$
A(t)=
A_0e^{-\gamma t}
$$

Aplicando o logaritmo natural:

$$
\ln A(t)=
\ln A_0-\gamma t
$$

Essa expressão possui comportamento linear.

Um gráfico de ln A em função do tempo deve apresentar uma reta cujo coeficiente angular é igual a menos γ.

Portanto:

$$
\gamma=-a
$$

onde `a` é o coeficiente angular da reta.

### Procedimento no Excel

Crie uma tabela com:

| Tempo do pico | Amplitude | Logaritmo da amplitude |
| ------------: | --------: | ---------------------: |
|         $t_1$ |     $A_1$ |              $\ln A_1$ |
|         $t_2$ |     $A_2$ |              $\ln A_2$ |
|         $t_3$ |     $A_3$ |              $\ln A_3$ |

Se a amplitude estiver em `E2`:

```excel
=LN(ABS(E2))
```

Depois:

1. construa um gráfico de dispersão;
2. coloque o tempo no eixo horizontal;
3. coloque ln A no eixo vertical;
4. adicione uma linha de tendência linear;
5. exiba a equação da reta;
6. identifique o coeficiente angular;
7. utilize seu valor negativo como γ.

Uma reta aproximadamente linear indica que o decaimento exponencial descreve adequadamente a envoltória.

---

## Ajuste completo do movimento amortecido

O modelo mais geral para os dados é:

$$
x_{\mathrm{modelo}}(t)=
x_c+
A_0e^{-\gamma t}
\cos\left(
\omega_dt+\phi
\right)
$$

Os parâmetros são:

| Parâmetro  | Significado                                    |
| ---------- | ---------------------------------------------- |
| $x_c$      | posição de equilíbrio ou deslocamento residual |
| $A_0$      | amplitude inicial                              |
| $\gamma$   | taxa de amortecimento                          |
| $\omega_d$ | frequência angular amortecida                  |
| $\phi$     | fase inicial                                   |

O ajuste completo permite determinar esses parâmetros simultaneamente.

---

## Ajuste não linear no Excel

O suplemento Solver pode ser utilizado para minimizar a diferença entre os dados medidos e o modelo teórico.

Organize os dados da seguinte forma:

| Coluna | Conteúdo                      |
| ------ | ----------------------------- |
| A      | tempo em segundos             |
| B      | posição medida                |
| C      | posição calculada pelo modelo |
| D      | resíduo                       |
| E      | quadrado do resíduo           |

Armazene os parâmetros iniciais em células separadas:

| Célula | Parâmetro  |
| ------ | ---------- |
| H2     | $x_c$      |
| H3     | $A_0$      |
| H4     | $\gamma$   |
| H5     | $\omega_d$ |
| H6     | $\phi$     |

Na célula `C2`, utilize:

```excel
=$H$2+$H$3*EXP(-$H$4*A2)*COS($H$5*A2+$H$6)
```

O resíduo em `D2` é:

```excel
=B2-C2
```

O quadrado do resíduo em `E2` é:

```excel
=D2^2
```

Em uma célula separada, calcule a soma dos quadrados:

```excel
=SOMA(E2:E1001)
```

Dependendo do idioma do Excel:

```excel
=SUM(E2:E1001)
```

No Solver:

1. escolha a soma dos quadrados como célula objetivo;
2. selecione a opção de minimização;
3. permita que o Solver altere as células `H2:H6`;
4. imponha amplitude positiva;
5. imponha taxa de amortecimento maior ou igual a zero;
6. imponha frequência angular positiva;
7. execute a otimização.

### Valores iniciais recomendados

A posição de equilíbrio pode ser estimada pela média dos dados.

A amplitude inicial pode ser estimada pelo primeiro pico.

A taxa de amortecimento pode ser estimada por:

$$
\gamma\approx
\frac{
\ln\left(
A_1/A_N
\right)
}{
t_N-t_1
}
$$

A frequência angular pode ser estimada por:

$$
\omega_d\approx
\frac{2\pi}{T_d}
$$

A fase inicial pode começar próxima de zero.

---

## Resíduos

O resíduo associado ao ponto i é:

$$
r_i=
x_i-
x_{\mathrm{modelo}}(t_i)
$$

Um gráfico dos resíduos em função do tempo deve ser construído após o ajuste.

Um bom modelo tende a produzir resíduos:

* distribuídos em torno de zero;
* sem tendência crescente ou decrescente;
* sem oscilações sistemáticas;
* sem longas sequências positivas ou negativas;
* com amplitude compatível com a incerteza da medição.

Padrões nos resíduos podem indicar:

* frequência incorreta;
* amortecimento não exponencial;
* posição de equilíbrio mal determinada;
* movimento lateral;
* resposta não linear da mola;
* presença de mais de um modo de oscilação;
* falhas na leitura do sensor.

!!! warning "Qualidade do ajuste"
Um valor elevado do coeficiente de determinação não garante sozinho que o modelo seja adequado. A inspeção dos resíduos continua sendo necessária.

---

## Erro quadrático médio

A raiz do erro quadrático médio é:

$$
\mathrm{RMSE}=
\sqrt{
\frac{1}{N}
\sum_{i=1}^{N}
\left[
x_i-
x_{\mathrm{modelo}}(t_i)
\right]^2
}
$$

O RMSE possui a mesma unidade da posição.

Quanto menor seu valor, menor é a diferença média entre os dados e o modelo.

Esse resultado deve ser interpretado em conjunto com:

* amplitude do movimento;
* resolução do sensor;
* quantidade de dados;
* distribuição dos resíduos;
* intervalo analisado.

---

## Erro absoluto

Quando existe um valor de referência, o erro absoluto é:

$$
E_{\mathrm{abs}}=
\left\lvert
x_{\mathrm{exp}}-
x_{\mathrm{ref}}
\right\rvert
$$

Para o período:

$$
E_T=
\left\lvert
T_{\mathrm{exp}}-
T_{\mathrm{teo}}
\right\rvert
$$

O erro absoluto possui a mesma unidade da grandeza analisada.

---

## Erro relativo

O erro relativo é:

$$
E_{\mathrm{rel}}=
\frac{
\left\lvert
x_{\mathrm{exp}}-
x_{\mathrm{ref}}
\right\rvert
}{
\left\lvert
x_{\mathrm{ref}}
\right\rvert
}
$$

O erro percentual é:

$$
E_{\mathrm{percentual}}=
100
\frac{
\left\lvert
x_{\mathrm{exp}}-
x_{\mathrm{ref}}
\right\rvert
}{
\left\lvert
x_{\mathrm{ref}}
\right\rvert
}
$$

Para o período:

$$
E_{T,\mathrm{percentual}}=
100
\frac{
\left\lvert
T_{\mathrm{exp}}-
T_{\mathrm{teo}}
\right\rvert
}{
\left\lvert
T_{\mathrm{teo}}
\right\rvert
}
$$

No Excel, se o valor experimental estiver em `H2` e o valor de referência em `H3`:

```excel
=ABS(H2-H3)/ABS(H3)
```

Para obter diretamente o resultado percentual:

```excel
=100*ABS(H2-H3)/ABS(H3)
```

Também é possível utilizar a primeira expressão e formatar a célula como porcentagem.

!!! warning "Valor de referência próximo de zero"
O erro relativo não deve ser utilizado quando o valor de referência é zero ou muito próximo de zero. Nesses casos, o erro absoluto é mais informativo.

---

## Erro e incerteza

Erro e incerteza não representam a mesma ideia.

O erro corresponde à diferença entre um valor experimental e um valor de referência:

$$
E=
x_{\mathrm{exp}}-
x_{\mathrm{ref}}
$$

A incerteza representa a limitação associada ao procedimento experimental.

Uma medição pode ser apresentada como:

$$
x=
x_{\mathrm{med}}
\pm
u_x
$$

A incerteza relativa é:

$$
u_r(x)=
\frac{
u_x
}{
\left\lvert x\right\rvert
}
$$

A incerteza percentual é:

$$
u_{\mathrm{percentual}}(x)=
100
\frac{
u_x
}{
\left\lvert x\right\rvert
}
$$

!!! info "Terminologia"
O termo incerteza deve ser utilizado para descrever limitações da medição. O termo erro relativo é mais adequado quando existe um valor de referência definido.

---

## Média de medições repetidas

Se uma grandeza for medida N vezes, seu valor médio é:

$$
\overline{x}=
\frac{1}{N}
\sum_{i=1}^{N}
x_i
$$

O desvio padrão amostral é:

$$
s_x=
\sqrt{
\frac{
\sum_{i=1}^{N}
\left(
x_i-\overline{x}
\right)^2
}{
N-1
}
}
$$

A incerteza padrão da média é:

$$
u_{\overline{x}}=
\frac{s_x}{\sqrt{N}}
$$

A média reduz a influência de variações aleatórias, mas não elimina erros sistemáticos.

---

## Fontes de incerteza

As principais fontes de incerteza incluem:

* calibração do sensor infravermelho;
* resolução do conversor analógico-digital;
* ruído elétrico;
* variação da tensão de alimentação;
* posicionamento do disco refletor;
* alinhamento entre sensor e disco;
* intervalo entre amostras;
* determinação dos instantes de pico;
* medição da massa;
* determinação da constante elástica;
* movimento lateral;
* vibração da estrutura;
* massa efetiva da mola;
* resposta não linear do sensor;
* resposta não linear da mola.

### Incertezas aleatórias

Variam entre medições, como:

* ruído instantâneo;
* pequenas oscilações laterais;
* flutuações da leitura;
* variação na identificação dos picos.

### Incertezas sistemáticas

Deslocam os resultados de maneira semelhante, como:

* curva de calibração incorreta;
* massa registrada incorretamente;
* desalinhamento permanente;
* posição de referência inadequada;
* escala de tempo incorreta.

---

## Combinação de incertezas

Quando diferentes fontes independentes contribuem para uma mesma grandeza:

$$
u_c=
\sqrt{
u_1^2+
u_2^2+
u_3^2+
\cdots
}
$$

Para a posição:

$$
u_x=
\sqrt{
u_{\mathrm{sensor}}^2+
u_{\mathrm{cal}}^2+
u_{\mathrm{rep}}^2
}
$$

Essa combinação pressupõe que as contribuições sejam aproximadamente independentes.

---

## Propagação da incerteza na frequência

Como:

$$
f=
\frac{1}{T}
$$

a incerteza relativa da frequência é aproximadamente:

$$
\frac{u_f}{f}
\approx
\frac{u_T}{T}
$$

Para a frequência angular:

$$
\omega=
\frac{2\pi}{T}
$$

também se obtém:

$$
\frac{u_\omega}{\omega}
\approx
\frac{u_T}{T}
$$

---

## Propagação da incerteza na constante elástica

Para:

$$
k=
\frac{
4\pi^2m
}{
T^2
}
$$

considerando massa e período independentes:

$$
\frac{u_k}{k}=
\sqrt{
\left(
\frac{u_m}{m}
\right)^2+
\left(
2\frac{u_T}{T}
\right)^2
}
$$

Portanto:

$$
u_k=
k
\sqrt{
\left(
\frac{u_m}{m}
\right)^2+
\left(
2\frac{u_T}{T}
\right)^2
}
$$

A incerteza relativa do período possui influência ampliada devido ao fator 2.

---

## Velocidade a partir dos dados

A velocidade pode ser estimada numericamente por diferença central:

$$
v_i\approx
\frac{
x_{i+1}-x_{i-1}
}{
t_{i+1}-t_{i-1}
}
$$

No Excel, considerando o tempo na coluna `A` e a posição na coluna `B`:

```excel
=(B4-B2)/(A4-A2)
```

Se a posição estiver em metros e o tempo em segundos, a unidade será m·s⁻¹.

---

## Aceleração a partir dos dados

Quando o intervalo de amostragem é aproximadamente constante:

$$
a_i\approx
\frac{
x_{i+1}-2x_i+x_{i-1}
}{
\Delta t^2
}
$$

No Excel:

```excel
=(B4-2*B3+B2)/(($A$3-$A$2)^2)
```

A unidade será m·s⁻².

!!! warning "Amplificação do ruído"
A derivação numérica amplifica pequenas flutuações dos dados. A aceleração tende a apresentar mais ruído do que a posição.

---

## Filtragem dos dados

Filtros podem reduzir ruídos de alta frequência, mas também podem deformar o movimento medido.

Algumas alternativas são:

* média móvel;
* média móvel ponderada;
* filtro de Savitzky–Golay;
* filtro passa-baixas;
* ajuste direto do modelo físico.

Uma média móvel simples de M pontos é:

$$
x_{\mathrm{filtrado},i}=
\frac{1}{M}
\sum_{j=0}^{M-1}
x_{i-j}
$$

O uso de uma janela muito grande pode:

* reduzir a amplitude;
* deslocar os picos;
* alterar a fase;
* eliminar variações físicas reais.

!!! tip "Boa prática"
O gráfico dos dados brutos deve ser mantido junto ao gráfico filtrado. O filtro e seus parâmetros devem ser registrados.

---

## Identificação de pontos discrepantes

Um ponto discrepante pode surgir por:

* perda momentânea do alvo;
* reflexão inadequada;
* movimento lateral;
* ruído elétrico;
* leitura fora da faixa do sensor;
* falha na conversão da tensão em distância.

Antes de remover um ponto, deve-se verificar:

1. se o valor é fisicamente impossível;
2. se existe uma causa experimental identificável;
3. se o ponto está isolado;
4. se sua remoção altera significativamente os resultados;
5. se o mesmo critério pode ser aplicado a todo o conjunto.

Toda exclusão deve ser registrada.

---

## Comparação com o modelo ideal

O período teórico do sistema ideal é:

$$
T_0=
2\pi
\sqrt{
\frac{m}{k}
}
$$

A frequência teórica é:

$$
f_0=
\frac{1}{2\pi}
\sqrt{
\frac{k}{m}
}
$$

O erro percentual do período pode ser calculado por:

$$
E_{T,\mathrm{percentual}}=
100
\frac{
\left\lvert
T_{\mathrm{exp}}-
T_0
\right\rvert
}{
\left\lvert
T_0
\right\rvert
}
$$

Diferenças podem resultar de:

* amortecimento;
* massa da mola;
* incerteza na massa;
* incerteza na constante elástica;
* movimento lateral;
* deformação não linear;
* identificação imprecisa dos picos;
* limitações do sensor.

---

## Comparação com o modelo amortecido

O modelo amortecido é:

$$
x(t)=
x_c+
A_0e^{-\gamma t}
\cos\left(
\omega_dt+\phi
\right)
$$

A comparação deve considerar:

* coincidência dos períodos;
* decaimento da amplitude;
* posição de equilíbrio;
* fase;
* resíduos;
* comportamento nos primeiros ciclos;
* comportamento nos últimos ciclos.

Se o modelo representar bem os primeiros ciclos, mas não os últimos, podem existir:

* ruído comparável à amplitude final;
* atrito não viscoso;
* variação da posição de equilíbrio;
* resposta não linear do sensor.

Se o modelo representar bem os últimos ciclos, mas não os primeiros, podem existir:

* grandes amplitudes;
* não linearidade da mola;
* movimento lateral inicial;
* saturação do sensor.

---

## Fluxo recomendado no Excel

Um tratamento básico pode seguir esta sequência:

1. importar o arquivo CSV;
2. remover a linha `END`;
3. verificar os separadores decimais;
4. manter uma cópia dos dados brutos;
5. converter o tempo para segundos;
6. converter a posição para a unidade desejada;
7. construir o gráfico de posição em função do tempo;
8. determinar a posição de equilíbrio;
9. corrigir o deslocamento residual;
10. identificar máximos de mesmo sentido;
11. calcular o período médio;
12. calcular frequência e frequência angular;
13. determinar a taxa de amortecimento;
14. construir o gráfico de ln A em função do tempo;
15. ajustar o modelo completo, quando necessário;
16. construir o gráfico dos resíduos;
17. calcular erros e incertezas;
18. registrar todos os procedimentos utilizados.

---

## Exemplo de organização dos resultados

| Grandeza                     | Símbolo                     | Resultado | Unidade               |
| ---------------------------- | --------------------------- | --------: | --------------------- |
| Massa efetiva                | $m_{\mathrm{ef}}$           |           | $\mathrm{kg}$         |
| Período amortecido           | $T_d$                       |           | $\mathrm{s}$          |
| Frequência amortecida        | $f_d$                       |           | $\mathrm{Hz}$         |
| Frequência angular           | $\omega_d$                  |           | $\mathrm{rad,s^{-1}}$ |
| Taxa de amortecimento        | $\gamma$                    |           | $\mathrm{s^{-1}}$     |
| Constante de tempo           | $\tau$                      |           | $\mathrm{s}$          |
| Coeficiente de amortecimento | $b$                         |           | $\mathrm{kg,s^{-1}}$  |
| Razão de amortecimento       | $\zeta$                     |           | adimensional          |
| Fator de qualidade           | $Q$                         |           | adimensional          |
| Constante elástica           | $k$                         |           | $\mathrm{N,m^{-1}}$   |
| Erro percentual do período   | $E_{T,\mathrm{percentual}}$ |           | $%$                   |
| Erro quadrático médio        | $\mathrm{RMSE}$             |           | unidade da posição    |

Os resultados devem ser apresentados com uma quantidade de algarismos significativos compatível com as incertezas experimentais.

---

## Análise alternativa com Python

Para conjuntos maiores de dados, o Python permite automatizar a importação, o ajuste e a construção dos gráficos.

```python
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

data = pd.read_csv("dados.csv")

data["t_ms"] = pd.to_numeric(data["t_ms"], errors="coerce")
data["pos_cm"] = pd.to_numeric(data["pos_cm"], errors="coerce")

data = data.dropna().copy()

data["t_s"] = (data["t_ms"] - data["t_ms"].iloc[0]) / 1000
data["pos_m"] = data["pos_cm"] / 100

def damped_oscillator(t, x_c, amplitude, gamma, omega_d, phase):
    return (
        x_c
        + amplitude
        * np.exp(-gamma * t)
        * np.cos(omega_d * t + phase)
    )

t = data["t_s"].to_numpy()
x = data["pos_m"].to_numpy()

initial_parameters = [
    np.mean(x),
    (np.max(x) - np.min(x)) / 2,
    0.1,
    2 * np.pi,
    0.0,
]

parameters, covariance = curve_fit(
    damped_oscillator,
    t,
    x,
    p0=initial_parameters,
    maxfev=20000,
)

x_fit = damped_oscillator(t, *parameters)
residuals = x - x_fit

x_c, amplitude, gamma, omega_d, phase = parameters

print(f"Posição de equilíbrio: {x_c:.6f} m")
print(f"Amplitude inicial: {amplitude:.6f} m")
print(f"Taxa de amortecimento: {gamma:.6f} 1/s")
print(f"Frequência angular: {omega_d:.6f} rad/s")
print(f"Fase inicial: {phase:.6f} rad")

plt.figure()
plt.scatter(t, x, s=8, label="Dados experimentais")
plt.plot(t, x_fit, label="Ajuste")
plt.xlabel("Tempo (s)")
plt.ylabel("Posição (m)")
plt.legend()
plt.tight_layout()
plt.show()

plt.figure()
plt.scatter(t, residuals, s=8)
plt.axhline(0)
plt.xlabel("Tempo (s)")
plt.ylabel("Resíduo (m)")
plt.tight_layout()
plt.show()
```

O ajuste computacional não substitui a inspeção visual. Os parâmetros encontrados devem ser comparados com o gráfico, os resíduos e as expectativas físicas do experimento.

---

## Outras ferramentas

Os mesmos procedimentos podem ser realizados em:

* LibreOffice Calc;
* Google Sheets;
* Wolfram Mathematica;
* MATLAB;
* GNU Octave;
* Python;
* Origin;
* GNUplot.

A escolha da ferramenta não altera os princípios físicos da análise. O procedimento deve continuar sendo documentado e reproduzível.

---

## Boas práticas

* mantenha os dados brutos;
* registre todas as unidades;
* utilize os tempos realmente armazenados;
* verifique a posição de equilíbrio;
* use vários ciclos para determinar o período;
* utilize picos de mesmo sentido;
* não confunda erro com incerteza;
* evite remover pontos sem justificativa;
* inspecione os resíduos;
* informe os parâmetros do filtro;
* compare os resultados com modelos físicos;
* apresente valores com algarismos significativos adequados;
* registre as condições do experimento.

---

## Equações principais

| Grandeza                     | Equação                                                           |
| ---------------------------- | ----------------------------------------------------------------- |
| Conversão do tempo           | $t_i=(t_{\mathrm{ms},i}-t_{\mathrm{ms},0})/1000$                  |
| Conversão da posição         | $x_{\mathrm{m}}=x_{\mathrm{cm}}/100$                              |
| Frequência de amostragem     | $f_s=1/\overline{\Delta t}$                                       |
| Frequência de Nyquist        | $f_N=f_s/2$                                                       |
| Período médio                | $T_d=(t_{n+N}-t_n)/N$                                             |
| Frequência                   | $f_d=1/T_d$                                                       |
| Frequência angular           | $\omega_d=2\pi/T_d$                                               |
| Amplitude                    | $A_n=\lvert x_n-x_c\rvert$                                        |
| Taxa de amortecimento        | $\gamma=\ln(A_n/A_{n+N})/(t_{n+N}-t_n)$                           |
| Constante de tempo           | $\tau=1/\gamma$                                                   |
| Coeficiente de amortecimento | $b=2m\gamma$                                                      |
| Modelo amortecido            | $x(t)=x_c+A_0e^{-\gamma t}\cos(\omega_dt+\phi)$                   |
| Resíduo                      | $r_i=x_i-x_{\mathrm{modelo}}(t_i)$                                |
| Erro absoluto                | $E_{\mathrm{abs}}=\lvert x_{\mathrm{exp}}-x_{\mathrm{ref}}\rvert$ |
| Erro relativo                | $E_{\mathrm{rel}}=E_{\mathrm{abs}}/\lvert x_{\mathrm{ref}}\rvert$ |
| Erro percentual              | $E_{\mathrm{percentual}}=100E_{\mathrm{rel}}$                     |
| Velocidade numérica          | $v_i\approx(x_{i+1}-x_{i-1})/(t_{i+1}-t_{i-1})$                   |
| Aceleração numérica          | $a_i\approx(x_{i+1}-2x_i+x_{i-1})/\Delta t^2$                     |
