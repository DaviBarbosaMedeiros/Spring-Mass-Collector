# Mechanical Design Overview

O projeto mecânico do **Spring-Mass Collector** foi desenvolvido para transformar o conjunto eletrônico em um equipamento físico adequado ao uso em experimentos didáticos com sistema massa-mola.

A estrutura 3D organiza os componentes, protege a eletrônica, melhora a visualização do display, facilita o acesso aos botões e permite ajustar a posição do sensor infravermelho em relação à massa oscilante.

---

## Função do projeto mecânico

O projeto mecânico não atua apenas como uma caixa para armazenar os componentes. Ele faz parte do funcionamento experimental do sistema, pois define a posição relativa entre:

* sensor infravermelho;
* massa oscilante;
* display LCD;
* botões de controle;
* circuito interno;
* usuário durante a operação.

A estrutura foi pensada para facilitar a montagem, o uso e a repetição do experimento em ambiente didático.

---

## Visão geral da estrutura

A estrutura física do Spring-Mass Collector pode ser dividida em três regiões principais:

```text
Estrutura 3D
├── Corpo principal da caixa
├── Região inclinada para o LCD 16x2
└── Extensor vertical para o sensor infravermelho
```

Cada região possui uma função específica dentro do sistema.

| Região             | Função                                        |
| ------------------ | --------------------------------------------- |
| Corpo principal    | acomoda ESP32, conexões e parte da eletrônica |
| Região do LCD      | posiciona o display para melhor visualização  |
| Extensor do sensor | ajusta a altura do sensor infravermelho       |
| Aberturas frontais | permitem acesso aos botões físicos            |
| Trava mecânica     | fixa o extensor na altura escolhida           |

---

## Corpo principal da caixa

O corpo principal é a base da estrutura. Ele abriga os componentes eletrônicos e fornece suporte para a interface local.

Essa região deve permitir:

* acomodação da ESP32;
* passagem dos fios internos;
* fixação do display;
* posicionamento dos botões;
* suporte ao extensor do sensor;
* proteção básica dos componentes;
* acesso para montagem e manutenção.

O objetivo é manter o sistema compacto, organizado e adequado ao uso em bancada.

---

## Região inclinada do display

A estrutura possui uma região frontal destinada ao display **LCD 16x2 I2C**.

Essa região é inclinada em aproximadamente **30 graus**, o que melhora a visualização da tela durante o uso do equipamento.

```text
Display LCD 16x2
        ↓
Região inclinada em 30°
        ↓
Melhor visualização durante a operação
```

Essa inclinação é importante porque o usuário normalmente opera a caixa sobre uma bancada. Com o LCD inclinado, a leitura das informações fica mais confortável sem exigir que o usuário olhe diretamente de cima para baixo.

Durante o experimento, o LCD pode exibir informações como:

* menu principal;
* posição inicial;
* posição relativa;
* quantidade de dados armazenados;
* estado da coleta;
* modo de transferência;
* aviso de memória cheia.

---

## Aberturas para botões

A caixa possui aberturas para os três botões físicos usados na navegação do sistema.

Os botões devem ficar acessíveis na parte frontal da estrutura, permitindo que o usuário controle a caixa sem movimentar o equipamento durante a coleta.

A função de cada botão depende do modo atual do firmware.

| Modo          | B1             | B2             | B3                    |
| ------------- | -------------- | -------------- | --------------------- |
| Default       | Calibração     | Coleta         | Transferência         |
| Calibração    | Recalibrar     | Confirmar      | Zerar posição inicial |
| Coleta        | Pausar/retomar | Resetar coleta | Voltar                |
| Transferência | Enviar dados   | Voltar         | Alterar limite        |

O posicionamento dos botões deve permitir operação simples e reduzir o risco de pressionamentos acidentais.

---

## Extensor vertical do sensor

O sensor infravermelho precisa estar alinhado com a massa oscilante. Como diferentes montagens experimentais podem ter alturas distintas, a estrutura possui um extensor vertical para ajuste da posição do sensor.

Esse extensor permite posicionar o sensor em até **três níveis de altura**.

```text
Extensor do sensor
├── nível 1
├── nível 2
└── nível 3
```

Esse ajuste torna o sistema mais flexível, permitindo adaptar a caixa a diferentes configurações do experimento massa-mola.

