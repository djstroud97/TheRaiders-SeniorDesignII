# Uses Python 3
# Requirements: matplotlib (install using "pip install matplotlib")
#               numpy (install using "pip install numpy")

import sys
import matplotlib.pyplot as plt
import numpy as np

# Check if log file has been passed properly
if (len(sys.argv) < 2):
    sys.exit("Log file not specified")
elif (len(sys.argv) == 2):
    print("Log file",sys.argv[1],"found")
else:
    sys.exit("Too many arguments passed")

# Function for reading each x,y,z measurement from file
def readFile(str,x,y,z):
    # Open given log file with read permission
    fileOpen = open(str,"r")
    print("Opening:",str)
    
    # Read each line from log file
    fileLine = fileOpen.readline()
    
    # Split values to x,y,z coordinates
    while(fileLine):
        temp = fileLine.split()
        x.append(temp[0])
        y.append(temp[1])
        z.append(temp[2])
        fileLine = fileOpen.readline()
    fileOpen.close()
## End of readFile() ##

# Function to graph x,y,z values
def plotData(x,y,z):
    # Test values for time interval
    t = []
    for i in range(len(x)):
        t.append(i)
    
    # Plot graph for X-Coordinates
    plt.subplot(3,1,1)
    plt.plot(t, x, '.-',linewidth=0.5)
    plt.yticks(np.arange(min(x), max(x)+4, 2.0))
    for i in range(len(x)):
        plt.annotate(x[i],(t[i],x[i]))
    plt.title('3-Axis Accelerometer Data')
    plt.ylabel('X acceleration')
    
    # Plot graph for Y-Coordinates
    plt.subplot(3,1,2)
    plt.plot(t, y, '.-',linewidth=0.5)
    plt.yticks(np.arange(min(y), max(y)+4, 2.0))
    for i in range(len(x)):
        plt.annotate(y[i],(t[i],y[i]))
    plt.xlabel('time')
    plt.ylabel('Y acceleration')
    
    # Plot graph for Z-Coordinates
    plt.subplot(3,1,3)
    plt.plot(t, z, '.-',linewidth=0.5)
    plt.yticks(np.arange(min(z), max(z)+4, 2.0))
    for i in range(len(x)):
        plt.annotate(z[i],(t[i],z[i]))
    plt.xlabel('time')
    plt.ylabel('Z acceleration')
    
    plt.show()
## End of plotData() ##

# Calculate the averages of the x,y,z coordinates to 2 decimal places
def calc_avg(x,y,z):
    avg_x = np.round(np.average(x), decimals=2)
    avg_y = np.round(np.average(y), decimals=2)
    avg_z = np.round(np.average(z), decimals=2)
    
    print("\nAverage X =", avg_x)
    print("Average Y =", avg_y)
    print("Average Z =", avg_z)
## End of calc_avg() ##

# List max for x,y,z coordinates
def calc_max(x,y,z):
    print("\nMax X =", max(x))
    print("Max Y =", max(y))
    print("Max Z =", max(z))
## End of calc_max() ##

# List all x,y,z coordinates
def list_coord(x,y,z):
    print("\nx =", *x, sep='\t')
    print("y =", *y, sep='\t')
    print("z =", *z, sep='\t')
## End of list_coord() ##

# Main function
def main():
    # Find name of log file
    fileName = sys.argv[1]
    
    # Check if text file was passed
    if(fileName.endswith('.txt')):
        # Initialize lists for x,y,z coordinates
        x, y, z = ([] for _ in range(3))
        
        # Call function to read values from file
        readFile(fileName,x,y,z)
        
        # Convert values from string to float
        x = list(map(float,x))
        y = list(map(float,y))
        z = list(map(float,z))
        
        # Print all x,y,z coordinates
        list_coord(x,y,z)
        
        # Calculate average for x,y,z coordinates
        calc_avg(x,y,z)
        
        # Calculate maximum for x,y,z coordinates
        calc_max(x,y,z)
        
        # Call function to plot x,y,z coordinates
        plotData(x,y,z)
    else:
        sys.exit("Wrong file type passed (.txt only)")
## End of main() ##

# Call main function
main()