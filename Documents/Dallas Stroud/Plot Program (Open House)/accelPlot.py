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
    
    # Split values to x,y,z acceleration data
    while(fileLine):
        temp = fileLine.split()
        if(len(temp) > 2):
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
        timeInterval = (i*20/1000)
        t.append(timeInterval)
    
    # Plot graph for X values
    plt.subplot(3,1,1)
    plt.plot(t, x, '.-',linewidth=0.5)
    plt.title('3-Axis Accelerometer Data')
    plt.ylabel('X acceleration')
    
    # Plot graph for Y values
    plt.subplot(3,1,2)
    plt.plot(t, y, '.-',linewidth=0.5)
    plt.ylabel('Y acceleration')
    
    # Plot graph for Z values
    plt.subplot(3,1,3)
    plt.plot(t, z, '.-',linewidth=0.5)
    plt.xlabel('Time Elapsed (sec)')
    plt.ylabel('Z acceleration')
    
    plt.show()
## End of plotData() ##

# Calculate the averages of the x,y,z values to 2 decimal places
def calc_avg(x,y,z):
    avg_x = np.round(np.average(x), decimals=2)
    avg_y = np.round(np.average(y), decimals=2)
    avg_z = np.round(np.average(z), decimals=2)
    
    print("\nAverage X =", avg_x)
    print("Average Y =", avg_y)
    print("Average Z =", avg_z)
## End of calc_avg() ##

# List max for x,y,z values
def calc_max(x,y,z):
    print("\nMax X =", max(x))
    print("Max Y =", max(y))
    print("Max Z =", max(z))
## End of calc_max() ##

# Main function
def main():
    # Find name of log file
    fileName = sys.argv[1]
    
    # Check if text file was passed
    if(fileName.endswith('.txt')):
        # Initialize lists for x,y,z values
        x, y, z = ([] for _ in range(3))
        
        # Call function to read values from file
        readFile(fileName,x,y,z)
        
        # Convert values from string to float
        x = list(map(float,x))
        y = list(map(float,y))
        z = list(map(float,z))
        
        # Calculate average for x,y,z values
        calc_avg(x,y,z)
        
        # Calculate maximum for x,y,z values
        calc_max(x,y,z)
        
        # Call function to plot x,y,z values
        plotData(x,y,z)
    else:
        sys.exit("Wrong file type passed (.txt only)")
## End of main() ##

# Call main function
main()