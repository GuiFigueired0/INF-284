'''
##########################################################
##### THIS FILE WAS WRITTEN WITH THE HELP OF CHATGPT #####
########################################################## 
'''

import os
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from scipy.stats import wilcoxon

# Carregar os dados
results = pd.read_csv(os.path.join("data", "results.csv"))
improvement = pd.read_csv(os.path.join("data", "improvement.csv"))

# Boxplot das melhorias
sns.set_palette('plasma')
plt.figure(figsize=(8, 5))
sns.boxplot(data=improvement[['grasp', 'ils']])
plt.ylabel('Melhoria (%)')
plt.title('Comparação de Melhoria: GRASP vs ILS')
plt.grid(True)
plt.tight_layout()
plt.savefig("improvement_boxplot")
plt.show()

# Teste estatístico: GRASP é melhor que ILS?
# H0: mediana(grasp - ils) == 0 ; H1: mediana(grasp - ils) > 0
diff = improvement['grasp'] - improvement['ils']
stat, p_value = wilcoxon(diff, alternative='greater')

print(f"Estatística de Wilcoxon: {stat}")
print(f"p-valor (GRASP > ILS): {p_value}")
