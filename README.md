# biosensor-pcb

Development of a printed circuit with NFC communication that performs cyclic voltammetry and chronoamperometry on printed electrodes with applications in amperometric biosensors.

## :books: Methodology

Kicad software will be used to make the printed circuit boards, and the first PCB made will be for testing the code and noise involved in the sampling. The test board in question has its files in the `./placa-teste` directory. The designed test board is illustrated in the figure below:

<p align="center">
<img src="https://github.com/LCrozatti/biosensor-pcb/blob/master/placa-teste/images/pcb1.png" alt="pcb" width="400"/>
</p>

The first firmware involved was made based on code produced by [Linnes Lab](https://github.com/LinnesLab/LMP91000). Initially, an ATmega168PA-MU microcontroller will be used to control the potentiostat.

### :hammer: Tools

[<img align="left" alt="Kicad" height="28px" src="https://user-images.githubusercontent.com/352202/53980744-60746100-4111-11e9-9f8c-17ca6b50efd8.png"/>](https://www.kicad.org/)

[<img align="left" alt="C" height="28px" src="https://cdn.iconscout.com/icon/free/png-512/c-programming-569564.png"/>]()

[<img align="left" alt="Python" height="28px" src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/c3/Python-logo-notext.svg/1200px-Python-logo-notext.svg.png"/>](https://www.python.org/)

[<img align="left" alt="Jupyter" height="28px" src="https://upload.wikimedia.org/wikipedia/commons/thumb/3/38/Jupyter_logo.svg/1200px-Jupyter_logo.svg.png"/>](https://jupyter.org/)

[<img align="left" alt="Numpy" height="28px" src="https://cdn.worldvectorlogo.com/logos/numpy.svg"/>](https://numpy.org/)

[<img align="left" alt="Pandas" height="28px" src="https://upload.wikimedia.org/wikipedia/commons/thumb/2/22/Pandas_mark.svg/1200px-Pandas_mark.svg.png"/>](https://pandas.pydata.org/)

[<img align="left" alt="Matplotlib" height="28px" src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/01/Created_with_Matplotlib-logo.svg/1024px-Created_with_Matplotlib-logo.svg.png"/>](https://numpy.org/)

<br />

### :test_tube: Data analysis

The data will be analyzed using the Python language, the file `./palca-teste/amostragem/eletroquimica.ipynb` contains some demonstrations on the use of python in cyclic voltammetry and chronoamperometry operations. The dataset used in this file can be accessed through the [IEEE Data Port](https://ieee-dataport.org/documents/supplementary-material-optimized-sampling-rate-voltammetry-based-electrochemical-sensing) [1].

<p align="center">
<img src="https://github.com/LCrozatti/biosensor-pcb/blob/master/placa-teste/images/amostragem.png" alt="Amostragem"/>
</p>

### :dart: Final prototype

The final board will have an antenna controlled by the *transponder* ST25DV64K, the control will be carried out by the microcontroller STM32L0 and the voltage control at the electrodes will be given through the programmable potentiostat LMP91000. The main study in this phase is the possibility of *energy harvesting*, leading to a circuit with low energy consumption.

### :iphone: App

The application in question will be built using the React-Native *framework*, along with the [react-native-nfc-manager](https://github.com/whitedogg13/react-native-nfc-manager) library. Its beginning has already been given with some reading tests..

<p align="center">
<img src="https://github.com/LCrozatti/biosensor-pcb/blob/master/aplicativo/images/inicio.jpeg" alt="pcb" width="150"/>
</p>

## :hourglass: Timeline

### 06/06/2021

The repository was created and updated with data from the test board.

### 13/09/2021

<p align="center">
<img src="https://github.com/LCrozatti/biosensor-pcb/blob/master/placa-teste/images/pcb_teste_frente.png" alt="placa_teste_frente" width="150"/>
</p>

The soldering of the components has been completed and now some tests are being done to confirm the code. There were some problems in the negative polarization part and I will now work on the IntZ variable to make this possible (67% Vref - when we work with negative polarization). So the positive bias is working and it is possible to do a "half" cyclic voltammetry.

<p align="center">
<img src="https://github.com/LCrozatti/biosensor-pcb/blob/master/placa-teste/images/osciloscopio_1.png" alt="osciloscopio_1" width="150"/>
</p>

### 12/10/2021

Another test was made and is possible to see that the potential between WE and RE is sweeping among -490 mV and 490 mV, demonstrating that the board is well functioning (24% of the reference voltage that is 2.048 V = 491,52 mV). Showing that the circuit can perform cyclic voltammetry in Potassium Ferrocyanide.

### 26/01/2022

The first PCB with NFC communication was developed, is being tested and the code of STM32L031G6U6 will be published here. To project the antenna, i used as a reference the Application note - AN2972 from ST Instruments and with some calculations the theoretic inductance obtained was 2.79 µH. Measuring with the help of a Handheld LCR Meter - UT612, the experimental inductance was 2.6 µH being an percent error of 7.3%.

<p align="center">
<img src="https://github.com/LCrozatti/biosensor-pcb/blob/master/placa-final/images/nfc_board.png" alt="nfc_board" width="150"/>
</p>

## References

[1] S. Aiassa, S. Carrara and D. Demarchi, "Optimized Sampling Rate for Voltammetry-Based Electrochemical Sensing in Wearable and IoT Applications," in IEEE Sensors Letters. doi: 10.1109/LSENS.2019.2918575.
