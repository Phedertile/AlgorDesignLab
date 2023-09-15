import math
from timeit import default_timer as timer

# Euclidean distance between two vertices
def dist(p1, p2):
    return math.sqrt( (p1[0] - p2[0])**2 + (p1[1] - p2[1])**2 )


# perimeter of triangle
def cost(polygon, i, j, k):
    p1 = polygon[i]
    p2 = polygon[j]
    p3 = polygon[k]
    return dist(p1, p2) + dist(p1, p3) + dist(p2, p3)

        
"""
every coordinate must be sorted by graham scan first.
graham scan is to sort all vertices by angle and distance from bottom-left corner by counter-clockwise.
some of teacher's test cases are not sorted and can run incorrectly.
"""

from functools import cmp_to_key

def orientation(p, q, r):
    val = ( (q[1] - p[0]) * (r[0] - q[0]) -(q[0] - p[0]) * (r[0] - q[0]) )
    
    if val == 0:
        return 0  # collinear
    elif val > 0:
        return 1  # clock wise
    else:
        return 2  # counterclock wise

def polar_angle(p1, p2):
    if p1[1] == p2[1]:
        return -math.pi
    dy = p1[1]-p2[1]
    dx = p1[0]-p2[0]
    return math.atan2(dy, dx)

def graham(points):
    points = points.copy()
    
    # find the most bottom vertice
    p0 = min(points, key=lambda p: (p[1], p[0]))
    # sort by angle first, if equal then sort by x value
    points.sort(key=lambda p: (polar_angle(p0, p), dist(p0, p)))
   
   # swap if next vertice is counter-clockwise
    for i in range(1, len(points)):
        while i > 1 and orientation(points[i-1], points[0], points[i]) == 2:
            # swap
            points[-1], points[i] = points[i], points[-1]
  
    return points

# function to find minimum cost of triangulation of n vertices polygon using recursion
def minCost(polygon, i, j):
    # Base case
    if j-i < 2:
        return 0

    # Initialize minimum variable
    minimum = math.inf
    
    # loop all every possible ways
    # similiar to matrix division in matrix chaining
    for k in range(i+1, j):
        minimum = min(minimum, minCost(polygon, i, k) + minCost(polygon, k, j) + cost(polygon, i, j, k))
    
    return round(minimum, 4)


# -----------------------------------------------------------------------------------------------------------------
start = timer()

file = open("./homework5/testcase/4.txt", "r")
n = int(file.readline())
polygon = []
# polygon = [(0, 0), (1, 0), (2, 1), (1, 2), (0, 2)]

for line in file:
    x, y = line.strip().split(" ")
    polygon.append( (float(x), float(y)) )

print("Coordinate : ")
print(polygon)
print("Sorted coordinate : ")
print(graham(polygon))
print("minimum triangulation : ", minCost(graham(polygon), 0, n-1))
end = timer()
print("Timer : ", end - start)

