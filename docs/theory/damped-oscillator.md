# Damped Oscillator

Em um sistema massa-mola ideal, a energia mecânica é conservada e a amplitude permanece constante. Em um experimento real, entretanto, a amplitude geralmente diminui com o tempo devido à dissipação de energia causada por efeitos como resistência do ar, atrito interno da mola e vibrações da estrutura.

Um sistema no qual a amplitude da oscilação diminui ao longo do tempo é denominado **oscilador amortecido**.

A análise do amortecimento permite compreender por que o movimento medido pelo Spring-Mass Collector não corresponde exatamente ao movimento harmônico simples e possibilita determinar parâmetros associados à dissipação de energia.

---

## Força de amortecimento

Um dos modelos mais simples para representar a dissipação consiste em considerar uma força proporcional à velocidade da massa:

$$
F_d=-b\dot{x}
$$

ou:

$$
F_d=-bv
$$

onde:

| Grandeza                     | Símbolo     | Unidade no SI        |
| ---------------------------- | ----------- | -------------------- |
| Força de amortecimento       | $F_d$       | $\mathrm{N}$         |
| Coeficiente de amortecimento | $b$         | $\mathrm{kg . s^{-1}}$ |
| Velocidade                   | $v=\dot{x}$ | $\mathrm{m . s^{-1}}$  |

O sinal negativo indica que a força de amortecimento possui sentido oposto ao movimento.

Quando a massa se desloca no sentido positivo, $\dot{x}>0$, a força de amortecimento aponta no sentido negativo. Quando a massa se desloca no sentido negativo, $\dot{x}<0$, a força aponta no sentido positivo.

A força de amortecimento, portanto, sempre retira energia mecânica do sistema.

!!! note "Amortecimento viscoso"
O modelo $F_d=-b\dot{x}$ é denominado amortecimento viscoso ou linear. Ele representa adequadamente muitos sistemas quando as velocidades são moderadas e a dissipação é aproximadamente proporcional à velocidade.

---

## Equação do movimento

Considere uma massa $m$ conectada a uma mola de constante elástica $k$ e sujeita a uma força de amortecimento linear.

As forças que atuam na direção do movimento são:

$$
F_s=-kx
$$

e:

$$
F_d=-b\dot{x}
$$

Aplicando a Segunda Lei de Newton:

$$
m\ddot{x}=-kx-b\dot{x}
$$

Reorganizando:

$$
m\ddot{x}+b\dot{x}+kx=0
$$

Essa é a equação diferencial do oscilador harmônico amortecido sem força externa.

Dividindo toda a equação pela massa:

$$
\ddot{x}+\frac{b}{m}\dot{x}+\frac{k}{m}x=0
$$

Define-se a frequência angular natural do sistema não amortecido:

$$
\omega_0=\sqrt{\frac{k}{m}}
$$

e o parâmetro de amortecimento:

$$
\gamma=\frac{b}{2m}
$$

Assim:

$$
\frac{b}{m}=2\gamma
$$

A equação do movimento pode ser escrita como:

$$
\ddot{x}+2\gamma\dot{x}+\omega_0^2x=0
$$

---

## Razão de amortecimento

Também é comum representar o amortecimento por meio da razão adimensional $\zeta$, definida por:

$$
\zeta=\frac{b}{2\sqrt{km}}
$$

Como:

$$
\omega_0=\sqrt{\frac{k}{m}}
$$

e:

$$
\gamma=\frac{b}{2m}
$$

obtém-se:

$$
\zeta=\frac{\gamma}{\omega_0}
$$

A equação do movimento pode então ser escrita como:

$$
\ddot{x}+2\zeta\omega_0\dot{x}+\omega_0^2x=0
$$

A razão de amortecimento permite classificar o comportamento do sistema:

| Condição    | Classificação           |
| ----------- | ----------------------- |
| $\zeta=0$   | sem amortecimento       |
| $0<\zeta<1$ | subamortecido           |
| $\zeta=1$   | criticamente amortecido |
| $\zeta>1$   | superamortecido         |

---

## Solução da equação diferencial

Considere a equação:

$$
\ddot{x}+2\gamma\dot{x}+\omega_0^2x=0
$$

