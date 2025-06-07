'''
##########################################################
##### THIS FILE WAS WRITTEN WITH THE HELP OF CHATGPT #####
########################################################## 
'''

import os
import pandas as pd
import numpy as np
from scipy import stats

results_path = os.path.join("data", "results.csv")
improvement_path = os.path.join("data", "improvement.csv")
metrics_path = os.path.join("data", "metrics.csv")

df_results = pd.read_csv(results_path)

heuristics = [col for col in df_results.columns if col not in ["id", "baseline"]]

df_improvement = pd.DataFrame()
df_improvement["id"] = df_results["id"]

for heuristic in heuristics:
    improvement = round(((df_results["baseline"] - df_results[heuristic]) / df_results["baseline"]) * 100, 2)
    df_improvement[heuristic] = improvement

df_improvement.to_csv(improvement_path, index=False)

metrics = []

for heuristic in heuristics:
    values = df_improvement[heuristic]
    mean = round(values.mean(), 2)
    std = round(values.std(), 2)
    count = len(values)
    improved_count = (values > 0).sum()
    improvement_percentage = round((improved_count / count) * 100, 2)

    # Intervalo de confiança de 95%
    confidence = 0.95
    sem = stats.sem(values)
    h = sem * stats.t.ppf((1 + confidence) / 2.0, count - 1)
    ci_lower = round(mean - h, 2)
    ci_upper = round(mean + h, 2)

    # Teste t para média diferente de 0
    t_stat, p_value = stats.ttest_1samp(values, 0)

    metrics.append({
        "metaheuristic": heuristic,
        "mean_improvement": mean,
        "std_dev": std,
        "percent_instances_improved": improvement_percentage,
        "confidence_95%_lower": ci_lower,
        "confidence_95%_upper": ci_upper,
        "p_value": round(p_value, 4)
    })

df_metrics = pd.DataFrame(metrics)
df_metrics.to_csv(metrics_path, index=False)
