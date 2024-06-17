import matplotlib.pyplot as plt
import numpy as np
import scienceplots

serial_time = [34.827892, 536.529739, 851.306370, 1245.024988, 1761.983244]
parallel_time = [1.214392, 16.378215, 25.546127, 37.820342, 50.399257]
# Sample data
categories = ['Serial', 'OpenACC']
groups = [1200, 13400, 25600, 37800, 50000]
values = np.array([[34.827892, 536.529739, 851.306370, 1245.024988, 1761.983244],
                   [1.214392, 16.378215, 25.546127, 37.820342, 50.399257]])

# Setting the positions for each group
x = np.arange(len(groups))

# Width of each bar
width = 0.2
with plt.style.context(['science','light','notebook']):

    # Plotting each cluster of columns
    fig, ax = plt.subplots()
    for i, category in enumerate(categories):
        ax.bar(x + width*i, values[i], width=width, label=category)

    # Adding labels and title
    ax.set_xlabel('Number of Images')
    ax.set_ylabel('Time (Seconds)')
    ax.set_title('Net Forward Execution Time')
    ax.set_xticks(x + width)
    ax.set_xticklabels(groups)
    ax.legend()

    # Display the plot
    plt.tight_layout()
    # plt.show()
    plt.savefig('figures/fig-4.jpg', dpi=300)  # Specify the filename with .jpg extension and optional DPI setting
    plt.close()