Procura-se uma solução exponencial da forma:

$$
x(t)=e^{rt}
$$

As derivadas são:

$$
\dot{x}(t)=re^{rt}
$$

e:

$$
\ddot{x}(t)=r^2e^{rt}
$$

Substituindo na equação diferencial:

$$
r^2e^{rt}+2\gamma re^{rt}+\omega_0^2e^{rt}=0
$$

Como $e^{rt}\neq 0$:

$$
r^2+2\gamma r+\omega_0^2=0
$$

Essa é a equação característica do sistema.

As raízes são:

$$
r=-\gamma\pm\sqrt{\gamma^2-\omega_0^2}
$$

O comportamento da solução depende do sinal do termo:

$$
\gamma^2-\omega_0^2
$$

Isso produz três regimes distintos de amortecimento.

---

## Movimento subamortecido

O sistema é subamortecido quando:

$$
\gamma<\omega_0
$$

ou, equivalentemente:

$$
0<\zeta<1
$$

Nesse caso:

$$
\gamma^2-\omega_0^2<0
$$

Define-se a frequência angular amortecida:

$$
\omega_d=\sqrt{\omega_0^2-\gamma^2}
$$

As raízes da equação característica são:

$$
r=-\gamma\pm i\omega_d
$$

A solução real pode ser escrita como:

$$
x(t)=e^{-\gamma t}
\left[
C_1\cos(\omega_dt)+C_2\sin(\omega_dt)
\right]
$$

Uma forma equivalente é:

$$
x(t)=Ae^{-\gamma t}\cos(\omega_dt+\phi)
$$

onde:

| Parâmetro  | Significado                                       |
| ---------- | ------------------------------------------------- |
| $A$        | amplitude inicial associada às condições iniciais |
| $\gamma$   | taxa de decaimento da amplitude                   |
| $\omega_d$ | frequência angular amortecida                     |
| $\phi$     | fase inicial                                      |
| $t$        | tempo                                             |

Esse é o regime esperado para a maioria dos experimentos didáticos com uma massa suspensa por uma mola.

A massa continua oscilando em torno da posição de equilíbrio, mas a amplitude diminui progressivamente.

---

## Envoltória da amplitude

No movimento subamortecido:

$$
x(t)=Ae^{-\gamma t}\cos(\omega_dt+\phi)
$$

O fator:

$$
A(t)=Ae^{-\gamma t}
$$

representa a envoltória da amplitude.

As envoltórias superior e inferior são:

$$
x_{\mathrm{sup}}(t)=Ae^{-\gamma t}
$$

e:

$$
x_{\mathrm{inf}}(t)=-Ae^{-\gamma t}
$$

No instante inicial:

$$
A(0)=A
$$

Após um tempo $t$:

$$
A(t)=Ae^{-\gamma t}
$$

Quanto maior o valor de $\gamma$, mais rapidamente a amplitude diminui.

---

## Constante de tempo do amortecimento

Define-se a constante de tempo $\tau$ por:

$$
\tau=\frac{1}{\gamma}
$$

Assim, a envoltória pode ser escrita como:

$$
A(t)=Ae^{-t/\tau}
$$

No instante $t=\tau$:

$$
A(\tau)=Ae^{-1}
$$

Como:

$$
e^{-1}\approx 0{,}368
$$

a amplitude após uma constante de tempo corresponde a aproximadamente $36{,}8%$ da amplitude inicial.

A constante de tempo pode ser escrita em função do coeficiente de amortecimento:

$$
\tau=\frac{2m}{b}
$$

Portanto, um sistema com maior coeficiente $b$ apresenta menor constante de tempo e perde amplitude mais rapidamente.

---

## Frequência amortecida

A frequência angular do sistema amortecido é:

$$
\omega_d=\sqrt{\omega_0^2-\gamma^2}
$$

Em termos da razão de amortecimento:

$$
\omega_d=\omega_0\sqrt{1-\zeta^2}
$$

Como $\gamma^2>0$:

$$
\omega_d<\omega_0
$$

Portanto, o amortecimento reduz ligeiramente a frequência de oscilação.

