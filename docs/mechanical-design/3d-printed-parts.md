# 3D Printed Parts

As peças impressas em 3D do **Spring-Mass Collector** formam a estrutura física responsável por acomodar os componentes eletrônicos, posicionar o display LCD 16x2, organizar os botões e permitir o ajuste de altura do sensor infravermelho.

A impressão 3D foi escolhida por permitir baixo custo, reprodução simples, ajustes rápidos no projeto e adaptação da estrutura às necessidades do experimento massa-mola.

---

## Função das peças impressas

As peças impressas transformam o circuito eletrônico em um equipamento físico utilizável em laboratório didático.

Elas possuem três funções principais:

```text
Organizar os componentes eletrônicos
        ↓
Facilitar a operação do sistema
        ↓
Permitir o posicionamento adequado do sensor
```

---

## Conjunto de peças

O conjunto mecânico pode ser organizado em quatro grupos principais:

| Grupo              | Função                                          |
| ------------------ | ----------------------------------------------- |
| Corpo principal    | acomoda a eletrônica e serve como base da caixa |
| Região do LCD      | posiciona o display em uma área inclinada       |
| Extensor do sensor | permite ajuste vertical do sensor infravermelho |
| Sistema de trava   | fixa o extensor na altura escolhida             |

Esses elementos trabalham em conjunto para manter a caixa estável, funcional e adaptável ao experimento.

---

## Corpo principal

O corpo principal é a maior peça da estrutura. Ele funciona como base do sistema e acomoda os principais elementos eletrônicos.

Essa região deve permitir:

* acomodação da ESP32;
* organização da fiação interna;
* passagem dos cabos do sensor, LCD e botões;
* estabilidade sobre a bancada;
* acesso para montagem e manutenção.

```text
Corpo principal
├── espaço interno para eletrônica
├── região frontal para interface
├── suporte para o extensor
└── base de apoio
```

---

## Região do LCD e botões

A região frontal da estrutura foi projetada para receber o **LCD 16x2 I2C** e os três botões físicos.

O suporte do display possui inclinação aproximada de:

```text
30 graus
```

Essa inclinação melhora a leitura da tela quando a caixa está posicionada sobre uma bancada.

<figure markdown>
  ![Região inclinada para o LCD](../assets/lcd-angled-region.png){ width="700" }
  <figcaption>Região inclinada da estrutura destinada ao encaixe do display LCD 16x2.</figcaption>
</figure>

Os três botões ficam acessíveis ao usuário e permitem controlar os modos de operação do sistema. As aberturas devem permitir acionamento confortável, sem folgas excessivas ou travamentos mecânicos.

!!! note "Imagem da peça"
Substitua a imagem acima pelo render ou foto real correspondente à região do LCD quando o arquivo final estiver disponível.

---

## Extensor vertical do sensor

O extensor vertical é responsável por ajustar a altura do sensor infravermelho.

Esse ajuste é necessário porque a posição da massa pode variar de acordo com a montagem experimental. O extensor permite até três níveis de altura:

```text
Extensor do sensor
├── Nível 1
├── Nível 2
└── Nível 3
```

Com isso, a caixa pode ser adaptada a diferentes configurações do sistema massa-mola sem necessidade de suportes externos.

O suporte do sensor deve manter o sensor infravermelho apontado para a massa oscilante, com passagem organizada dos fios e estabilidade durante toda a coleta.

---

## Sistema de trava mecânica

O extensor vertical possui um sistema de trava mecânica acionado pelas laterais.

Para ajustar a altura do sensor, o usuário deve pressionar simultaneamente as laterais do mecanismo. Isso libera o movimento vertical do extensor. Ao soltar as laterais, a trava fixa novamente o extensor na posição escolhida.

```text
Pressionar as laterais
        ↓
Destravar o extensor
        ↓
Ajustar a altura do sensor
        ↓
Soltar as laterais
        ↓
Fixar o extensor
```

!!! warning "Antes da coleta"
Verifique se a trava mecânica está corretamente encaixada antes de iniciar a coleta. Se o extensor se mover durante o experimento, a leitura do sensor pode ser comprometida.

---

## Organização dos arquivos 3D

Os arquivos das peças impressas devem ser organizados de forma clara para facilitar a reprodução do projeto.

