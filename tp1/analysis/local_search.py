import os
import pandas as pd

# Carrega os datasets
df_inst = pd.read_csv(os.path.join("data", "instances.csv"))
df_res = pd.read_csv(os.path.join("data", "results.csv"))

# Junta os dois dataframes pela coluna 'id'
df = pd.merge(df_inst, df_res, on="id")

# -------------------------------------------------------------
# ANÁLISE 3: A busca local melhora significativamente a solução trivial?
# -------------------------------------------------------------
df["melhora_busca_local_vs_trivial"] = round(((df["trivial"] - df["busca_local"]) / df["trivial"]) * 100, 2)
melhora_media_3 = df["melhora_busca_local_vs_trivial"].mean()

print("Análise 3: A busca local melhora significativamente a solução trivial?")
print(f"→ Melhora média: {melhora_media_3:.2f}%")
print()

# -------------------------------------------------------------
# ANÁLISE 4: A busca local melhora significativamente a solução gulosa?
# -------------------------------------------------------------
df["melhora_busca_local_vs_guloso"] = round(((df["guloso"] - df["guloso_busca_local"]) / df["guloso"]) * 100, 2)
melhora_media_4 = df["melhora_busca_local_vs_guloso"].mean()

print("Análise 4: A busca local melhora significativamente a solução gulosa?")
print(f"→ Melhora média: {melhora_media_4:.2f}%")
print()

# -------------------------------------------------------------
# ANÁLISE 5: É mais vantajoso aplicar a busca local à solução gulosa do que à trivial?
# -------------------------------------------------------------
# Comparação direta entre as melhorias da busca local aplicada à trivial e à gulosa
df["melhora_trivial_vs_guloso"] = round(((df["busca_local"] - df["guloso_busca_local"]) / df["busca_local"]) * 100, 2)
melhora_media_5 = df["melhora_trivial_vs_guloso"].mean()

print("Análise 5: É mais vantajoso aplicar a busca local à solução gulosa do que à trivial?")
print(f"→ Diferença média de melhora (trivial - guloso): {melhora_media_5:.2f}%")

# Exporta os dados das análises em CSV para uso em tabelas LaTeX
df_export = df[["id", "melhora_busca_local_vs_trivial", "melhora_busca_local_vs_guloso", "melhora_trivial_vs_guloso"]].copy()
df_export.columns = ["id", "melhora_trivial", "melhora_guloso", "diff_trivial_guloso"]
df_export.to_csv(os.path.join("data", "local_search_analysis.csv"), index=False)