O período amortecido é:

$$
T_d=\frac{2\pi}{\omega_d}
$$

e a frequência amortecida é:

$$
f_d=\frac{\omega_d}{2\pi}
$$

Quando o amortecimento é fraco:

$$
\gamma\ll\omega_0
$$

pode-se aproximar:

$$
\omega_d\approx\omega_0
$$

e:

$$
T_d\approx T_0
$$

Nesse caso, a principal diferença entre o movimento ideal e o movimento real é a diminuição da amplitude.

---

## Movimento criticamente amortecido

O amortecimento crítico ocorre quando:

$$
\gamma=\omega_0
$$

ou:

$$
\zeta=1
$$

Nesse caso, a equação característica possui duas raízes reais iguais:

$$
r=-\gamma=-\omega_0
$$

A solução é:

$$
x(t)=\left(C_1+C_2t\right)e^{-\omega_0t}
$$

O sistema retorna à posição de equilíbrio sem oscilar.

O amortecimento crítico corresponde ao retorno mais rápido possível ao equilíbrio sem que a massa ultrapasse essa posição repetidamente.

Esse comportamento é desejável em sistemas como:

* instrumentos de medição;
* mecanismos de fechamento;
* sistemas de suspensão;
* amortecedores;
* dispositivos de controle mecânico.

---

## Movimento superamortecido

O sistema é superamortecido quando:

$$
\gamma>\omega_0
$$

ou:

$$
\zeta>1
$$

As raízes da equação característica são reais e distintas:

$$
r_1=-\gamma+\sqrt{\gamma^2-\omega_0^2}
$$

e:

$$
r_2=-\gamma-\sqrt{\gamma^2-\omega_0^2}
$$

A solução é:

$$
x(t)=C_1e^{r_1t}+C_2e^{r_2t}
$$

Como as duas raízes são negativas, ambos os termos diminuem com o tempo.

O sistema retorna à posição de equilíbrio sem oscilar, mas de maneira mais lenta do que no caso criticamente amortecido.

---

## Comparação entre os regimes

| Regime                  | Condição          | Comportamento                    |
| ----------------------- | ----------------- | -------------------------------- |
| Sem amortecimento       | $\gamma=0$        | oscila com amplitude constante   |
| Subamortecido           | $\gamma<\omega_0$ | oscila com amplitude decrescente |
| Criticamente amortecido | $\gamma=\omega_0$ | retorna rapidamente sem oscilar  |
| Superamortecido         | $\gamma>\omega_0$ | retorna lentamente sem oscilar   |

Para o Spring-Mass Collector, o regime de maior interesse é o subamortecido, pois permite observar sucessivas oscilações e analisar o decaimento da amplitude.

---

## Velocidade no regime subamortecido

Para:

$$
x(t)=Ae^{-\gamma t}\cos(\omega_dt+\phi)
$$

a velocidade é:

$$
v(t)=\frac{dx}{dt}
$$

Aplicando a regra do produto:

$$
v(t)=-Ae^{-\gamma t}\left[\gamma\cos(\omega_dt+\phi)+\omega_d\sin(\omega_dt+\phi)\right]
$$

Diferentemente do movimento harmônico simples ideal, a velocidade não depende apenas do termo senoidal. Existe também uma contribuição relacionada ao decaimento exponencial.

---

## Aceleração no regime subamortecido

A aceleração pode ser obtida por derivação direta ou pela equação do movimento:

$$
\ddot{x}+2\gamma\dot{x}+\omega_0^2x=0
$$

Assim:

$$
a(t)=-2\gamma v(t)-\omega_0^2x(t)
$$

Essa expressão mostra que a aceleração depende tanto da posição quanto da velocidade.

No sistema ideal, sem amortecimento:

$$
a(t)=-\omega_0^2x(t)
$$

No sistema amortecido, surge o termo adicional:

$$
-2\gamma v(t)
$$

associado à dissipação.

---

## Dissipação de energia

A energia mecânica instantânea do sistema é:

$$
E(t)=\frac{1}{2}m\dot{x}^2+\frac{1}{2}kx^2
$$

Derivando em relação ao tempo:

