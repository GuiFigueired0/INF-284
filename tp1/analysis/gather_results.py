import os
import pandas as pd

# Dados extraídos da imagem
instancias = [
    # id, origem, solucao_inicial, T, P, L
    ("it_1", "burma14", "crescente", 14, 0, 0),
    ("it_2", "burma14", "impar-par", 14, 0, 0),
    ("it_3", "berlin52", "crescente", 52, 0, 0),
    ("it_4", "berlin52", "impar-par", 52, 0, 0),
    ("it_5", "st70", "crescente", 70, 0, 0),
    ("it_6", "st70", "impar-par", 70, 0, 0),
    ("it_7", "gil262", "crescente", 262, 0, 0),
    ("it_8", "gil262", "impar-par", 262, 0, 0),
    ("it_9", "gr666", "crescente", 666, 0, 0),
    ("it_10", "gr666", "impar-par", 666, 0, 0),
    ("it_11", "dsj1000", "crescente", 1000, 0, 0),
    ("it_12", "dsj1000", "impar-par", 1000, 0, 0),
    ("it_13", "burma14", "crescente", 2, 1, 1),
    ("it_14", "burma14", "crescente", 4, 1, 2),
    ("it_15", "burma14", "crescente", 4, 2, 2),
    ("it_16", "berlin52", "crescente", 10, 200, 400),
    ("it_17", "berlin52", "crescente", 15, 100, 300),
    ("it_18", "berlin52", "crescente", 15, 200, 300),
    ("it_19", "st70", "crescente", 15, 2, 8),
    ("it_20", "st70", "crescente", 15, 6, 8),
    ("it_21", "st70", "crescente", 10, 6, 10),
    ("it_22", "st70", "crescente", 10, 10, 15),
    ("it_23", "gil262", "crescente", 30, 7, 12),
    ("it_24", "gil262", "crescente", 30, 5, 12)
]

df_instancias = pd.DataFrame(instancias, columns=[
    "id", "arquivo_origem", "solucao_inicial", "T", "P", "L"
])

df_instancias.to_csv(os.path.join("data", "instances.csv"), index=False)
print("Arquivo instances.csv criado com sucesso!")

# Lê os valores dos arquivos .txt
def ler_arquivo(nome_arquivo):
    with open(nome_arquivo, 'r') as f:
        return [int(l.strip()) for l in f.readlines()]

# Lê os valores
val_part_0 = ler_arquivo(os.path.join("..", "output", "part_0.txt"))
val_part_1 = ler_arquivo(os.path.join("..", "output", "part_1.txt"))
val_part_2 = ler_arquivo(os.path.join("..", "output", "part_2.txt"))
val_greedy = ler_arquivo(os.path.join("..", "output", "part_2_greedy.txt"))

# Verifica o número de instâncias (deve bater com a anterior)
num_instancias = len(val_part_0)
assert num_instancias == len(val_part_1) == len(val_part_2) == len(val_greedy)

# Cria os ids (it_1, it_2, ..., it_n)
ids = [f"it_{i+1}" for i in range(num_instancias)]

# Cria o dataframe de resultados
df_resultados = pd.DataFrame({
    "id": ids,
    "trivial": val_part_0,
    "busca_local": val_part_1,
    "guloso_busca_local": val_part_2,
    "guloso": val_greedy
})

df_resultados.to_csv(os.path.join("data", "results.csv"), index=False)
print("Arquivo results.csv criado com sucesso!")
