# Assembly

A montagem do **Spring-Mass Collector** integra as peças impressas em 3D, os componentes eletrônicos e a organização interna da fiação. O objetivo desta etapa é transformar os módulos individuais em um equipamento funcional para aquisição de dados em experimentos massa-mola.

Esta página apresenta uma sequência geral de montagem, destacando os cuidados necessários para instalar o LCD, os botões, a ESP32, o sensor infravermelho e o extensor vertical.

---

## Visão geral da montagem

A montagem pode ser dividida em cinco etapas principais:

```text
Preparar as peças impressas
        ↓
Instalar LCD e botões
        ↓
Instalar ESP32 e organizar conexões
        ↓
Montar sensor e extensor vertical
        ↓
Realizar testes antes do fechamento
```

Essa sequência evita que a caixa seja fechada antes da verificação dos encaixes, conexões e funcionamento básico dos componentes.

---

## Preparação das peças impressas

Antes de inserir os componentes eletrônicos, verifique a qualidade das peças impressas.

Recomenda-se:

* remover suportes de impressão;
* retirar rebarbas;
* testar o encaixe das peças móveis;
* verificar se o extensor desliza corretamente;
* confirmar se a trava mecânica fixa o extensor;
* testar se o LCD encaixa na região inclinada;
* verificar se os botões entram nas aberturas frontais.

Essa verificação inicial reduz o risco de danificar componentes eletrônicos durante a montagem.

---

## Instalação do LCD 16x2

O display **LCD 16x2 I2C** deve ser instalado na região inclinada da caixa.

Essa região possui inclinação aproximada de:

```text
30 graus
```

A inclinação melhora a visualização da tela durante o uso em bancada.

Durante a instalação, verifique:

* se o LCD está alinhado com a abertura;
* se a tela fica visível pela parte externa;
* se o módulo I2C não pressiona outros componentes;
* se os fios de alimentação e comunicação ficam livres;
* se o encaixe não força a placa do display.

<figure markdown>
  ![Instalação do LCD](../assets/lcd-installation.png){ width="700" }
  <figcaption>Região de instalação do display LCD 16x2 na parte inclinada da estrutura.</figcaption>
</figure>

!!! note "Imagem da montagem"
Substitua a imagem acima por uma foto ou render da instalação real do LCD quando o arquivo final estiver disponível.

---

## Instalação dos botões

Os três botões físicos devem ser instalados nas aberturas frontais da caixa.

Eles são responsáveis pela navegação entre os modos de operação:

| Botão | Função geral                |
| ----- | --------------------------- |
| B1    | primeira ação do modo atual |
| B2    | segunda ação do modo atual  |
| B3    | terceira ação do modo atual |

Durante a montagem, verifique se:

* os botões ficam acessíveis pela parte externa;
* o acionamento ocorre sem travamento;
* os botões não ficam frouxos;
* os fios não impedem o movimento mecânico;
* cada botão está ligado ao pino correto da ESP32.

No firmware atual, os pinos dos botões são:

```cpp
const uint8_t buttonPins[BUTTON_QTD] = {
  25,
  33,
  32
};
```

A ligação elétrica considerada é:

```text
GPIO ---- botão ---- GND
```

Como os pinos usam `INPUT_PULLUP`, o botão pressionado corresponde a `LOW`.

---

## Instalação da ESP32

A ESP32 deve ser posicionada no interior do corpo principal da caixa.

O posicionamento deve permitir:

* acesso à porta USB, se necessário;
* organização dos cabos internos;
* afastamento de regiões móveis do extensor;
* fixação segura durante o uso;
* manutenção ou substituição futura.

A ESP32 é o centro de conexão do sistema. Ela recebe o sensor, os botões, o LCD e controla a comunicação Bluetooth.

```text
ESP32
├── Sensor infravermelho
├── LCD 16x2 I2C
├── Botões físicos
└── Bluetooth integrado
```

!!! warning "Curto-circuito"
Evite contato direto entre terminais expostos. Antes de ligar o sistema, verifique se não há fios soltos ou conexões encostando em regiões condutivas.

---

## Organização da fiação

A organização interna da fiação é importante para evitar mau contato, interferência mecânica e dificuldade de manutenção.

Recomenda-se separar os fios por função:

| Grupo       | Fios associados                        |
| ----------- | -------------------------------------- |
| Alimentação | VCC e GND dos módulos                  |
| Sensor      | alimentação, GND e saída analógica     |
| LCD         | VCC, GND, SDA e SCL                    |
| Botões      | GPIOs e GND                            |
| USB         | acesso para programação ou alimentação |

Os fios devem ser organizados de forma que:

* não pressionem os botões;
* não travem o movimento do extensor;
* não fiquem tensionados;
* não dificultem o fechamento da caixa;
* não se soltem durante o uso.

