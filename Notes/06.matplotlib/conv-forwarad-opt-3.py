import matplotlib.pyplot as plt
import scienceplots
from textwrap import wrap
import numpy as np

# Example data (updated from your table)
optimizations =  [
    "gang, vector", "gang, worker, vector", "gang, vector collapse(2)", 
    "gang vector collapse(3)", "gang vector(128) collapse(3)", 
    "gang vector(64) collapse(3)", "gang vector(32) collapse(3)", 
    "gang worker vector collapse(3)"
]

conv_time = [6.340464, 6.344539, 6.337192, 6.224324, 6.23119, 6.24428, 6.214942, 6.223223]
total_time = [8.154614, 8.154156, 8.153062, 8.045263, 8.056375, 8.07061, 8.023729, 8.044619]
acceleration = [68.65, 68.65, 68.66, 69.58, 69.49, 69.37, 69.77, 69.59]

# Wrap labels for readability
wrapped_labels = ['\n'.join(wrap(label, width=15)) for label in optimizations]

# Set bar width and positions
x = np.arange(len(optimizations))  # X-axis positions for bars
bar_width = 0.2  # Width of each bar

# Scale acceleration values to make the bar appear shorter
scaling_factor = 5  # Adjust this value to control the relative height of the acceleration bars
scaled_acceleration = [value / scaling_factor for value in acceleration]


# Create the plot
with plt.style.context(['science', 'notebook']):
    plt.figure(figsize=(14, 8))  # Adjust figure size
    
    # Plot grouped bars
    bars1 = plt.bar(x - bar_width, conv_time, bar_width, color='#2066a8', label='Conv')
    bars2 = plt.bar(x, total_time, bar_width, color='#3594cc', label='Total time')
    bars3 = plt.bar(x + bar_width, scaled_acceleration, bar_width, color='#8cc5e3', label='Acceleration')

    # Add titles and labels
    plt.title('pad_input', fontsize=14)
    plt.xlabel('OpenACC clauses', fontsize=12)
    plt.ylabel('χρόνος εκτέλεσης / επιτάχυνση', fontsize=12)
    plt.xticks(x, wrapped_labels, fontsize=10, rotation=45, ha='right')  # Rotated and wrapped x-axis labels
    plt.yticks(fontsize=10)
    plt.ylim(0, 15)  # Adjust y-axis range to go from 0 to 12

    # Annotate bars with values
    for bars, data, label in zip([bars1, bars2, bars3], [conv_time, total_time, acceleration],
                                 ['sec', 'sec', 'x']):
        for bar, value in zip(bars, data):
            plt.text(bar.get_x() + bar.get_width() / 2, 
                     bar.get_height() + 0.2, 
                     f'{value:.2f} {label}', 
                     ha='center', fontsize=8)

# Add legend
plt.legend(fontsize=10, loc='lower right', facecolor='white', framealpha=1) 

# Save the plot
plt.tight_layout()
plt.savefig('figures/fig-3-accel.jpg', dpi=300)
plt.close()
