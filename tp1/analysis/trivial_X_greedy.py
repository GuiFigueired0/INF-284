import os
import pandas as pd

# Carrega os datasets
df_inst = pd.read_csv(os.path.join("data", "instances.csv"))
df_res = pd.read_csv(os.path.join("data", "results.csv"))

# Junta os dois dataframes pela coluna 'id'
df = pd.merge(df_inst, df_res, on="id")

# -------------------------------------------------------------
# ANÁLISE 1: O algoritmo guloso encontra rotas melhores que a solução trivial?
# -------------------------------------------------------------
df["melhora_guloso_vs_trivial"] = ((df["trivial"] - df["guloso"]) / df["trivial"]) * 100

melhorias_positivas = df["melhora_guloso_vs_trivial"] > 0
percentual_melhorou = 100 * melhorias_positivas.sum() / len(df)
melhora_media = df["melhora_guloso_vs_trivial"].mean()

print("Análise 1: O algoritmo guloso encontra rotas melhores que a solução trivial?")
print(f"→ Percentual de instâncias com melhora: {percentual_melhorou:.2f}%")
print(f"→ Melhora média: {melhora_media:.2f}%")
print()

# -------------------------------------------------------------
# ANÁLISE 2: Existe uma versão do guloso superior à outra?
# -------------------------------------------------------------
grupo_crescente = df[df["solucao_inicial"] == "crescente"]
grupo_impar_par = df[df["solucao_inicial"] == "impar-par"]

melhora_crescente = ((grupo_crescente["trivial"] - grupo_crescente["guloso"]) / grupo_crescente["trivial"]) * 100
melhora_impar_par = ((grupo_impar_par["trivial"] - grupo_impar_par["guloso"]) / grupo_impar_par["trivial"]) * 100

media_crescente = melhora_crescente.mean()
media_impar_par = melhora_impar_par.mean()

print("Análise 2: Existe uma versão do guloso superior à outra?")
print(f"→ Melhora média - versão crescente: {media_crescente:.2f}%")
print(f"→ Melhora média - versão ímpar-par: {media_impar_par:.2f}%")

# Escrevendo os valores em um .csv para virar uma tabela do relatório
with open(os.path.join('data', 'greedy_analysis.csv'), "w") as f:
    f.write(f'id,tipo_guloso,melhora\n')
    for index, row in df.iterrows():
        f.write(f'{row['id']},{'simples' if row['solucao_inicial'] == 'crescente' else 'duas-pontas'},{round(row['melhora_guloso_vs_trivial'], 2)}\n')
