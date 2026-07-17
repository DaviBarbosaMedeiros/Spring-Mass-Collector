# Spring-Mass System

O sistema massa-mola é um dos modelos fundamentais para o estudo de movimentos oscilatórios. Em sua forma mais simples, ele é constituído por uma massa conectada a uma mola que exerce uma força restauradora quando é comprimida ou alongada.

Esse modelo permite relacionar matematicamente o deslocamento da massa, sua velocidade, sua aceleração, a constante elástica da mola, o período de oscilação e a energia mecânica do sistema.

---

## Modelo físico ideal

Considere uma massa $m$ conectada a uma mola de constante elástica $k$. O movimento ocorre em uma única direção, descrita pela coordenada $x$.

No modelo ideal, são adotadas as seguintes aproximações:

* a mola obedece à Lei de Hooke;
* a massa da mola é desprezível;
* o movimento ocorre em apenas uma dimensão;
* não existem forças dissipativas;
* a deformação permanece dentro do regime elástico;
* a massa pode ser tratada como uma partícula;
* a estrutura de suporte permanece fixa;
* a constante elástica da mola não varia durante o movimento.

A coordenada $x=0$ é escolhida na posição de equilíbrio. Dessa forma, $x$ representa o deslocamento da massa em relação a essa posição.

---

## Lei de Hooke

Quando uma mola é deformada dentro de seu regime elástico, ela exerce uma força aproximadamente proporcional à deformação:

$$
F_s=-kx
$$

onde:

| Grandeza           | Símbolo | Unidade no SI       |
| ------------------ | ------- | ------------------- |
| Força elástica     | $F_s$   | $\mathrm{N}$        |
| Constante elástica | $k$     | $\mathrm{N . m^{-1}}$ |
| Deslocamento       | $x$     | $\mathrm{m}$        |

O sinal negativo indica que a força elástica possui sentido oposto ao deslocamento.

Quando $x>0$, a força aponta no sentido negativo. Quando $x<0$, a força aponta no sentido positivo. Em ambos os casos, a força tende a conduzir a massa de volta à posição de equilíbrio.

!!! note "Regime elástico"
A Lei de Hooke é uma aproximação válida enquanto a mola permanece em sua região de resposta linear. Deformações excessivas podem produzir comportamento não linear ou deformação permanente.

A constante elástica $k$ caracteriza a rigidez da mola. Quanto maior o valor de $k$, maior será a força necessária para produzir uma determinada deformação.

---

## Equação do movimento

Aplicando a Segunda Lei de Newton à massa:

$$
\sum F=m\frac{d^2x}{dt^2}
$$

No sistema massa-mola horizontal ideal, a única força na direção do movimento é a força elástica:

$$
m\frac{d^2x}{dt^2}=-kx
$$

Reorganizando os termos:

$$
m\frac{d^2x}{dt^2}+kx=0
$$

Utilizando a notação de derivadas temporais:

$$
m\ddot{x}+kx=0
$$

Dividindo toda a equação pela massa:

$$
\ddot{x}+\frac{k}{m}x=0
$$

Define-se a frequência angular natural do sistema por:

$$
\omega_0^2=\frac{k}{m}
$$

Portanto:

$$
\omega_0=\sqrt{\frac{k}{m}}
$$

A equação do movimento assume a forma:

$$
\ddot{x}+\omega_0^2x=0
$$

Essa é a equação diferencial do movimento harmônico simples.

---

## Solução da equação diferencial

Considere a equação:

$$
\ddot{x}+\omega_0^2x=0
$$

Uma possível solução pode ser escrita na forma exponencial:

$$
x(t)=e^{rt}
$$

As derivadas dessa função são:

$$
\dot{x}(t)=re^{rt}
$$

e

$$
\ddot{x}(t)=r^2e^{rt}
$$

Substituindo na equação diferencial:

$$
r^2e^{rt}+\omega_0^2e^{rt}=0
$$

Como $e^{rt}\neq 0$, obtém-se a equação característica:

$$
r^2+\omega_0^2=0
$$

As raízes são:

$$
r=\pm i\omega_0
$$

A solução real correspondente pode ser escrita como:

$$
x(t)=C_1\cos(\omega_0t)+C_2\sin(\omega_0t)
$$

Outra forma equivalente, mais conveniente para a interpretação física, é:

$$
x(t)=A\cos(\omega_0t+\phi)
$$

onde:

| Parâmetro  | Significado                |
| ---------- | -------------------------- |
| $A$        | amplitude da oscilação     |
| $\omega_0$ | frequência angular natural |
| $\phi$     | fase inicial               |
| $t$        | tempo                      |

A amplitude $A$ representa o maior valor absoluto do deslocamento em relação ao equilíbrio:

$$
-A\leq x(t)\leq A
$$

A fase inicial $\phi$ determina o estado inicial da oscilação, isto é, a posição da massa dentro do ciclo oscilatório no instante $t=0$.

---

## Condições iniciais

A amplitude e a fase inicial são determinadas pela posição e pela velocidade da massa no instante inicial.

Considere:

$$
x(0)=x_i
$$

e

$$
v(0)=v_i
$$

Para a solução:

$$
x(t)=A\cos(\omega_0t+\phi)
$$

a posição inicial é:

$$
x_i=A\cos(\phi)
$$

A velocidade é obtida derivando a posição:

$$
v(t)=\frac{dx}{dt}
$$

Portanto:

$$
v(t)=-A\omega_0\sin(\omega_0t+\phi)
$$

No instante inicial:

$$
v_i=-A\omega_0\sin(\phi)
$$

A amplitude pode ser determinada a partir das condições iniciais:

$$
A=\sqrt{x_i^2+\left(\frac{v_i}{\omega_0}\right)^2}
$$

Assim, diferentes condições iniciais modificam a amplitude e a fase, mas não alteram a frequência natural do sistema ideal.

---

## Velocidade e aceleração

A posição da massa é dada por:

$$
x(t)=A\cos(\omega_0t+\phi)
$$

Derivando em relação ao tempo, obtém-se a velocidade:

$$
v(t)=-A\omega_0\sin(\omega_0t+\phi)
$$

O módulo máximo da velocidade é:

$$
v_{\max}=A\omega_0
$$

A velocidade é máxima quando a massa passa pela posição de equilíbrio, onde $x=0$.

Derivando novamente, obtém-se a aceleração:

$$
a(t)=-A\omega_0^2\cos(\omega_0t+\phi)
$$

Como:

$$
x(t)=A\cos(\omega_0t+\phi)
$$

a aceleração também pode ser escrita como:

$$
a(t)=-\omega_0^2x(t)
$$

Essa expressão mostra que a aceleração é proporcional ao deslocamento e possui sentido oposto a ele.

O módulo máximo da aceleração é:

$$
a_{\max}=A\omega_0^2
$$

A aceleração é máxima nos extremos da trajetória, onde $x=\pm A$, e é nula na posição de equilíbrio.

---

## Período, frequência e frequência angular

O período $T$ é o intervalo de tempo necessário para que o sistema complete uma oscilação.

Como o argumento da função cosseno varia em $2\pi$ durante um ciclo completo:

$$
\omega_0T=2\pi
$$

Portanto:

$$
T=\frac{2\pi}{\omega_0}
$$

Usando:

$$
\omega_0=\sqrt{\frac{k}{m}}
$$

obtém-se:

$$
T=2\pi\sqrt{\frac{m}{k}}
$$

A frequência $f_0$ corresponde ao número de oscilações completas realizadas por unidade de tempo:

$$
f_0=\frac{1}{T}
$$

Logo:

$$
f_0=\frac{1}{2\pi}\sqrt{\frac{k}{m}}
$$

As três grandezas estão relacionadas por:

$$
\omega_0=2\pi f_0=\frac{2\pi}{T}
$$