$$
\frac{dE}{dt}=m\dot{x}\ddot{x}+kx\dot{x}
$$

Colocando $\dot{x}$ em evidência:

$$
\frac{dE}{dt}=\dot{x}\left(m\ddot{x}+kx\right)
$$

A equação do movimento é:

$$
m\ddot{x}+b\dot{x}+kx=0
$$

Portanto:

$$
m\ddot{x}+kx=-b\dot{x}
$$

Substituindo:

$$
\frac{dE}{dt}=-b\dot{x}^2
$$

Como:

$$
b\dot{x}^2\geq 0
$$

tem-se:

$$
\frac{dE}{dt}\leq 0
$$

A energia mecânica nunca aumenta devido à força de amortecimento. Ela é continuamente transformada em outras formas de energia, principalmente energia térmica.

---

## Decaimento médio da energia

No regime subamortecido, a amplitude diminui segundo:

$$
A(t)=A_0e^{-\gamma t}
$$

Como a energia é proporcional ao quadrado da amplitude:

$$
E\propto A^2
$$

a envoltória da energia diminui como:

$$
E(t)\approx E_0e^{-2\gamma t}
$$

Em termos da constante de tempo:

$$
E(t)\approx E_0e^{-2t/\tau}
$$

A energia, portanto, diminui aproximadamente duas vezes mais rapidamente no expoente do que a amplitude.

!!! note "Energia instantânea"
A expressão exponencial representa a envoltória ou o comportamento médio da energia. A energia cinética e a energia potencial continuam sendo convertidas uma na outra durante cada oscilação.

---

## Decremento logarítmico

O decremento logarítmico é uma forma experimental de determinar o amortecimento a partir das amplitudes de picos sucessivos.

Considere dois máximos de mesmo sentido, separados por um período amortecido:

$$
x_n=Ae^{-\gamma t_n}
$$

e:

$$
x_{n+1}=Ae^{-\gamma(t_n+T_d)}
$$

A razão entre eles é:

$$
\frac{x_n}{x_{n+1}}=e^{\gamma T_d}
$$

Aplicando o logaritmo natural:

$$
\delta=
\ln\left(
\frac{x_n}{x_{n+1}}
\right)
$$

Portanto:

$$
\delta=\gamma T_d
$$

O parâmetro $\delta$ é denominado decremento logarítmico.

A taxa de amortecimento pode ser determinada por:

$$
\gamma=\frac{\delta}{T_d}
$$

Se forem utilizadas amplitudes separadas por $N$ períodos:

$$
\delta=
\frac{1}{N}
\ln\left(
\frac{x_n}{x_{n+N}}
\right)
$$

O uso de vários períodos reduz a influência de pequenas flutuações experimentais.

---

## Decremento logarítmico e razão de amortecimento

Como:

$$
T_d=\frac{2\pi}{\omega_d}
$$

e:

$$
\omega_d=\omega_0\sqrt{1-\zeta^2}
$$

o decremento logarítmico pode ser escrito como:

$$
\delta=
\frac{2\pi\zeta}{\sqrt{1-\zeta^2}}
$$

Isolando $\zeta$:

$$
\zeta=
\frac{\delta}{\sqrt{4\pi^2+\delta^2}}
$$

Para amortecimento fraco, $\zeta\ll1$, pode-se utilizar a aproximação:

$$
\zeta\approx\frac{\delta}{2\pi}
$$

---

## Fator de qualidade

O fator de qualidade $Q$ mede quão lentamente o sistema perde energia.

Para um oscilador fracamente amortecido:

$$
Q=\frac{\omega_0}{2\gamma}
$$

Como:

$$
\gamma=\frac{b}{2m}
$$

obtém-se:

$$
Q=\frac{m\omega_0}{b}
$$

Em termos da razão de amortecimento:

$$
Q=\frac{1}{2\zeta}
$$

Para amortecimento fraco, o fator de qualidade também pode ser aproximado por:

$$
Q\approx\frac{\pi}{\delta}
$$

Um valor elevado de $Q$ indica que o sistema realiza muitas oscilações antes que a amplitude diminua significativamente.

Um valor baixo de $Q$ indica dissipação mais intensa.

