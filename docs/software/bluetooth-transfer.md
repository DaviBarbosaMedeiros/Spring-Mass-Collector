# Bluetooth Transfer

A transferência dos dados no **Spring-Mass Collector** é feita por comunicação Bluetooth. Essa etapa permite enviar os dados armazenados na ESP32 para um dispositivo externo, como um celular ou computador, para posterior salvamento e análise.

Nos testes do projeto, foi utilizado o aplicativo **Serial Bluetooth Terminal**. Apesar disso, o sistema pode ser usado com outros aplicativos ou programas compatíveis com comunicação Bluetooth Serial.

---

## Função da transferência

Após a coleta, os dados permanecem armazenados temporariamente na memória da ESP32. Para que esses dados possam ser analisados externamente, é necessário transferi-los para outro dispositivo.

O fluxo geral é:

```text
Dados armazenados na ESP32
        ↓
Modo de transferência
        ↓
Envio por Bluetooth Serial
        ↓
Recebimento no terminal Bluetooth
        ↓
Salvamento em arquivo .csv
        ↓
Análise externa
```

Essa estratégia torna o sistema independente de conexão USB durante o uso experimental e facilita sua aplicação em laboratório didático.

---

## Comunicação Bluetooth na ESP32

A ESP32 possui suporte integrado à comunicação Bluetooth. No firmware do Spring-Mass Collector, a transferência é feita usando Bluetooth Serial.

No código, essa comunicação é representada por:

```cpp
BluetoothSerial SerialBT;
```

Durante a inicialização, a ESP32 configura o nome do dispositivo Bluetooth. Na versão atual do firmware, o dispositivo deve aparecer como:

```text
MassaMolaEsp32
```

Esse é o nome que deve ser procurado no celular durante o pareamento e também dentro do aplicativo de terminal Bluetooth.

---

## Aplicativo utilizado nos testes

O aplicativo usado como referência durante os testes foi o **Serial Bluetooth Terminal**.

Ele permite:

* conectar o celular à ESP32 por Bluetooth;
* visualizar os dados enviados pelo firmware;
* receber a saída em formato textual;
* salvar os dados recebidos em arquivo;
* reutilizar os dados posteriormente em softwares de análise.

O aplicativo deve ser configurado antes da primeira coleta para evitar perda de dados durante a transferência.

---

## Configuração recomendada do Serial Bluetooth Terminal

Antes de transferir os dados, recomenda-se ajustar algumas configurações do aplicativo.

Ao abrir o **Serial Bluetooth Terminal**, acesse o menu lateral pelo ícone de três linhas no canto superior esquerdo.

Em seguida, entre em:

```text
Settings
```

---

## Configuração do terminal

Dentro das configurações, acesse a aba:

```text
Terminal
```

Nessa aba, localize a opção:

```text
Buffer size
```

Recomenda-se definir essa opção como:

```text
Unlimited
```

Essa configuração evita problemas em transferências maiores, nas quais o aplicativo poderia limitar a quantidade de dados exibidos ou recebidos.

Ainda na aba **Terminal**, verifique a opção:

```text
Show Timestamps
```

Essa opção deve ficar desabilitada.

Caso ela esteja habilitada, o aplicativo pode adicionar marcações de tempo próprias em cada linha recebida, modificando o formato dos dados enviados pela ESP32.

O formato correto esperado é:

```text
t_ms,pos_cm
25,0.0123
50,0.0181
75,0.0204
END
```

Com `Show Timestamps` habilitado, esse formato pode ser alterado, dificultando a importação dos dados em programas de análise.

---

## Configuração da pasta de salvamento

Ainda dentro de **Settings**, acesse a aba:

```text
Misc.
```

Nessa aba, localize a opção:

```text
Save + log folder
```

Defina uma pasta para receber os arquivos salvos pelo aplicativo.

Essa pasta será usada posteriormente quando os dados recebidos forem salvos manualmente pela opção **Save**.

Essa configuração é importante porque permite saber exatamente onde o arquivo `.csv` será armazenado no dispositivo móvel.

---

## Conexão Bluetooth com a ESP32

Antes de usar o aplicativo, é necessário conectar o dispositivo móvel à ESP32 pelo Bluetooth do próprio sistema.

O procedimento recomendado é:

```text
1. Ligar o Spring-Mass Collector.
2. Ativar o Bluetooth no celular.
3. Procurar pelo dispositivo MassaMolaEsp32.
4. Realizar o pareamento Bluetooth.
5. Abrir o aplicativo Serial Bluetooth Terminal.
```

Depois de parear a ESP32 com o celular, abra o aplicativo e acesse o menu lateral pelo ícone de três linhas no canto superior esquerdo.

