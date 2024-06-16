import matplotlib.pyplot as plt
import numpy as np
import scienceplots


# Sample data
categories = ['conv', 'relu', 'pool','fc', 'softmax']
groups = [1200, 13400, 25600, 37800, 50000]
values = np.array([[34.467251,531.192975,842.637947,1232.192096,1744.045365],
                   [0.138085,1.981061,3.273687,4.892354,6.785088],
                   [0.194502,2.944394,4.723809,6.945552,9.765129],
                   [0.013239,0.198928,0.319371,0.471294,0.661414],
                   [0.001524,0.023067,0.036922,0.055039,0.078102]])

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
    ax.set_xlabel('Layers')
    ax.set_ylabel('Time (sec)')
    ax.set_title('Serial Execution Time')
    ax.set_xticks(x + width)
    ax.set_xticklabels(groups, rotation=45, ha='right')
    ax.legend()

    # Display the plot
    plt.tight_layout()
    # plt.show()
    plt.savefig('figures/fig-3.jpg', dpi=300)  # Specify the filename with .jpg extension and optional DPI setting
    plt.close()
