import os
import pandas as pd

def generate_latex(csv_path):
    df = pd.read_csv(csv_path)

    num_colunas = df.shape[1]
    col_format = "c" * num_colunas
    col_format = col_format.strip()

    # Cabeçalho da tabela
    latex = "\\begin{table}[H]\n"
    latex += "    \\centering\n"
    latex += "    {\\begin{tabular}{" + col_format + "}\n"
    latex += "        \\hline\n"
    latex += "        " + " & ".join(df.columns) + " \\\\\n"
    latex += "        \\hline\n"

    # Conteúdo da tabela
    for _, row in df.iterrows():
        valores = [str(v) for v in row]
        latex += "        " + " & ".join(valores) + " \\\\\n"

    latex += "        \\hline\n"
    latex += "    \\end{tabular}}\n"
    latex += "    \\caption{}\n"
    latex += "    \\label{}\n"
    latex += "\\end{table}\n"

    latex = latex.replace('_', '\\_')

    return latex

if __name__ == '__main__':
    with open(os.path.join('data', 'table_instances.tex'), "w") as f:
        f.write(generate_latex(os.path.join('data', 'instances.csv')))
    with open(os.path.join('data', 'table_results.tex'), "w") as f:
        f.write(generate_latex(os.path.join('data', 'results.csv')))
    with open(os.path.join('data', 'greedy_analysis.tex'), "w") as f:
        f.write(generate_latex(os.path.join('data', 'greedy_analysis.csv')))
    with open(os.path.join('data', 'local_search_analysis.tex'), "w") as f:
        f.write(generate_latex(os.path.join('data', 'local_search_analysis.csv')))