Em seguida, entre em:

```text
Devices
```

Selecione o dispositivo:

```text
MassaMolaEsp32
```

Após a conexão, uma mensagem deve aparecer no terminal indicando que o dispositivo foi conectado.

---

## Reconexão no aplicativo

Depois que o dispositivo já foi selecionado anteriormente, o aplicativo pode permitir a reconexão de forma mais rápida.

Na parte superior da tela principal existe um ícone de conexão, localizado próximo ao ícone de lixeira.

Ao pressionar esse ícone, o aplicativo tenta reconectar ao dispositivo Bluetooth previamente selecionado.

Quando a conexão for estabelecida, o terminal deve exibir uma mensagem informando que o dispositivo está conectado.

---

## Modo de transferência na caixa

A transferência é realizada a partir do modo **Transferência** do Spring-Mass Collector.

No menu principal da caixa, o usuário acessa esse modo pressionando **B3**.

Uma tela típica no LCD é:

```text
Modo Transfer
D: 120 M:5000
```

onde:

| Campo | Significado                                |
| ----- | ------------------------------------------ |
| `D`   | quantidade de dados atualmente armazenados |
| `M`   | limite máximo de dados configurado         |

Nesse modo, a caixa não realiza nova coleta. Ela apenas informa a quantidade de dados disponíveis e aguarda o comando do usuário para iniciar o envio.

---

## Função dos botões no modo de transferência

No modo de transferência, os botões possuem as seguintes funções:

| Botão | Função                                 |
| ----- | -------------------------------------- |
| B1    | enviar os dados por Bluetooth e Serial |
| B2    | voltar ao modo Default                 |
| B3    | alterar a quantidade máxima de dados   |

O envio dos dados é iniciado quando o usuário pressiona **B1**.

Durante a transmissão, o LCD pode mostrar:

```text
Transferindo
Aguarde...
```

Ao final do envio, o sistema retorna para a tela do modo de transferência.

---

## Formato dos dados enviados

Os dados são enviados em formato textual, usando uma estrutura semelhante a CSV.

O cabeçalho enviado é:

```text
t_ms,pos_cm
```

Cada linha seguinte contém um par de tempo e posição:

```text
25,0.0123
50,0.0181
75,0.0204
100,0.0195
```

Ao final da transmissão, o sistema envia:

```text
END
```

Um exemplo completo de transmissão é:

```text
t_ms,pos_cm
25,0.0123
50,0.0181
75,0.0204
100,0.0195
END
```

!!! note "Formato CSV"
Como os valores são separados por vírgula, recomenda-se salvar os dados com a extensão `.csv`. Isso facilita a importação em planilhas e softwares de análise.

---

## Significado das colunas

| Coluna   | Unidade | Descrição                                                   |
| -------- | ------- | ----------------------------------------------------------- |
| `t_ms`   | ms      | tempo em milissegundos desde o início da coleta             |
| `pos_cm` | cm      | posição relativa da massa em relação à referência calibrada |

A posição enviada não é a distância absoluta entre o sensor e a massa. Ela corresponde ao deslocamento relativo calculado a partir da calibração inicial:

$$
x_{rel}(t) = x(t) - x_0
$$

Assim, os dados transferidos já estão no formato adequado para construção de gráficos de posição em função do tempo.

---

## Salvamento dos dados no aplicativo

Após receber os dados no **Serial Bluetooth Terminal**, eles devem ser salvos manualmente.

Na tela principal do aplicativo, após a transferência ser finalizada, pressione o menu de três pontos no canto superior direito.

Em seguida, acesse:

```text
Data
```

Depois selecione:

```text
Save
```

Os dados serão salvos na pasta definida anteriormente em:

```text
Settings → Misc. → Save + log folder
```

Recomenda-se salvar o arquivo com a extensão `.csv`, pois os dados já são enviados em uma estrutura separada por vírgulas.

Um nome recomendado para o arquivo é:

```text
spring_mass_data.csv
```

O arquivo salvo poderá ser utilizado posteriormente para análise dos dados experimentais em Python, Excel, MATLAB, Mathematica, Origin ou softwares equivalentes.

---

## Verificação da transferência

Uma transferência correta deve conter três partes:

```text
1. Cabeçalho t_ms,pos_cm
2. Linhas com pares tempo, posição
3. Palavra END no final
```

A presença da palavra `END` é importante porque indica que a transmissão foi concluída.

Se a palavra `END` não aparecer, a transferência pode ter sido interrompida antes do fim. Nesse caso, recomenda-se repetir o envio sem apagar os dados armazenados.

---

## Uso dos dados em análise externa

Depois de salvos, os dados podem ser utilizados para construir gráficos e realizar ajustes.

