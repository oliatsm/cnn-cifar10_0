import matplotlib.pyplot as plt
import scienceplots
from textwrap import wrap

# Example data
parallel_loop_optimizations = [
    "no Opt",
    "gang, vector",
    "gang, worker, vector",
    "gang collapse(2), worker, vector",
    "gang collapse(3),vector collapse(2)"
]  # Parallel loop optimizations
execution_times = [92.297987, 92.080878, 27.883512, 7.073652, 8.26153]  # Execution times in seconds

# Wrap the x-axis labels
wrapped_labels = ['\n'.join(wrap(label, width=15)) for label in parallel_loop_optimizations]

# Create the bar plot
with plt.style.context(['science', 'notebook']):
    plt.figure(figsize=(10, 6))  # Set a reasonable figure size
    bars = plt.bar(wrapped_labels, execution_times, color='skyblue', width=0.5)

    # Add title and labels
    plt.title('Βελτιστοποίηση conv_forward', fontsize=14)
    plt.xlabel('βελτιστοποίηση', fontsize=12)
    plt.ylabel('χρόνος εκτέλεσης (seconds)', fontsize=12)

    # Annotate bars with execution times
    for bar, time in zip(bars, execution_times):
        plt.text(bar.get_x() + bar.get_width() / 2,  # X position (center of bar)
                 bar.get_height() + 1,              # Y position (just above the bar)
                 f'{time:.2f} sec',                 # Text (formatted execution time with "sec")
                 ha='center', fontsize=10)          # Horizontal alignment and font size

    # Adjust font sizes for clarity
    plt.xticks(fontsize=10)
    plt.yticks(fontsize=10)

    # Save the plot
    plt.savefig('figures/fig-1.jpg', dpi=300)
    plt.close()
