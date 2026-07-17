# Requirements

Esta página reúne os materiais, as ferramentas e a infraestrutura necessários para construir o Spring-Mass Collector.

---

## Componentes eletrônicos

| Componente                      |          Quantidade |
| ------------------------------- | ------------------: |
| ESP32 DevKit de 30 pinos        |                   1 |
| Sensor Sharp GP2Y0A41SK0F       |                   1 |
| Cabo de conexão do sensor       |                   1 |
| Display LCD 16×2 com I²C        |                   1 |
| Botões de pressão               |                   3 |
| Fios ou cabos jumper            | conforme necessário |
| Placa de prototipagem perfurada |                   1 |
| Cabo USB de dados               |                   1 |

---

## Peças impressas em 3D

| Peça                  | Quantidade |
| --------------------- | ---------: |
| Caixa principal       |          1 |
| Tampa inferior        |          1 |
| Suporte base          |          1 |
| Suporte intermediário |          1 |
| Suporte superior      |          1 |
| Suporte do sensor     |          1 |
| Disco refletor        |          1 |

Para a fabricação, é necessário um rolo de filamento compatível com impressão FDM, preferencialmente PLA.

---

## Elementos de fixação

| Material                              | Quantidade |
| ------------------------------------- | ---------: |
| Insertos roscados M3                  |          4 |
| Parafusos M3 para a tampa             |          4 |
| Insertos roscados M2                  |          2 |
| Parafusos M2 para o suporte do sensor |          2 |
| Parafusos para o display LCD          |          4 |

O comprimento dos parafusos deve ser compatível com a espessura das peças e com a profundidade dos insertos.

---

## Materiais auxiliares

* estanho para soldagem;
* fita isolante ou tubo termo-retrátil;
* fita dupla face;
* abraçadeiras plásticas;
* conectores para fios;
* material refletivo para o disco;
* lixa fina.

---

## Ferramentas

* ferro de solda;
* multímetro;
* chave para parafusos M2 e M3;
* alicate de corte;
* alicate desencapador;
* pinça;
* estilete;
* lima ou lixa;
* paquímetro.

---

## Infraestrutura

* impressora 3D FDM;
* computador com porta USB;
* programa de fatiamento;
* Arduino IDE com suporte à ESP32;
* smartphone ou computador com terminal Bluetooth Serial;
* bancada para montagem;
* estrutura para o experimento massa-mola;
* mola, suporte e conjunto de massas.

!!! note "Cabo USB"
O cabo USB deve permitir transmissão de dados. Cabos destinados apenas à alimentação não podem ser utilizados para carregar o firmware.

---

## Verificação inicial

Antes da montagem, confirme que:

* todas as peças foram impressas;
* os parafusos são compatíveis com os insertos;
* a ESP32 é reconhecida pelo computador;
* o display possui interface I²C;
* o sensor acompanha o cabo de conexão;
* as travas mecânicas não apresentam trincas;
* as ferramentas estão disponíveis.