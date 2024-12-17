import matplotlib.pyplot as plt
import scienceplots
from textwrap import wrap
import numpy as np

# Example data (updated from your table)
optimizations = [
    "no loop Opt", "gang, vector", "gang, worker, vector", 
    "gang collapse(2), worker, vector", "gang collapse(2), vector collapse(2)", 
    "gang collapse(3), vector collapse(2)", "gang collapse(3), vector collapse(3)",
    "gang collapse(3), vector(32) collapse(2)", "gang collapse(3), vector(32) collapse(3)",
    "gang collapse(3), vector(64) collapse(2)", "gang collapse(3), vector(128) collapse(2)"
]

conv_time = [92.297987, 92.080878, 27.883512, 7.073652, 9.201076, 8.26153, 
             9.233146, 6.324218, 7.083581, 6.809921, 8.257616]

total_time = [94.112327, 93.902484, 29.731619, 8.886524, 11.017764, 10.070598, 
              11.046693, 8.14043, 8.91002, 8.621175, 10.088358]

acceleration = [5.95, 5.96, 18.83, 63.00, 50.81, 55.59, 50.68, 68.77, 62.83, 64.94, 55.49]

# Wrap labels for readability
wrapped_labels = ['\n'.join(wrap(label, width=15)) for label in optimizations]

# Set bar width and positions
x = np.arange(len(optimizations))  # X-axis positions for bars
bar_width = 0.3  # Width of each bar

# Create the plot
with plt.style.context(['science', 'notebook']):
    plt.figure(figsize=(14, 8))  # Adjust figure size
    
    # Plot grouped bars
    bars1 = plt.bar(x - bar_width, conv_time, bar_width, color='#2066a8', label='Conv')
    bars2 = plt.bar(x, total_time, bar_width, color='#3594cc', label='Total time')
    bars3 = plt.bar(x + bar_width, acceleration, bar_width, color='#8cc5e3', label='Acceleration')

    # Add titles and labels
    plt.title('conv_forward', fontsize=14)
    plt.xlabel('OpenACC clauses', fontsize=12)
    plt.ylabel('χρόνος εκτέλεσης / επιτάχυνση', fontsize=12)
    plt.xticks(x, wrapped_labels, fontsize=10, rotation=45, ha='right')  # Rotated and wrapped x-axis labels
    plt.yticks(fontsize=10)

    # Annotate bars with values
    for bars, data, label in zip([bars1, bars2, bars3], [conv_time, total_time, acceleration],
                                 ['sec', 'sec', 'x']):
        for bar, value in zip(bars, data):
            plt.text(bar.get_x() + bar.get_width() / 2, 
                     bar.get_height() + 0.5, 
                     f'{value:.2f} {label}', 
                     ha='center', fontsize=8)

# Add legend
plt.legend(fontsize=10, loc='upper right')

# Save the plot
plt.tight_layout()
plt.savefig('figures/fig-2-acceleration.jpg', dpi=300)
plt.close()
