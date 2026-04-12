import matplotlib.pyplot as plt #import matplotlib

# Prepare data
N_values = [100, 500, 1000, 2000, 4000, 6000, 8000, 10000]

# The following data is in seconds
binary_iterative = [1.72e-8, 2.22e-8, 2.36e-8, 2.78e-8, 2.94e-8, 3.98e-8, 3.82e-8, 5.46e-8]
binary_recursive = [2.02e-8, 2.52e-8, 2.74e-8, 3.00e-8, 3.28e-8, 3.56e-8, 3.58e-8, 3.78e-8]
sequential_iterative = [1.06e-7, 4.74e-7, 9.32e-7, 1.86e-6, 3.70e-6, 5.58e-6, 7.50e-6, 9.42e-6]
sequential_recursive = [2.65e-7, 1.34e-6, 2.61e-6, 5.09e-6, 1.05e-5, 1.59e-5, 2.11e-5, 2.65e-5]

plt.figure(figsize=(10, 6), dpi=300) #High-definition output

# Draw a line graph
plt.plot(N_values, sequential_recursive, marker='s', linestyle='-', color='red', label='Sequential (Recursive)') #Plotting Sequential Search (Recursive)
plt.plot(N_values, sequential_iterative, marker='o', linestyle='--', color='orange', label='Sequential (Iterative)') #Plotting Sequential Search (Iterative)
plt.plot(N_values, binary_recursive, marker='^', linestyle='-', color='blue', label='Binary (Recursive)') #Plotting Binary Search (Recursive)
plt.plot(N_values, binary_iterative, marker='d', linestyle='--', color='green', label='Binary (Iterative)') #Plotting Binary Search (Iterative)

# Format chart
plt.title('Worst-Case Performance of Search Algorithms', fontsize=14, fontweight='bold') #set title
plt.xlabel('Input Size (N)', fontsize=12)
plt.ylabel('Single Run Duration (seconds)', fontsize=12)
plt.grid(True, linestyle=':', alpha=0.7)
plt.legend(loc='upper left', fontsize=10) 

plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0)) # Let the Y-axis use scientific notation

# Save and display the picture
plt.savefig('performance_plot.png', bbox_inches='tight')
print("Plot successfully saved as 'performance_plot.png'")
plt.show()