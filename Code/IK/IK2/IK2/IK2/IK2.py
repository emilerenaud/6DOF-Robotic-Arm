import ikpy
import numpy as np
import ikpy.plot_utils as plot_utils
#from ikpy.chain import Chain
#from ikpy.link import OriginLink, URDFLink

import matplotlib.pyplot
from mpl_toolkits.mplot3d import Axes3D
ax = matplotlib.pyplot.figure().add_subplot(111, projection='3d')

my_chain = ikpy.chain.Chain.from_urdf_file("C:/Users/lukab/Desktop/DEC/IK/IK2/IK2/IK2/ur3_robot.urdf")

x = int(input("X:"))
y = int(input("Y:"))
z = int(input("Z:"))

target_position = [[1, 1, 1, x],
                   [1, 1, 1, y],
                   [1, 1, 1, z],
                   [0, 0, 0, 1]]

angles = my_chain.inverse_kinematics(target_position)

i = 0
for a in range(len(angles) - 2):
    i += 1
    angles[a] = np.degrees(angles[a])
    print(f"{i}: {angles[a]}")


#1 --
#2 Positice -> CCW
#3 Positive -> CW
#4 Positive -> CW
#5 Positive -> CCW
#6 Positive -> CCW


my_chain.plot(my_chain.inverse_kinematics(target_position), ax)
matplotlib.pyplot.show()
