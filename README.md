# biosensor-pcb

Desenvolvimento de um circuito impresso com comunicação NFC que realiza voltametria e cronoamperometria cíclica em eletrodos impressos com aplicações em biossensores amperométricos.

## :books: Metodologia 

O software Kicad será utilizado para a confecção das placas de circuito impresso, sendo que a primeira PCB confeccionada será para testes do código e ruído envolvido na amostragem. A placa teste em questão está com seus arquivos no diretório `./placa-teste`. A placa teste projetada está ilustrada na figura abaixo:

<img src="https://github.com/LCrozatti/biosensor-pcb/blob/master/placa-teste/images/pcb1.png" alt="pcb" width="300"/>

O primeiro firmware envolvido foi feito com base no código produzido pelo [Linnes Lab](https://github.com/LinnesLab/LMP91000). De início será utilizado um microcontrolador ATmega168PA-MU para o controle do potenciostato.

### :test_tube: Análise dos dados 

Os dados serão analisados utilizando a linguagem python, o arquivo `./placa-teste/amostragem/demo.ipynb` contém algumas demonstrações sobre o uso do python em operações de voltametria cíclica e cronoamperometria.

### :dart: Protótipo final 

A placa final terá uma antena controlada pelo *transponder* ST25DV04K, o controle será efetuado pelo microcontrolador STM32L0 e o controle de tensão nos eletrodos será dados através do potenciostato programável LMP91000. O principal estudo nessa fase é a possibilidade de *energy harvesting*, caminhando em um circuito sem alimentação externa.

### :iphone: Aplicativo

<img src="https://github.com/LCrozatti/biosensor-pcb/blob/master/aplicativo/images/inicio.jpeg" alt="pcb" width="100"/>

O aplicativo em questão será construído utilizando o *framework* React-Native, juntamente com a biblioteca [react-native-nfc-manager](https://github.com/whitedogg13/react-native-nfc-manager). O seu início já foi dado com alguns testes de leitura.

## Linha do Tempo

### 06/06/2021

O repositório foi criado e atualizado com os dados da placa teste.

## Instituições envolvidas

Fundação Araucária  |  UEM       |     CNPq
:----------:|:----------:|:----------:|
<img src="http://www.aintec.com.br/wp-content/uploads/2015/02/araucaria.jpg" alt="Araucaria" width="200"/> | <img src="https://marcoadp.github.io/WebSiteDIN/img/logo-uem2.svg" alt="UEM" width="200"/> | <img src="https://www.gov.br/cnpq/pt-br/canais_atendimento/identidade-visual/logo_cnpq.svg" alt="CNPq" width="200"/>
