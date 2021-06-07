%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   
%      Simone AIASSA                  
% Politecnico di Torino, Turin, Italy 
% EPFL, Lausanne, Switzerland         
%                          27.05.2019 
%
% DISCLAIMER:
% 
% To use this data you have to cite the author as follow:
% [] S. Aiassa, S. Carrara and D. Demarchi, "Optimized Sampling Rate for Voltammetry-Based Electrochemical Sensing in Wearable and IoT Applications," in IEEE Sensors Letters. doi: 10.1109/LSENS.2019.2918575.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all
clear all

%load the matlab file
load SCV.mat
load DPV.mat

%number of calibration series
number_of_series = 7;

%set figures
for i=1:14
    figure(i)
    hold on;
    xlabel("Driving Voltage (V)");
    ylabel("Output Current (uA)");
end
         
%cycle on calibrtion series and plot
for i=1:number_of_series
    
     figure(1) 
     plot(CV33_66{i}(1,:), CV33_66{i}(2,:)); 
     title("SCV at 33.66 Hz");
     saveas(gcf,'first','epsc')
     figure(2)
     plot(CV16_83{i}(1,:), CV16_83{i}(2,:)); 
     title("SCV at 16,83 Hz");
     figure(3)
     plot(CV8_41{i}(1,:), CV8_41{i}(2,:));  
     title("SCV at 8,41 Hz");
     figure(4)
     plot(CV4_25{i}(1,:), CV4_25{i}(2,:));  
     title("SCV at 4,25 Hz");
     figure(5)
     plot(CV2_16{i}(1,:), CV2_16{i}(2,:));  
     title("SCV at 2,16 Hz");
     figure(6)
     plot(CV1_08{i}(1,:), CV1_08{i}(2,:));  
     title("SCV at 1,08 Hz");
     figure(7)
     plot(CV0_58{i}(1,:), CV0_58{i}(2,:));  
     title("SCV at 0,58 Hz");
     saveas(gcf,'third','epsc')
     figure(8)
     plot(DPV16_83{i}(1,:), DPV16_83{i}(2,:)); 
     title("DPV at 16,83 Hz");
     figure(9)
     plot(DPV8_41{i}(1,:), DPV8_41{i}(2,:));  
     title("DPV at 8,41 Hz");
     figure(10)
     plot(DPV4_25{i}(1,:), DPV4_25{i}(2,:));  
     title("DPV at 4,25 Hz");
     figure(11)
     plot(DPV2_16{i}(1,:), DPV2_16{i}(2,:));  
     title("DPV at 2,16 Hz");
     figure(12)
     plot(DPV1_08{i}(1,:), DPV1_08{i}(2,:));  
     title("DPV at 1,08 Hz");
     figure(13)
     plot(DPV0_58{i}(1,:), DPV0_58{i}(2,:));  
     title("DPV at 0,58 Hz");
     figure(14)
     plot(DPV0_29{i}(1,:), DPV0_29{i}(2,:));  
     title("DPV at 0,29 Hz");    
end

%add legends
for i=1:14
    figure(i)
    legend("0uM", "50uM", "100uM", "150uM", "200uM", "250uM", "300uM");
end

fclose('all');