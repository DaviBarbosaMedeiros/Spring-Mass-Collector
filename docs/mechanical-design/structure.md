# Structure

A estrutura do **Spring-Mass Collector** foi projetada para organizar os componentes eletrônicos, facilitar a operação do sistema e permitir o posicionamento adequado do sensor infravermelho durante o experimento massa-mola.

Essa estrutura é composta por um corpo principal, uma região inclinada para o display LCD 16x2, aberturas para os botões físicos e um extensor vertical ajustável para o sensor.

---

## Visão geral da estrutura

A estrutura física pode ser dividida em quatro partes principais:

```text
Spring-Mass Collector
├── Corpo principal
├── Região inclinada do LCD
├── Aberturas para botões
└── Extensor vertical do sensor
```

Cada parte foi pensada para cumprir uma função específica dentro do equipamento.

| Parte                | Função                                            |
| -------------------- | ------------------------------------------------- |
| Corpo principal      | acomodar a eletrônica e servir como base da caixa |
| Região inclinada     | posicionar o LCD em ângulo adequado para leitura  |
| Aberturas dos botões | permitir acesso aos comandos físicos              |
| Extensor do sensor   | ajustar a altura do sensor infravermelho          |

---

## Corpo principal

O corpo principal é a base da caixa coletora. Ele abriga os componentes eletrônicos e fornece suporte para o display, os botões e o extensor do sensor.

Essa região deve permitir:

* acomodação da ESP32;
* organização da fiação interna;
* passagem dos cabos do sensor, LCD e botões;
* proteção básica dos circuitos;
* estabilidade sobre a bancada;
* acesso para manutenção e montagem.

O corpo principal também deve manter o conjunto suficientemente rígido para evitar deslocamentos durante a coleta de dados.

---

## Região inclinada do LCD

A parte frontal da estrutura possui uma região inclinada para encaixe do display **LCD 16x2 I2C**.

Essa inclinação é de aproximadamente:

```text
30 graus
```

A inclinação melhora a visualização das informações exibidas no LCD durante o uso em bancada.

<figure markdown>
  ![Região inclinada do LCD](../assets/lcd-angled-region.png){ width="700" }
  <figcaption>Região inclinada da estrutura, projetada para facilitar a leitura do display LCD 16x2 durante a operação.</figcaption>
</figure>

Durante o experimento, o usuário pode acompanhar:

* menu principal;
* modo atual;
* posição inicial calibrada;
* posição relativa;
* número de dados armazenados;
* estado da coleta;
* status de transferência;
* aviso de memória cheia.

A inclinação do display reduz a necessidade de reposicionar a caixa ou o usuário durante a operação.

---

## Aberturas para botões

A estrutura possui aberturas para três botões físicos.

Esses botões são responsáveis pela navegação entre os modos de operação e devem estar posicionados em uma região de fácil acesso.

A disposição dos botões deve permitir que o usuário controle a caixa sem deslocar o equipamento durante o experimento.

| Botão | Função geral                |
| ----- | --------------------------- |
| B1    | primeira ação do modo atual |
| B2    | segunda ação do modo atual  |
| B3    | terceira ação do modo atual |

A função específica de cada botão depende do modo ativo no firmware.

```text
Default       → B1 calibração, B2 coleta, B3 transferência
Calibração   → B1 recalibrar, B2 confirmar, B3 zerar
Coleta       → B1 pausar/retomar, B2 resetar, B3 voltar
Transferência→ B1 enviar, B2 voltar, B3 alterar limite
```

---

## Extensor vertical do sensor

O sensor infravermelho precisa estar alinhado com a massa oscilante. Para permitir esse ajuste, a estrutura possui um extensor vertical dedicado ao posicionamento do sensor.

Esse extensor permite ajustar a altura do sensor em até três níveis.

```text
Extensor do sensor
├── Nível 1
├── Nível 2
└── Nível 3
```

Esse recurso é importante porque diferentes montagens do sistema massa-mola podem posicionar a massa em alturas diferentes.

O ajuste vertical permite adaptar a caixa a diferentes configurações experimentais sem necessidade de suportes externos.

---

## Trava mecânica

O extensor vertical possui um sistema de trava mecânica lateral.

Para liberar o movimento do extensor, o usuário deve pressionar simultaneamente as laterais do mecanismo. Com as laterais pressionadas, o extensor pode ser deslocado verticalmente.