---

## Montagem do sensor infravermelho

O sensor infravermelho deve ser instalado no suporte associado ao extensor vertical.

A posição do sensor deve permitir que ele fique apontado diretamente para a massa oscilante.

Durante a instalação, verifique:

* se o sensor está firme;
* se a saída óptica não está obstruída;
* se os fios acompanham o movimento do extensor;
* se o sensor não se desloca ao ajustar a altura;
* se o alinhamento com a massa pode ser ajustado.

O sensor deve permanecer fixo durante a coleta. Qualquer movimento do sensor pode aparecer nos dados como uma falsa variação da posição da massa.

---

## Montagem do extensor vertical

O extensor vertical permite ajustar a altura do sensor em até três níveis.

Para verificar o funcionamento:

```text
1. Pressione simultaneamente as laterais do mecanismo.
2. Desloque o extensor para outro nível.
3. Solte as laterais.
4. Verifique se a trava fixou a posição.
```

O movimento deve ser possível apenas quando as laterais estiverem pressionadas. Após soltar, o extensor deve permanecer travado.

!!! warning "Extensor solto"
Não inicie a coleta se o extensor estiver frouxo ou parcialmente encaixado. O movimento do sensor durante a aquisição compromete a confiabilidade dos dados.

---

## Conexões principais

Antes do fechamento da caixa, revise as conexões principais.

| Elemento   | Conexão com a ESP32         |
| ---------- | --------------------------- |
| Sensor OUT | GPIO 39                     |
| Botão B1   | GPIO 25                     |
| Botão B2   | GPIO 33                     |
| Botão B3   | GPIO 32                     |
| LCD SDA    | GPIO 21                     |
| LCD SCL    | GPIO 22                     |
| GND        | comum para todos os módulos |

Todos os componentes devem compartilhar o mesmo GND.

```text
GND da ESP32
├── GND do sensor
├── GND do LCD
└── GND dos botões
```

---

## Testes antes do fechamento

Antes de fechar a caixa, realize testes básicos de funcionamento.

| Teste         | Verificação esperada                             |
| ------------- | ------------------------------------------------ |
| Inicialização | LCD mostra a tela inicial ou menu principal      |
| Botão B1      | acessa ou controla a primeira ação do modo atual |
| Botão B2      | acessa ou controla a segunda ação do modo atual  |
| Botão B3      | acessa ou controla a terceira ação do modo atual |
| Sensor        | leitura varia ao mudar a distância do alvo       |
| Bluetooth     | dispositivo `MassaMolaEsp32` aparece no celular  |
| Extensor      | sensor fica travado na altura escolhida          |

Esses testes ajudam a identificar erros antes da montagem final.

---

## Fechamento da caixa

Depois de verificar os encaixes, conexões e testes básicos, a caixa pode ser fechada.

Antes do fechamento, confirme:

* se nenhum fio está sendo esmagado;
* se a ESP32 está fixa;
* se o LCD está alinhado;
* se os botões funcionam livremente;
* se o extensor ainda se move e trava corretamente;
* se a porta USB permanece acessível, caso necessário;
* se o sensor está corretamente posicionado.

O fechamento deve proteger os componentes sem dificultar manutenção futura.

---

## Verificação final

Após o fechamento da caixa, realize uma verificação completa.

```text
1. Ligue o sistema.
2. Confirme a tela inicial no LCD.
3. Teste os três botões.
4. Entre no modo de calibração.
5. Verifique a leitura do sensor.
6. Inicie uma coleta curta.
7. Entre no modo de transferência.
8. Conecte ao Bluetooth.
9. Envie os dados.
10. Verifique se o arquivo .csv pode ser salvo.
```

Essa verificação confirma se a montagem mecânica, elétrica e lógica está funcionando de forma integrada.

---

## Cuidados de montagem

Durante a montagem, evite:

* forçar o encaixe do LCD;
* dobrar excessivamente os fios;
* deixar o sensor frouxo;
* fechar a caixa com cabos pressionados;
* inverter alimentação de módulos;
* deixar terminais expostos em contato;
* usar o extensor sem testar a trava;
* iniciar coleta sem conferir o alinhamento do sensor.

Esses cuidados reduzem falhas elétricas, mecânicas e experimentais.

---

## Resumo

A montagem do Spring-Mass Collector integra estrutura 3D, eletrônica e firmware.

```text
Assembly
├── Preparação das peças impressas
├── Instalação do LCD
├── Instalação dos botões
├── Fixação da ESP32
├── Organização da fiação
├── Montagem do sensor
├── Teste do extensor
├── Verificação elétrica
└── Fechamento da caixa
```

Com a montagem concluída, o sistema fica pronto para calibração, coleta de dados e transferência Bluetooth em experimentos massa-mola.