Uma estrutura recomendada é:

```text
mechanical-files/
├── stl/
│   ├── main-body.stl
│   ├── lcd-support.stl
│   ├── sensor-extender.stl
│   └── locking-system.stl
│
├── source/
│   └── editable-model-files
│
└── README.md
```

Os arquivos `.stl` são usados para impressão 3D. Os arquivos editáveis devem ser mantidos separadamente para permitir modificações futuras no modelo.

!!! note "Nomes dos arquivos"
Os nomes acima são sugestões de organização. Eles podem ser substituídos pelos nomes finais usados no projeto.

---

## Parâmetros de impressão

Os parâmetros de impressão podem variar de acordo com a impressora 3D, o material e a qualidade desejada.

Uma configuração inicial recomendada é:

| Parâmetro        | Valor sugerido                      |
| ---------------- | ----------------------------------- |
| Material         | PLA                                 |
| Altura de camada | 0,20 mm                             |
| Preenchimento    | 15% a 30%                           |
| Suporte          | conforme orientação da peça         |
| Borda ou brim    | opcional                            |
| Temperatura      | conforme especificação do filamento |

Esses valores servem como ponto de partida. A configuração final deve ser ajustada de acordo com a impressora utilizada e com o resultado obtido.

---

## Tolerâncias e encaixes

Como a estrutura possui encaixes, aberturas para botões e mecanismo de trava, as tolerâncias de impressão são importantes.

Alguns fatores que podem exigir ajuste são:

* precisão da impressora;
* folga entre peças móveis;
* diâmetro real dos botões;
* dimensões reais do LCD;
* dimensões reais do sensor;
* acabamento após a impressão.

Se uma peça ficar muito justa, pode ser necessário lixar levemente a região de encaixe ou ajustar o modelo original. Se ficar muito folgada, pode ser necessário corrigir as dimensões no arquivo editável.

---

## Montagem e verificação

Antes da integração final com a eletrônica, recomenda-se verificar o encaixe e o funcionamento das peças.

Uma sequência simples é:

```text
1. Remover suportes e rebarbas.
2. Testar o encaixe do LCD.
3. Testar o acionamento dos botões.
4. Testar o movimento do extensor.
5. Verificar o funcionamento da trava.
6. Inserir o sensor no suporte.
7. Organizar a fiação interna.
8. Fixar a ESP32 e demais componentes.
9. Realizar teste elétrico antes do fechamento.
```

A verificação deve confirmar:

| Item             | Verificação                            |
| ---------------- | -------------------------------------- |
| Corpo principal  | estabilidade e ausência de deformações |
| Região do LCD    | encaixe e ângulo de visualização       |
| Botões           | acionamento livre e sem travamento     |
| Extensor         | movimento vertical adequado            |
| Trava            | fixação firme após soltar as laterais  |
| Sensor           | alinhamento e firmeza                  |
| Passagem de fios | ausência de tensão nos cabos           |

---

## Relação com a qualidade dos dados

A estrutura impressa influencia diretamente a qualidade da coleta.

Se o sensor estiver desalinhado, solto ou vibrando, os dados podem apresentar ruídos que não correspondem ao movimento real da massa.

Por isso, a peça impressa deve garantir:

* sensor fixo;
* caixa estável;
* extensor travado;
* ausência de folgas excessivas;
* montagem firme sobre a bancada.

---

## Possíveis ajustes futuros

A estrutura 3D pode ser modificada em versões futuras para melhorar a usabilidade do equipamento.

Possíveis melhorias incluem:

* reforço do sistema de trava;
* melhoria no acesso aos botões;
* otimização da passagem de fios;
* adição de tampa ou fechamento traseiro;
* adaptação para outros sensores;
* redução do tempo de impressão;
* diminuição do consumo de material.

---

## Resumo

As peças impressas em 3D formam a estrutura física do Spring-Mass Collector.

```text
3D Printed Parts
├── Corpo principal
├── Região inclinada para o LCD
├── Aberturas para botões
├── Extensor vertical do sensor
├── Suporte do sensor infravermelho
└── Sistema de trava mecânica
```

Essas peças organizam a eletrônica, melhoram a operação do sistema, permitem ajuste de altura do sensor e tornam o equipamento mais adequado para uso em experimentos didáticos com sistema massa-mola.
