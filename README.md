# biosensor-pcb

Desenvolvimento de um circuito impresso com comunicação NFC que realiza voltametria e cronoamperometria cíclica em eletrodos impressos com aplicações em biossensores amperométricos.

## :books: Metodologia 

O software Kicad será utilizado para a confecção das placas de circuito impresso, sendo que a primeira PCB confeccionada será para testes do código e ruído envolvido na amostragem. A placa teste em questão está com seus arquivos no diretório `./placa-teste`. A placa teste projetada está ilustrada na figura abaixo:

<p align="center">
<img src="https://github.com/LCrozatti/biosensor-pcb/blob/master/placa-teste/images/pcb1.png" alt="pcb" width="400"/>
</p>

O primeiro firmware envolvido foi feito com base no código produzido pelo [Linnes Lab](https://github.com/LinnesLab/LMP91000). De início será utilizado um microcontrolador ATmega168PA-MU para o controle do potenciostato.

### :hammer: Ferramentas envolvidas

[<img align="left" alt="Kicad" height="28px" src="https://user-images.githubusercontent.com/352202/53980744-60746100-4111-11e9-9f8c-17ca6b50efd8.png"/>](https://www.kicad.org/)

[<img align="left" alt="C" height="28px" src="https://cdn.iconscout.com/icon/free/png-512/c-programming-569564.png"/>]()

[<img align="left" alt="Python" height="28px" src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/c3/Python-logo-notext.svg/1200px-Python-logo-notext.svg.png"/>](https://www.python.org/)

[<img align="left" alt="Jupyter" height="28px" src="https://upload.wikimedia.org/wikipedia/commons/thumb/3/38/Jupyter_logo.svg/1200px-Jupyter_logo.svg.png"/>](https://jupyter.org/)

[<img align="left" alt="Numpy" height="28px" src="https://cdn.worldvectorlogo.com/logos/numpy.svg"/>](https://numpy.org/)

[<img align="left" alt="Pandas" height="28px" src="https://upload.wikimedia.org/wikipedia/commons/thumb/2/22/Pandas_mark.svg/1200px-Pandas_mark.svg.png"/>](https://pandas.pydata.org/)

[<img align="left" alt="Matplotlib" height="28px" src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/01/Created_with_Matplotlib-logo.svg/1024px-Created_with_Matplotlib-logo.svg.png"/>](https://numpy.org/)

<br />

### :test_tube: Análise dos dados 

Os dados serão analisados utilizando a linguagem python, o arquivo `./placa-teste/amostragem/eletroquimica.ipynb` contém algumas demonstrações sobre o uso do python em operações de voltametria cíclica e cronoamperometria. O *dataset* utilizado nesse arquivo pode ser acesso no [kaggle](https://ieee-dataport.org/documents/supplementary-material-optimized-sampling-rate-voltammetry-based-electrochemical-sensing).

![Image of Yaktocat](https://github.com/LCrozatti/biosensor-pcb/blob/master/placa-teste/images/amostragem.png)

![Image of Yaktocat](https://github.com/LCrozatti/biosensor-pcb/blob/master/placa-teste/images/amostragem1.png)

### :dart: Protótipo final 

A placa final terá uma antena controlada pelo *transponder* ST25DV04K, o controle será efetuado pelo microcontrolador STM32L0 e o controle de tensão nos eletrodos será dados através do potenciostato programável LMP91000. O principal estudo nessa fase é a possibilidade de *energy harvesting*, caminhando em um circuito sem alimentação externa.

### :iphone: Aplicativo

O aplicativo em questão será construído utilizando o *framework* React-Native, juntamente com a biblioteca [react-native-nfc-manager](https://github.com/whitedogg13/react-native-nfc-manager). O seu início já foi dado com alguns testes de leitura.

<p align="center">
<img src="https://github.com/LCrozatti/biosensor-pcb/blob/master/aplicativo/images/inicio.jpeg" alt="pcb" width="150"/>
</p>

## :hourglass: Linha do Tempo

### 06/06/2021

O repositório foi criado e atualizado com os dados da placa teste.

## Referências

[1] S. Aiassa, S. Carrara and D. Demarchi, "Optimized Sampling Rate for Voltammetry-Based Electrochemical Sensing in Wearable and IoT Applications," in IEEE Sensors Letters. doi: 10.1109/LSENS.2019.2918575.

## Instituições envolvidas

Fundação Araucária  |  UEM       |     CNPq
:----------:|:----------:|:----------:|
<img src="http://www.aintec.com.br/wp-content/uploads/2015/02/araucaria.jpg" alt="Araucaria" width="200"/> | <img src="https://marcoadp.github.io/WebSiteDIN/img/logo-uem2.svg" alt="UEM" width="200"/> | <img src="https://www.gov.br/cnpq/pt-br/canais_atendimento/identidade-visual/logo_cnpq.svg" alt="CNPq" width="200"/>