O gráfico mais direto é:

```text
posição relativa × tempo
```

A série coletada representa:

$$
x_{rel}(t)
$$

A partir dela, é possível estudar características do movimento, como:

* período de oscilação;
* frequência;
* amplitude;
* decaimento da amplitude;
* comportamento amortecido;
* comparação com modelos teóricos.

Um modelo típico para comparação é:

$$
x(t) = A e^{-\gamma t}\cos(\omega_d t + \phi)
$$

O Spring-Mass Collector não realiza automaticamente esse ajuste. A função da transferência é disponibilizar os dados em um formato simples para análise externa.

---

## Envio por Serial e Bluetooth

Durante a transferência, o firmware pode enviar os dados tanto pela comunicação Bluetooth quanto pela Serial USB.

Essa duplicação é útil durante o desenvolvimento porque permite verificar a saída também pelo monitor serial da Arduino IDE.

De forma conceitual, o envio segue a lógica:

```text
Buffer de dados
        ↓
Impressão do cabeçalho
        ↓
Envio dos pares tempo, posição
        ↓
Envio da marca END
```

No uso experimental comum, o caminho principal é o Bluetooth. A saída Serial é mais útil para depuração e testes de firmware.

---

## Quantidade de dados transferidos

A quantidade de dados enviados depende do número de pontos armazenados durante a coleta.

No modo de transferência, o LCD mostra:

```text
D: 120 M:5000
```

Nesse exemplo, `D = 120` indica que existem 120 pontos armazenados. Ao pressionar **B1**, esses 120 pontos são enviados.

O valor `M` indica o limite máximo de pontos configurado para a coleta. Esse limite pode ser alterado pelo usuário pressionando **B3** no modo de transferência.

Um ciclo possível de configuração é:

```text
500 → 1000 → 2000 → 3000 → 5000 → 500
```

Essa configuração permite ajustar o tamanho da coleta conforme a necessidade do experimento.

---

## Cuidados durante a transferência

Durante a transferência, recomenda-se:

* manter o dispositivo receptor próximo da caixa;
* configurar `Buffer size` como `Unlimited`;
* desabilitar `Show Timestamps`;
* definir previamente a pasta em `Save + log folder`;
* não sair da tela do terminal antes do fim da transmissão;
* aguardar a palavra `END`;
* salvar os dados com extensão `.csv`;
* salvar os dados antes de iniciar uma nova coleta;
* verificar se o número de linhas recebidas é compatível com a quantidade de dados indicada no LCD.

!!! warning "Preservação dos dados"
Ao iniciar uma nova coleta ou resetar o buffer, os dados anteriores podem ser apagados. Transfira e salve os dados antes de reiniciar o experimento.

---

## Possíveis problemas

| Problema                             | Possível causa                                                      | Ação recomendada                                            |
| ------------------------------------ | ------------------------------------------------------------------- | ----------------------------------------------------------- |
| dispositivo não aparece no Bluetooth | ESP32 desligada, Bluetooth não inicializado ou dispositivo distante | reiniciar a caixa e aproximar o celular                     |
| conexão falha                        | pareamento incompleto                                               | remover pareamento antigo e conectar novamente              |
| dados incompletos                    | buffer do aplicativo limitado ou terminal fechado antes do fim      | configurar `Buffer size` como `Unlimited` e repetir o envio |
| linhas com horários extras           | opção `Show Timestamps` ativada                                     | desabilitar `Show Timestamps` nas configurações             |
| arquivo não encontrado               | pasta de salvamento não definida                                    | configurar `Save + log folder` em `Settings → Misc.`        |
| dados não salvos                     | saída recebida, mas `Save` não foi executado                        | acessar `Data → Save` após a transferência                  |
| arquivo não abre como tabela         | arquivo salvo com extensão inadequada                               | salvar ou renomear o arquivo com extensão `.csv`            |

---

## Resumo

A transferência Bluetooth permite que o Spring-Mass Collector envie os dados coletados para análise externa sem depender de conexão USB durante o experimento.

O processo recomendado é:

```text
1. Configurar Buffer size como Unlimited.
2. Desabilitar Show Timestamps.
3. Definir a pasta em Save + log folder.
4. Parear o celular com MassaMolaEsp32.
5. Selecionar MassaMolaEsp32 em Devices.
6. Entrar no modo Transferência na caixa.
7. Pressionar B1 para enviar os dados.
8. Aguardar a palavra END.
9. Acessar Data → Save.
10. Salvar o arquivo com extensão .csv.
```

Com essa etapa, os dados experimentais ficam disponíveis para tratamento computacional, construção de gráficos e comparação com modelos físicos de oscilação amortecida.
