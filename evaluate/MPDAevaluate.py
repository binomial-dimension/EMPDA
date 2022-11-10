
import numpy as np
from scipy import spatial


class Task():
    def __init__(self,Q_demand,rate,Time_uncompleted) -> None:
        self.Q_demand = Q_demand # demand of task indexed j accumulated at time t, which represents as q_j(t) in the 
        self.rate = rate
        self.Time_uncompleted = 0
class Robot():
    def __init__(self,ability) -> None:
        self.ability = ability

poslist = []

with open('test.graph','r') as f:
    for line in f:
        pos = (float(i) for i in line.split())
        poslist.append(pos)
    distance = spatial.distance(poslist)

with open('test.task','r') as f:
    for line in f:
        pos = (float(i) for i in line.split())
# 再写个robot 和 解的读入


