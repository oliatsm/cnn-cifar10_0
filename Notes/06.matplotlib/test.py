
# importing package  
import matplotlib.pyplot as plt  
import numpy as np  
  
# create data  
X = [1,2,3,4,5]  
Y = [3,3,3,3,3]  
  
# plot lines  
plt.plot(X, Y, label = "Line-1")  
plt.plot(Y, X, label = "Line-2")  
plt.plot(X, np.sin(X), label = "Curve-1")  
plt.plot(X, np.cos(X), label = "Curve-2")  
  
#Change the background color of a  legend. 
plt.legend(fontsize=10, loc='lower right', facecolor="white") 
plt.title("Line Graph - Geeksforgeeks") 
  
# Save the plot
plt.tight_layout()
plt.savefig('figures/test.jpg', dpi=300)
plt.close()