---

## Determinação experimental do coeficiente de amortecimento

Se a massa $m$ e o parâmetro $\gamma$ forem conhecidos:

$$
b=2m\gamma
$$

Utilizando o decremento logarítmico:

$$
\gamma=\frac{\delta}{T_d}
$$

obtém-se:

$$
b=\frac{2m\delta}{T_d}
$$

O procedimento experimental pode ser resumido da seguinte forma:

1. identificar máximos sucessivos da posição;
2. medir suas amplitudes em relação ao equilíbrio;
3. calcular o decremento logarítmico;
4. determinar o período amortecido;
5. calcular $\gamma$;
6. calcular o coeficiente $b$.

Para maior precisão, devem ser utilizados vários picos e vários períodos.

---

## Linearização da envoltória

A envoltória da amplitude é:

$$
A(t)=A_0e^{-\gamma t}
$$

Aplicando o logaritmo natural:

$$
\ln A(t)=\ln A_0-\gamma t
$$

Essa expressão possui a forma de uma equação linear:

$$
y=a+bt
$$

com:

$$
y=\ln A(t)
$$

$$
a=\ln A_0
$$

e:

$$
b=-\gamma
$$

Assim, um gráfico de $\ln A$ em função do tempo deve ser aproximadamente linear.

O módulo do coeficiente angular da reta fornece a taxa de amortecimento:

$$
\gamma=-\frac{d(\ln A)}{dt}
$$

Esse procedimento é particularmente útil para o tratamento computacional dos dados experimentais.

---

## Sistema massa-mola vertical amortecido

Na configuração vertical, considere a coordenada $y$ medida a partir do comprimento natural da mola.

As forças são:

* peso $mg$;
* força elástica $-ky$;
* força de amortecimento $-b\dot{y}$.

A equação do movimento é:

$$
m\ddot{y}=mg-ky-b\dot{y}
$$

Reorganizando:

$$
m\ddot{y}+b\dot{y}+ky=mg
$$

A posição de equilíbrio estático satisfaz:

$$
ky_{\mathrm{eq}}=mg
$$

Define-se o deslocamento relativo ao equilíbrio:

$$
x=y-y_{\mathrm{eq}}
$$

Como:

$$
y=x+y_{\mathrm{eq}}
$$

e:

$$
\dot{y}=\dot{x}
$$

$$
\ddot{y}=\ddot{x}
$$

substituindo na equação:

$$
m\ddot{x}+b\dot{x}
+k\left(x+y_{\mathrm{eq}}\right)=mg
$$

Utilizando:

$$
ky_{\mathrm{eq}}=mg
$$

obtém-se:

$$
m\ddot{x}+b\dot{x}+kx=0
$$

Portanto, a gravidade desloca a posição de equilíbrio, mas não modifica a forma da equação do oscilador amortecido quando o deslocamento é medido em relação ao equilíbrio.

---

## Relação com o Spring-Mass Collector

O Spring-Mass Collector registra a posição relativa da massa em função do tempo.

Quando o sistema opera no regime subamortecido, espera-se um comportamento aproximadamente descrito por:

$$
x_{\mathrm{rel}}(t)=A e^{-\gamma t} \cos(\omega_dt+\phi)
$$

Em um experimento real, pode existir um pequeno deslocamento residual da referência. Nesse caso, um modelo mais geral é:

$$
x_{\mathrm{rel}}(t)=x_c+Ae^{-\gamma t}\cos(\omega_dt+\phi)
$$

onde $x_c$ representa um possível deslocamento constante em relação ao zero definido durante a calibração.

A partir dos dados coletados, podem ser determinados:

* amplitude inicial $A$;
* posição de equilíbrio ou deslocamento residual $x_c$;
* frequência angular amortecida $\omega_d$;
* período amortecido $T_d$;
* taxa de amortecimento $\gamma$;
* constante de tempo $\tau$;
* razão de amortecimento $\zeta$;
* coeficiente de amortecimento $b$;
* fator de qualidade $Q$.

O comportamento ideal esperado no gráfico de posição em função do tempo é uma oscilação cuja envoltória diminui exponencialmente.

---

## Sinal da posição medida