| Grandeza           | Símbolo    | Unidade no SI         |
| ------------------ | ---------- | --------------------- |
| Período            | $T$        | $\mathrm{s}$          |
| Frequência         | $f_0$      | $\mathrm{Hz}$         |
| Frequência angular | $\omega_0$ | $\mathrm{rad . s^{-1}}$ |

A expressão do período mostra que:

* o aumento da massa produz um aumento no período;
* o aumento da constante elástica produz uma diminuição no período;
* no modelo ideal, o período não depende da amplitude;
* molas mais rígidas produzem oscilações mais rápidas;
* massas maiores produzem oscilações mais lentas.

---

## Sistema massa-mola vertical

No Spring-Mass Collector, o experimento é realizado com uma configuração vertical. Nesse caso, além da força elástica, a massa está sujeita à força gravitacional.

Considere o eixo vertical orientado para baixo e a coordenada $y$ medida a partir do comprimento natural da mola.

As forças que atuam sobre a massa são:

* o peso $mg$, orientado para baixo;
* a força elástica $-ky$, orientada no sentido contrário à deformação.

Aplicando a Segunda Lei de Newton:

$$
m\ddot{y}=mg-ky
$$

Reorganizando:

$$
m\ddot{y}+ky=mg
$$

### Posição de equilíbrio estático

Na posição de equilíbrio, a massa permanece em repouso. Portanto:

$$
\ddot{y}=0
$$

Assim:

$$
ky_{\mathrm{eq}}=mg
$$

A deformação da mola na posição de equilíbrio é:

$$
y_{\mathrm{eq}}=\frac{mg}{k}
$$

Essa expressão também pode ser utilizada para determinar experimentalmente a constante elástica:

$$
k=\frac{mg}{y_{\mathrm{eq}}}
$$

### Deslocamento em relação ao equilíbrio

Define-se o deslocamento $x$ em relação à posição de equilíbrio:

$$
x=y-y_{\mathrm{eq}}
$$

Portanto:

$$
y=x+y_{\mathrm{eq}}
$$

Substituindo na equação do movimento:

$$
m\ddot{x}+k\left(x+y_{\mathrm{eq}}\right)=mg
$$

Como:

$$
ky_{\mathrm{eq}}=mg
$$

os termos gravitacionais se cancelam:

$$
m\ddot{x}+kx=0
$$

Portanto:

$$
\ddot{x}+\omega_0^2x=0
$$

com:

$$
\omega_0=\sqrt{\frac{k}{m}}
$$

Isso mostra que o sistema massa-mola vertical, quando descrito em relação à posição de equilíbrio, possui a mesma equação do movimento harmônico simples que o sistema horizontal.

!!! note "Efeito da gravidade"
No modelo ideal, a gravidade desloca a posição de equilíbrio, mas não altera a frequência natural da oscilação. Essa conclusão é válida quando a mola permanece no regime linear e o deslocamento é medido em relação ao equilíbrio.

---

## Energia potencial elástica

A energia potencial armazenada em uma mola ideal é:

$$
U(x)=\frac{1}{2}kx^2
$$

A energia potencial é mínima na posição de equilíbrio:

$$
U(0)=0
$$

Nos extremos da oscilação, onde $x=\pm A$, a energia potencial é máxima:

$$
U_{\max}=\frac{1}{2}kA^2
$$

Nesses pontos, a velocidade da massa é momentaneamente nula.

---

## Energia cinética

A energia cinética da massa é:

$$
K(t)=\frac{1}{2}mv^2(t)
$$

Substituindo a expressão da velocidade:

$$
v(t)=-A\omega_0\sin(\omega_0t+\phi)
$$

obtém-se:

$$
K(t)=\frac{1}{2}mA^2\omega_0^2
\sin^2(\omega_0t+\phi)
$$

Como:

$$
m\omega_0^2=k
$$

a energia cinética também pode ser escrita como:

$$
K(t)=\frac{1}{2}kA^2
\sin^2(\omega_0t+\phi)
$$

A energia cinética é máxima quando a massa passa pela posição de equilíbrio:

$$
x=0
$$

Nesse ponto:

