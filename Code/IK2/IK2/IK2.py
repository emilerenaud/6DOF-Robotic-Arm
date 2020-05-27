import ikpy
import numpy as np


#For arm simulation uncomment 4 lines below
import ikpy.utils.plot as plot_utils
import matplotlib.pyplot
from mpl_toolkits.mplot3d import Axes3D
ax = matplotlib.pyplot.figure().add_subplot(111, projection='3d')

#Open URDF file of arm for links and chains
my_chain = ikpy.chain.Chain.from_urdf_file("C:/Users/lukab/Desktop/6DOF/Code/IK2/IK2/ur3_robot.urdf")

#cartisean coordinates in m (input in cm)
x = float(input("X:")) / 100
y = float(input("Y:")) / 100
z = float(input("Z:")) / 100

#Martice for end-effector's position
target_position = [x, y, z]

#list of joints angles
angles = my_chain.inverse_kinematics(target_position)

#Convert radians to degrees
for a in range(len(angles) - 2):
    angles[a] = np.degrees(angles[a])

#Add offset to angles (homing 0's)
angles[1] = angles[1] + 90
angles[2] = angles[2] + 135
angles[2] = angles[3] + 110
#angles[2] = angles[4] +
#angles[2] = angles[5] +

#To print joints angles
i = 0
for a in range(len(angles) - 2):
    i += 1
    print(f"{i}: {angles[a]}")

#Display GUI of arm simulation
my_chain.plot(my_chain.inverse_kinematics(target_position), ax)
matplotlib.pyplot.show()
