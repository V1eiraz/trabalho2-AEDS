import os
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as mticker

# CAMINHOS
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
CSV_PATH = os.path.join(BASE_DIR, "ratings.csv")
OUTPUT_DIR = os.path.join(BASE_DIR, "images")

# RÓTULOS
ALGORITHMS_LABELS = {
    "quicksort_m3": "Quick Sort - Mediana de 3",
    "quicksort_rand": "Quick Sort Aleatorizado",
}

SCENARIO_LABELS = {
    "random": "Aleatório",
    "ascending": "Crescente",
    "descending": "Decrescente",
}

METRIC_LABELS = {
    "time_ms": "Tempo de Execução (ms)",
    "memory_mb": "Uso de Memória (MB)",
}

# CORES E MARCADORES
LANGUAGE_CONFIG = {
    "Java": {"color": "#E53935", "marker": "o"},
    "C": {"color": "#1E88E5", "marker": "s"},
    "C++": {"color": "#43A047", "marker": "^"},
    "Python": {"color": "#FB8C00", "marker": "D"},
    "Go": {"color": "#8E24AA", "marker": "P"},
}

# PASTAS 
ALGORITHMS_FOLDERS = {
    "quicksort_m3": "quicksort",
    "quicksort_rand": "randomizedquicksort",
}

# DEFINIÇÃO E FORMATAÇÃO DOS INPUTS
INPUT_SIZES = [100, 1_000, 10_000, 100_000, 1_000_000]

def fmt_input(x, _):
    mapping = {
        100: r"$10^2$",
        1_000: r"$10^3$",
        10_000: r"$10^4$",
        100_000: r"$10^5$",
        1_000_000: r"$10^6$",
    }
    return mapping.get(int(x), str(int(x)))

# GERAÇÃO DOS GRÁFICOS
def generate_graph(df: pd.DataFrame, algorithm: str, scenario: str, metric: str, output_folder: str) -> None:
    fig, ax = plt.subplots(figsize=(8, 5))
    df_filtered = df[(df["algorithm"] == algorithm) & (df["scenario"] == scenario)]
    
    for language, cfg in LANGUAGE_CONFIG.items():
        df_lang = (df_filtered[df_filtered["language"] == language].sort_values("input_size"))
        
        if df_lang.empty:
            continue
        ax.plot(
            df_lang["input_size"],
            df_lang[metric],
            label = language,
            color = cfg["color"],
            marker = cfg["marker"],
            linewidth = 2,
            markersize = 7,
            markeredgewidth = 0.8,
            markeredgecolor = "white",
        )

    # EIXOS
    ax.set_xscale("log")
    if metric == "time_ms":
        ax.set_yscale("log")
    ax.set_xticks(INPUT_SIZES)
    ax.xaxis.set_major_formatter(mticker.FuncFormatter(fmt_input))
    ax.set_xlabel("Tamanho da Entrada", fontsize = 12, labelpad = 8)
    ax.set_ylabel(METRIC_LABELS[metric], fontsize = 12, labelpad = 8)

    # TÍTULO
    ax.set_title(
        f"{ALGORITHMS_LABELS[algorithm]} - {SCENARIO_LABELS[scenario]}\n"
        f"{METRIC_LABELS[metric]} x Tamanho da Entrada",
        fontsize = 13,
        fontweight = "bold",
        pad = 12,
    )
    
    # GRADE E LEGENDA
    ax.grid(True, which = "both", linestyle = "--", linewidth = 0.6, alpha = 0.6)
    ax.grid(True, which = "minor", linestyle = ":", linewidth = 0.4, alpha = 0.4)
    ax.legend(title = "Linguagem", fontsize = 10, title_fontsize = 10, framealpha = 0.9)
    
    # NOTA DE RODAPÉ
    if metric == "time_ms":
        fig.text(
            0.99, 0.01,
            "* Tempo médio de 100 repetições",
            ha = "right",
            va = "bottom",
            fontsize = 8,
            color = "gray",
            style = "italic",
        )
    
    plt.tight_layout()
    
    # SAVE
    metric_tag = "time" if metric == "time_ms" else "memory"
    filename = f"{scenario}_{metric_tag}.png"
    filepath = os.path.join(output_folder, filename)
    
    plt.savefig(filepath, dpi = 150, bbox_inches = "tight")
    plt.close()
    print(f" ✓ {filename}")
    
# MAIN
def main() -> None:
        
    # CARREGA OS DADOS
    if not os.path.exists(CSV_PATH):
        raise FileExistsError(
            f"CSV não encontrado: {CSV_PATH}\n"
            "Certifique-se de que 'ratings.csv' está na mesma pasta que 'charts.py'"
        )
        
    df = pd.read_csv(CSV_PATH)
    df.columns = df.columns.str.strip()
        
    required_cols = {
        "language",
        "algorithm",
        "scenario",
        "input_size",
        "time_ms",
        "memory_mb",
    }
        
    missing = required_cols - set(df.columns)
        
    if missing:
        raise ValueError(f"Colunas ausentes no CSV: {missing}")
        
    # GERANDO TODOS OS GRÁFICOS
    total_graphs = 0
    algorithms = ["quicksort_m3", "quicksort_rand"]
    scenarios = ["random", "ascending", "descending"]
    metrics = ["time_ms", "memory_mb"]
    
    for algorithm in algorithms:
        folder_name = ALGORITHMS_FOLDERS[algorithm]
        output_folder = os.path.join(OUTPUT_DIR, folder_name)
        os.makedirs(output_folder, exist_ok = True)
        
        print(f"\n[{ALGORITHMS_LABELS[algorithm]}] -> {output_folder}")
        
        for scenario in scenarios:
            for metric in metrics:
                generate_graph(df, algorithm, scenario, metric, output_folder)
                total_graphs += 1
    print(f"\n{'-' * 50}")
    print(f" Processo Concluído! {total_graphs} gráficos salvos em '{OUTPUT_DIR}/'")
    print(f"\n{'-' * 50}")

if __name__ == "__main__":
    main()