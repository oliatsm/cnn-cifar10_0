import matplotlib.pyplot as plt
import scienceplots

# Example data
num_images = [1200, 13400, 25600, 37800, 50000]  # Number of input images
execution_times = [36.961910, 424.840853, 829.744195, 1188.364496, 1569.110519]  # Execution times in seconds

# Create the bar plot
with plt.style.context(['science','notebook']):

    plt.figure()
    plt.bar(num_images, execution_times, color='skyblue',width=5000)

    # Add title and labels
    plt.title('Σειριακή εκτέλεση')
    plt.xlabel('αριθμός εικόνων')
    plt.ylabel('χρόνος εκτέλεσης (seconds)')

    # Set the x-axis to only show the numbers in num_images
    plt.xticks(num_images, num_images,fontsize=13)
    plt.yticks([int(time) for time in execution_times],fontsize=13)

    # Show the plot
    plt.savefig('figures/fig-1.jpg', dpi=300)  # Specify the filename with .jpg extension and optional DPI setting
    plt.close()

#---------------------------------------------------------------------------------------------------------------------
# Speed Up
serial_time = [34.827892, 536.529739, 851.306370, 1245.024988, 1761.983244]  # Serial execution times in seconds
parallel_time = [1.214392, 16.378215, 25.546127, 37.820342, 50.399257]  # Parallel execution times in seconds

# Speed Up
serial_asus = [44.246349, 1648.611241]  # Serial execution times in seconds
parallel_asus = [11.396601, 471.426173]  # Parallel execution times in seconds

# Calculate speedup
speedup = [s / p for s, p in zip(serial_time, parallel_time)]

# Create the bar plot
plt.figure()
bars = plt.bar(num_images, speedup, color='lightgreen', width=2500)

# Add title and labels
plt.title('Speedup of Parallel Execution over Serial Execution')
plt.xlabel('Number of Input Images')
plt.ylabel('Speedup (Serial / Parallel)')

# Set the x-axis to only show the numbers in num_images
plt.xticks(num_images, num_images, fontsize=12)
plt.yticks(fontsize=10)

# Annotate the bars with the speedup values
for bar, speed in zip(bars, speedup):
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width() / 2, yval, round(speed, 2), ha='center', va='bottom', fontsize=10)

# Show the plot
plt.savefig('figures/fig-2.jpg', dpi=300)  # Specify the filename with .jpg extension and optional DPI setting
plt.close()

#---------------------------------------------------------------------------------------------------------------------
