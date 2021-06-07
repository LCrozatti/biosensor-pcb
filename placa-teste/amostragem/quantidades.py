import numpy as np

n = int(input("Número de amostras a serem testadas: ")) # numero de amostras com concentracoes diferentes

g_ferro = float(input("Massa utilizada para o Ferrocianeto (g):"))

c_kcl = float(input("Concentracao de KCl encontrado(M):"))

c_ferro = np.linspace(0.2,10,n,endpoint=True)

vol_sol = []

for i in c_ferro: 
    
    vol_sol.append(g_ferro/(422.39*i*10**-3))

c_final = 30*c_ferro*10**-3 # Para suprimir a migração, um eletrólito é adicionado 
                            # em excesso (10–50 vezes a concentração da espécie a ser estudada)

vol_kcl = []

for i in range(n): 
        
    vol_kcl.append(c_final[i]*vol_sol[i]/(c_kcl-c_final[i]))    

print("\nPara as seguintes condições iniciais:\n")
print("Num. de amostras:",n,"\nFerrocianeto (g):",g_ferro,"\nKCl(M):",c_kcl,"\nConcentração final de KCl(M):",c_final)
print("\nTemos as seguintes amostras:")

for i in range(n):
    print("------------------------------------------------------------------------")
    print("Amostra num.",i+1)
    print("Ferrocianeto(mM): ",c_ferro[i],"\nVol_água(mL): ",vol_sol[i]*1000,"\nKCl(mL): ",vol_kcl[i]*1000)
    print("Ferrocianeto pós adição de KCl(mM): ",c_ferro[i]*vol_sol[i]/(vol_sol[i]+vol_kcl[i])) 
    
    

