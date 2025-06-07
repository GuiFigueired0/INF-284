'''
##########################################################
##### THIS FILE WAS WRITTEN WITH THE HELP OF CHATGPT #####
########################################################## 
'''

import os
import pandas as pd

instances = [
    ("inst_1", "burma14", 14, 0, 0),
    ("inst_2", "burma14", 2, 1, 1),
    ("inst_3", "burma14", 4, 1, 2),
    ("inst_4", "burma14", 4, 2, 2),
    ("inst_5", "berlin52", 52, 0, 0),
    ("inst_6", "berlin52", 10, 200, 400),
    ("inst_7", "berlin52", 15, 100, 300),
    ("inst_8", "berlin52", 15, 200, 300),
    ("inst_9", "st70", 70, 0, 0),
    ("inst_10", "st70", 15, 2, 8),
    ("inst_11", "st70", 15, 6, 8),
    ("inst_12", "st70", 10, 6, 10),
    ("inst_13", "st70", 10, 10, 15),
    ("inst_14", "gil262", 262, 0, 0),
    ("inst_15", "gil262", 30, 7, 12),
    ("inst_16", "gil262", 30, 5, 12),
    ("inst_17", "gr666", 666, 0, 0),
    ("inst_18", "dsj1000", 1000, 0, 0),
]
df_instances = pd.DataFrame(instances, columns=["id", "file", "T", "P", "L"])
df_instances.to_csv(os.path.join("data", "instances.csv"), index=False)

output_path = os.path.join("..", "output")

def read_values(file_path):
    with open(file_path, "r") as f:
        elems = {line.strip().split(',')[0]: int(line.strip().split(',')[1]) for line in f if line != ""}
        keys = sorted([(int(key_value[5:]), key_value) for key_value in elems.keys()])
        return [ elems[key_value] for _, key_value in keys ]

result_files = [
    f for f in os.listdir(output_path)
    if f.endswith(".csv")
]

baseline_file = "baseline.csv"
assert baseline_file in result_files, "Arquivo baseline.csv não encontrado na pasta output."

result_files.remove(baseline_file)
ordered_files = [baseline_file] + result_files

result_dict = {}
for file_name in ordered_files:
    key = "baseline" if file_name == baseline_file else os.path.splitext(file_name)[0]
    file_path = os.path.join(output_path, file_name)
    result_dict[key] = read_values(file_path)

num_instances = len(result_dict["baseline"])
ids = [f"inst_{i+1}" for i in range(num_instances)]

df_resultados = pd.DataFrame({"id": ids})
for key, values in result_dict.items():
    df_resultados[key] = values

df_resultados.to_csv(os.path.join("data", "results.csv"), index=False)