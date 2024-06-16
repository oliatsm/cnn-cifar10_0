import matplotlib.pyplot as plt
import scienceplots

# Example data
num_images = [1200, 13400, 25600, 37800, 50000]  # Number of input images
execution_times = [34.867567, 536.818719, 852.228448, 1245.807212, 1764.764805]  # Execution times in seconds

# Create the bar plot
with plt.style.context(['science','notebook']):

    plt.figure()
    plt.bar(num_images, execution_times, color='skyblue',width=5000)

    # Add title and labels
    plt.title('Serial Program')
    plt.xlabel('Number of Input Images')
    plt.ylabel('Execution Time (seconds)')

    # Set the x-axis to only show the numbers in num_images
    plt.xticks(num_images, num_images,fontsize=10)
    plt.yticks([int(time) for time in execution_times],fontsize=8)

    # Show the plot
    plt.savefig('execution_times-3.jpg', dpi=300)  # Specify the filename with .jpg extension and optional DPI setting
    plt.close()