$$
K_{\max}=\frac{1}{2}kA^2
$$

---

## Conservação da energia mecânica

No sistema ideal, não existem forças dissipativas. Consequentemente, a energia mecânica total permanece constante:

$$
E=K+U
$$

Substituindo as expressões da energia cinética e da energia potencial:

$$
E=
\frac{1}{2}mv^2+
\frac{1}{2}kx^2
$$

Para o movimento harmônico simples:

$$
E=\frac{1}{2}kA^2
$$

A energia mecânica alterna continuamente entre as formas cinética e potencial.

| Posição | Velocidade | Energia predominante       |               |                            |
| ------- | ---------- | -------------------------- | ------------- | -------------------------- |
| $x=0$   | máxima     | energia cinética           |               |                            |
| $x=+A$  | zero       | energia potencial elástica |               |                            |
| $x=-A$  | zero       | energia potencial elástica |               |                            |
| $0$     | x          | $A$                        | intermediária | combinação das duas formas |

Na posição de equilíbrio, a energia cinética é máxima e a energia potencial elástica é mínima. Nos extremos da trajetória, ocorre o contrário.

No sistema ideal, a amplitude permanece constante porque não existe perda de energia mecânica.

---

## Determinação experimental da constante elástica

A constante elástica pode ser determinada por diferentes métodos experimentais.

### Método estático

No equilíbrio vertical:

$$
ky_{\mathrm{eq}}=mg
$$

Portanto:

$$
k=\frac{mg}{y_{\mathrm{eq}}}
$$

Nesse método, mede-se a deformação produzida por uma massa conhecida.

Também é possível realizar várias medições com diferentes massas. A relação entre a força aplicada e a deformação é:

$$
F=kx
$$

Um gráfico de $F$ em função de $x$ deve apresentar comportamento aproximadamente linear. O coeficiente angular da reta corresponde à constante elástica $k$.

### Método dinâmico

Partindo da expressão do período:

$$
T=2\pi\sqrt{\frac{m}{k}}
$$

elevando ambos os lados ao quadrado:

$$
T^2=4\pi^2\frac{m}{k}
$$

Isolando a constante elástica:

$$
k=\frac{4\pi^2m}{T^2}
$$

Quando o experimento é realizado com diferentes massas:

$$
T^2=\frac{4\pi^2}{k}m
$$

Assim, um gráfico de $T^2$ em função de $m$ deve apresentar comportamento aproximadamente linear.

O coeficiente angular $a$ da reta é:

$$
a=\frac{4\pi^2}{k}
$$

Portanto:

$$
k=\frac{4\pi^2}{a}
$$

O uso de várias medições reduz a dependência de um único valor de período e permite avaliar melhor a consistência dos dados experimentais.

---

## Influência da massa da mola

No modelo ideal, a massa da mola é considerada desprezível. Entretanto, em um experimento real, parte da mola também se movimenta.

Para uma mola uniforme, uma aproximação frequentemente utilizada consiste em adicionar um terço da massa da mola à massa suspensa:

$$
m_{\mathrm{ef}}=m+\frac{m_s}{3}
$$

onde:

* $m_{\mathrm{ef}}$ é a massa efetiva do sistema;
* $m$ é a massa suspensa;
* $m_s$ é a massa da mola.

Nesse caso, o período pode ser aproximado por:

$$
T=2\pi\sqrt{\frac{m_{\mathrm{ef}}}{k}}
$$

ou:

$$
T=2\pi\sqrt{\frac{m+m_s/3}{k}}
$$

Essa correção pode ser importante quando a massa da mola não é pequena em comparação com a massa suspensa.

---

## Relação com o Spring-Mass Collector

O Spring-Mass Collector utiliza um sensor infravermelho para medir a distância entre o sensor e o disco refletor conectado à massa.

Inicialmente, o sensor fornece uma distância absoluta:

$$
x_{\mathrm{med}}(t)
$$

Durante a calibração, uma posição de referência é armazenada como $x_0$. O firmware calcula então a posição relativa:

$$
x_{\mathrm{rel}}(t)=x_{\mathrm{med}}(t)-x_0
$$

onde:

| Grandeza              | Descrição                                    |
| --------------------- | -------------------------------------------- |
| $x_{\mathrm{med}}(t)$ | distância absoluta medida pelo sensor        |
| $x_0$                 | distância definida como referência           |
| $x_{\mathrm{rel}}(t)$ | deslocamento relativo calculado pelo sistema |

Quando a calibração é realizada com a massa na posição de equilíbrio, a posição relativa corresponde ao deslocamento utilizado no modelo teórico:

$$
x_{\mathrm{rel}}(t)\approx x(t)
$$

Para um sistema ideal, espera-se que os dados apresentem o comportamento:

$$
x_{\mathrm{rel}}(t)=A\cos(\omega_0t+\phi)
$$

A partir dos valores de posição e tempo coletados pelo equipamento, é possível estimar experimentalmente:

* a amplitude da oscilação;
* o período;
* a frequência;
* a frequência angular;
* a constante elástica da mola;
* a velocidade e a aceleração;
* a diferença entre o comportamento ideal e o comportamento real.

---

## Limitações do modelo ideal

O movimento harmônico simples é uma aproximação. Em um experimento real, podem estar presentes:

* resistência do ar;
* atrito entre componentes;
* dissipação interna da mola;
* massa não desprezível da mola;
* movimento lateral da massa;
* rotação da massa ou do disco refletor;
* resposta não linear da mola;
* vibração da estrutura de suporte;
* desalinhamento entre o sensor e o disco refletor;
* incertezas na medição da posição;
* limitações da taxa de amostragem;
* ruídos na saída analógica do sensor.

Esses efeitos podem produzir diferenças entre a solução ideal e os dados experimentais.

!!! info "Interpretação física"
O movimento harmônico simples fornece uma referência teórica para o experimento. Diferenças entre o modelo e os dados não representam necessariamente uma falha do equipamento, mas podem indicar a presença de fenômenos físicos não considerados na descrição ideal.

Em particular, a diminuição da amplitude ao longo do tempo indica a presença de dissipação de energia. Esse comportamento será estudado na seção **Damped Oscillator**.

---

## Equações principais

| Grandeza                        | Equação                               |
| ------------------------------- | ------------------------------------- |
| Força elástica                  | $F_s=-kx$                             |
| Equação do movimento            | $m\ddot{x}+kx=0$                      |
| Frequência angular natural      | $\omega_0=\sqrt{k/m}$                 |
| Posição                         | $x(t)=A\cos(\omega_0t+\phi)$          |
| Velocidade                      | $v(t)=-A\omega_0\sin(\omega_0t+\phi)$ |
| Aceleração                      | $a(t)=-\omega_0^2x(t)$                |
| Período                         | $T=2\pi\sqrt{m/k}$                    |
| Frequência                      | $f_0=(1/2\pi)\sqrt{k/m}$              |
| Energia potencial elástica      | $U=(1/2)kx^2$                         |
| Energia cinética                | $K=(1/2)mv^2$                         |
| Energia mecânica total          | $E=(1/2)kA^2$                         |
| Equilíbrio vertical             | $y_{\mathrm{eq}}=mg/k$                |
| Constante elástica pelo período | $k=4\pi^2m/T^2$                       |

---

## Referências bibliográficas

1. NUSSENZVEIG, H. M. *Curso de Física Básica: Fluidos, Oscilações e Ondas, Calor*. v. 2. São Paulo: Blucher.

2. HALLIDAY, D.; RESNICK, R.; WALKER, J. *Fundamentos de Física: Gravitação, Ondas e Termodinâmica*. Rio de Janeiro: LTC.

3. TIPLER, P. A.; MOSCA, G. *Física para Cientistas e Engenheiros: Mecânica, Oscilações e Ondas, Termodinâmica*. Rio de Janeiro: LTC.

4. TAYLOR, J. R. *Classical Mechanics*. Sausalito: University Science Books.