Dependendo da orientação do sensor, o aumento da distância medida pode corresponder a um deslocamento positivo ou negativo no modelo físico.

Uma inversão do sinal produz:

$$
x_{\mathrm{med}}(t)=-x(t)
$$

Essa inversão não altera:

* o período;
* a frequência;
* a taxa de amortecimento;
* a constante de tempo;
* o módulo da amplitude.

Ela corresponde apenas a uma mudança na orientação do eixo ou a uma alteração da fase da oscilação.

---

## Fontes de amortecimento no experimento

O amortecimento observado no sistema real pode resultar da combinação de diferentes mecanismos:

* resistência do ar;
* atrito interno da mola;
* deformações internas do material;
* movimento do suporte da massa;
* vibração da estrutura;
* movimento lateral ou pendular;
* atrito em pontos de conexão;
* rotação da massa ou do disco refletor;
* transferência de energia para o suporte;
* interação entre a mola e os elementos de fixação.

O coeficiente $b$ obtido experimentalmente representa, em geral, o efeito combinado desses mecanismos.

---

## Limitações do modelo linear

A expressão:

$$
F_d=-b\dot{x}
$$

é uma aproximação.

Em algumas situações, a resistência do ar pode depender aproximadamente do quadrado da velocidade:

$$
F_d\propto-\dot{x}|\dot{x}|
$$

Também podem existir forças de atrito aproximadamente constantes, como no atrito seco:

$$
F_f\approx-\mu N,\operatorname{sgn}(\dot{x})
$$

Esses mecanismos produzem decaimentos diferentes do comportamento exponencial simples.

Outras limitações incluem:

* deformação não linear da mola;
* variação do coeficiente de amortecimento;
* massa não desprezível da mola;
* grandes amplitudes;
* movimento em mais de uma dimensão;
* ruído do sensor;
* desalinhamento do disco refletor;
* vibrações externas;
* resolução temporal limitada;
* pequenas variações na posição de equilíbrio.

!!! info "Interpretação experimental"
O modelo linear amortecido deve ser utilizado como uma aproximação de referência. Diferenças sistemáticas entre a curva teórica e os dados podem indicar que outros mecanismos de dissipação estão presentes.

---

## Equações principais

| Grandeza                     | Equação                                   |
| ---------------------------- | ----------------------------------------- |
| Força de amortecimento       | $F_d=-b\dot{x}$                           |
| Equação do movimento         | $m\ddot{x}+b\dot{x}+kx=0$                 |
| Frequência natural           | $\omega_0=\sqrt{k/m}$                     |
| Taxa de amortecimento        | $\gamma=b/(2m)$                           |
| Razão de amortecimento       | $\zeta=b/(2\sqrt{km})$                    |
| Frequência amortecida        | $\omega_d=\sqrt{\omega_0^2-\gamma^2}$     |
| Solução subamortecida        | $x(t)=Ae^{-\gamma t}\cos(\omega_dt+\phi)$ |
| Período amortecido           | $T_d=2\pi/\omega_d$                       |
| Constante de tempo           | $\tau=1/\gamma$                           |
| Envoltória da amplitude      | $A(t)=A_0e^{-\gamma t}$                   |
| Decaimento médio da energia  | $E(t)\approx E_0e^{-2\gamma t}$           |
| Decremento logarítmico       | $\delta=\ln(x_n/x_{n+1})$                 |
| Taxa pelo decremento         | $\gamma=\delta/T_d$                       |
| Coeficiente de amortecimento | $b=2m\gamma$                              |
| Fator de qualidade           | $Q=\omega_0/(2\gamma)$                    |

---

## Referências bibliográficas

1. NUSSENZVEIG, H. M. *Curso de Física Básica: Fluidos, Oscilações e Ondas, Calor*. v. 2. São Paulo: Blucher.

2. HALLIDAY, D.; RESNICK, R.; WALKER, J. *Fundamentos de Física: Gravitação, Ondas e Termodinâmica*. Rio de Janeiro: LTC.

3. MARION, J. B.; THORNTON, S. T. *Classical Dynamics of Particles and Systems*. Belmont: Brooks/Cole.