Ao soltar as laterais, a trava volta a fixar o extensor na posição escolhida.

```text
Pressionar laterais
        ↓
Trava é liberada
        ↓
Extensor pode se mover
        ↓
Soltar laterais
        ↓
Extensor fica travado
```

Esse mecanismo permite ajustar a altura do sensor de forma simples e sem ferramentas externas.

!!! warning "Travamento antes da coleta"
Antes de iniciar a coleta, verifique se o extensor está corretamente travado. Caso o sensor se mova durante o experimento, os dados de posição podem ser comprometidos.

---

## Posicionamento do sensor

O sensor deve ser posicionado de modo que a massa permaneça dentro da faixa de leitura durante toda a oscilação.

O alinhamento correto deve considerar:

* altura do sensor;
* distância inicial entre sensor e massa;
* amplitude esperada da oscilação;
* superfície refletora do alvo;
* ausência de obstáculos entre sensor e massa;
* estabilidade da caixa sobre a bancada.

Um posicionamento inadequado pode gerar leituras instáveis ou representar uma distância diferente da trajetória real da massa.

---

## Integração com o experimento massa-mola

A estrutura não deve interferir no movimento da massa. Sua função é posicionar o sensor e manter a eletrônica estável durante a coleta.

Durante a montagem, a caixa deve ser colocada em uma posição em que:

```text
Sensor infravermelho → massa oscilante
```

O sensor deve permanecer fixo, enquanto a massa se desloca em relação a ele.

A medida obtida será posteriormente convertida em posição relativa pelo firmware, usando a referência definida no modo de calibração.

---

## Estabilidade mecânica

A estabilidade da estrutura é essencial para a qualidade dos dados coletados.

Se a caixa se mover durante o experimento, o sensor também se move. Nesse caso, a distância medida pode variar devido ao movimento da própria caixa, e não apenas devido ao movimento da massa.

Por isso, a estrutura deve garantir:

* base estável;
* boa fixação dos componentes;
* rigidez suficiente;
* extensor do sensor travado;
* botões acessíveis sem deslocar a caixa;
* fiação interna organizada.

---

## Organização interna

A parte interna da caixa deve acomodar a ESP32 e as conexões entre os módulos.

A organização interna deve evitar:

* fios pressionando os botões;
* cabos soltos próximos ao extensor;
* conexões tensionadas;
* contato indevido entre terminais;
* dificuldade de acesso para manutenção.

Uma organização interna adequada facilita testes, reparos e futuras modificações no protótipo.

---

## Relação entre estrutura e interface

A estrutura foi projetada para tornar a interface local mais confortável.

A região inclinada melhora a leitura do LCD, enquanto os botões frontais permitem operação direta.

```text
LCD inclinado
        ↓
melhor leitura

Botões frontais
        ↓
melhor acesso

Extensor ajustável
        ↓
melhor alinhamento do sensor
```

Essa combinação torna o sistema mais adequado para uso em bancada didática.

---

## Requisitos funcionais da estrutura

A estrutura 3D deve atender aos seguintes requisitos:

| Requisito                  | Descrição                               |
| -------------------------- | --------------------------------------- |
| proteger componentes       | reduzir exposição da eletrônica         |
| permitir leitura do LCD    | posicionar o display em ângulo adequado |
| permitir acesso aos botões | facilitar controle dos modos            |
| ajustar altura do sensor   | adaptar a caixa a diferentes montagens  |
| manter o sensor fixo       | evitar movimento durante a coleta       |
| facilitar montagem         | permitir reprodução do projeto          |
| manter baixo custo         | preservar o caráter didático do sistema |

---

## Resumo

A estrutura do Spring-Mass Collector é formada por um corpo principal, uma região inclinada para o LCD, aberturas para os botões e um extensor vertical ajustável para o sensor infravermelho.

```text
Structure
├── Corpo principal
│   └── acomoda ESP32 e conexões
│
├── Região inclinada do LCD
│   └── melhora a visualização da tela
│
├── Aberturas frontais
│   └── permitem acesso aos botões
│
└── Extensor do sensor
    ├── permite ajuste em três níveis
    └── possui trava mecânica lateral
```

Essa estrutura integra a eletrônica ao uso experimental, permitindo que o sistema seja operado de forma estável, organizada e reprodutível.