---

## Trava mecânica do extensor

O extensor vertical possui um sistema de trava mecânica.

Para destravar o mecanismo, o usuário deve pressionar simultaneamente as laterais da estrutura. Isso libera o movimento vertical do extensor.

Ao soltar as laterais, a trava volta a fixar o sensor na altura escolhida.

```text
Pressionar laterais
        ↓
Trava destrava
        ↓
Extensor pode se mover
        ↓
Soltar laterais
        ↓
Trava fixa a nova posição
```

Esse mecanismo permite ajustar a altura do sensor sem depender de ferramentas externas.

!!! note "Travamento do sensor"
Antes de iniciar a coleta, verifique se o extensor está corretamente travado. Movimentos do sensor durante o experimento podem introduzir erro na leitura da posição.

---

## Posicionamento do sensor

O sensor deve ficar apontado para a massa oscilante, de modo que sua leitura represente a distância entre a caixa e o alvo.

Um bom posicionamento deve garantir que:

* o sensor esteja alinhado com a trajetória da massa;
* a massa permaneça dentro da faixa útil de leitura;
* não existam obstáculos entre sensor e massa;
* a estrutura permaneça fixa durante a coleta;
* o extensor esteja travado;
* a superfície detectada seja adequada para reflexão infravermelha.

O ajuste mecânico do sensor é essencial para a qualidade dos dados experimentais.

---

## Integração entre mecânica e eletrônica

A estrutura mecânica foi projetada para integrar os componentes eletrônicos de forma funcional.

| Elemento mecânico   | Componente associado   |
| ------------------- | ---------------------- |
| região inclinada    | LCD 16x2 I2C           |
| aberturas frontais  | botões físicos         |
| extensor vertical   | sensor infravermelho   |
| corpo interno       | ESP32 e conexões       |
| tampa ou fechamento | proteção dos circuitos |

Essa integração evita que a eletrônica fique exposta ou mal posicionada durante o experimento.

---

## Relação com a aquisição de dados

A qualidade da aquisição depende também da estabilidade mecânica da caixa.

Se o sensor se movimentar durante a coleta, a distância medida pode mudar mesmo que a massa não tenha se deslocado da forma esperada.

Por isso, a estrutura deve garantir:

* rigidez suficiente;
* fixação adequada do sensor;
* estabilidade sobre a bancada;
* alinhamento com a massa;
* acesso aos comandos sem deslocar a caixa.

A estrutura 3D contribui diretamente para a reprodutibilidade do experimento.

---

## Uso didático

O projeto mecânico também foi pensado para facilitar o uso em laboratório didático.

A caixa deve permitir que o usuário:

* entenda visualmente a função de cada parte;
* acesse rapidamente os botões;
* visualize o LCD com facilidade;
* ajuste a posição do sensor;
* monte o sistema sem ferramentas complexas;
* transporte o equipamento com segurança.

Essa organização torna o Spring-Mass Collector mais prático para atividades experimentais envolvendo estudantes.

---

## Requisitos mecânicos principais

Os principais requisitos mecânicos da estrutura são:

| Requisito                  | Justificativa                             |
| -------------------------- | ----------------------------------------- |
| estabilidade               | evita movimento da caixa durante a coleta |
| acesso aos botões          | permite operação direta do sistema        |
| boa visualização do LCD    | facilita acompanhamento do experimento    |
| ajuste de altura do sensor | adapta o sistema a diferentes montagens   |
| proteção dos componentes   | reduz exposição da eletrônica             |
| montagem simples           | facilita reprodução do projeto            |
| baixo custo                | mantém o caráter didático e acessível     |

---

## Resumo

O projeto mecânico do Spring-Mass Collector organiza fisicamente os componentes e melhora a usabilidade do sistema durante o experimento.

```text
Mechanical Design
├── Corpo principal da caixa
│   └── acomoda ESP32 e conexões
│
├── Região inclinada do LCD
│   └── melhora visualização da interface
│
├── Aberturas para botões
│   └── permitem controle dos modos
│
└── Extensor vertical do sensor
    ├── ajusta a altura em até três níveis
    └── usa trava mecânica lateral
```

Essa estrutura permite que o sistema funcione como um equipamento compacto de aquisição de dados, integrando eletrônica, interface e posicionamento experimental em uma única caixa.
