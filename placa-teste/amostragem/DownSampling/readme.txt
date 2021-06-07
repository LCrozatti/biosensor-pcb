%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   
%      Simone AIASSA                  
% Politecnico di Torino, Turin, Italy 
% EPFL, Lausanne, Switzerland         
%                          27.05.2019 
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


DISCLAIMER:
TO USE THIS DATA YOU HAVE TO CITE THE AUTHOR AS FOLLOW:

[] S. Aiassa, S. Carrara and D. Demarchi, "Optimized Sampling Rate for Voltammetry-Based Electrochemical Sensing in Wearable and IoT Applications," in IEEE Sensors Letters. doi: 10.1109/LSENS.2019.2918575.

The dataset contains Scan Cyclic Voltammetry (SCV) and Differential Pulse Voltammetry (DPV) waveform, obtained from APAP (Paracetamol) samples, considering different sampling rate. The data are provided to the reader "as is", for more detail on the set-up, the chemicals and materials refer to [1].

The DownSampling.zip folder contains the following file:

- SCV.mat contains seven cells, one per every sampling rate in the range [33,66:0,58] Hz named CV[sampling_rate]. Any of this cell is composed of seven calibration point, acquired respectively sensing sample of [0,50,100,150,200,250,300] µM of APAP. Every cell contains a matrix composed of a couple of coordinates, the first column, x-axis, is the voltage (V), and the second column, y-axis, is the current (µA). The matrix describes the full Scav Cyclic Voltammogram acquired at the given condition, every voltammogram is repeated three times to consider inter-electrode variability and avoid artefact. 

- DPV.mat contains seven cells, one per every sampling rate in the range [16,83:0,29] Hz named DPV[sampling_rate]. Any of this cell is composed of seven calibration point, acquired respectively sensing sample of [0,50,100,150,200,250,300] µM of APAP. Every cell contains a matrix composed of a couple of coordinates, the first column, x-axis, is the voltage (V), and the second column, y-axis, is the current (µA). The matrix describes the full Differential Pulse Voltammogram acquired at the given condition, every voltammogram is repeated three times to consider inter-electrode variability and avoid artefact.

- openfile.m helps the user to import and plot data in Matlab.

- readme.txt contains this information.

[1] S. Aiassa, S. Carrara and D. Demarchi, "Optimized Sampling Rate for Voltammetry-Based Electrochemical Sensing in Wearable and IoT Applications," in IEEE Sensors Letters. doi: 10.1109/LSENS.2019.2918575.
