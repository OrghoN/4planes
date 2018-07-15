from sympy import Point, Line, Polygon, pi
from itertools import product

def ccw(A, B, C):
    return (C.y - A.y) * (B.x - A.x) > (B.y - A.y) * (C.x - A.x)

def intersect(A, B, C, D):
    return ccw(A, C, D) != ccw(B, C, D) and ccw(A, B, C) != ccw(A, B, D)

class wire:

    def __init__(self, left0, left1, right0, right1):
        self.leftBound = Line(left0, left1)
        self.rightBound = Line(right0, right1)


    def rotate(self, angle):
        self.leftBound = self.leftBound.rotate(angle)
        self.rightBound = self.rightBound.rotate(angle)

    def translate(self, x, y):
        self.leftBound = self.leftBound.translate(x, y)
        self.rightBound = self.rightBound.translate(x, y)

    def doesIntersect(self, wire):
        ll = intersect(self.leftBound.points[0], self.leftBound.points[1], wire.leftBound.points[0], wire.leftBound.points[1])
        lr = intersect(self.leftBound.points[0], self.leftBound.points[1], wire.rightBound.points[0], wire.rightBound.points[1])
        rl = intersect(self.rightBound.points[0], self.rightBound.points[1], wire.leftBound.points[0], wire.leftBound.points[1])
        rr = intersect(self.rightBound.points[0], self.rightBound.points[1], wire.rightBound.points[0], wire.rightBound.points[1])
        # print(ll,lr,rl,rr)
        return ll and lr and rl and rr

    def __repr__(self):
        return str([self.leftBound, self.rightBound])

def make3PlaneGrid():
    grid = [[],[],[]]

    wirePitch = 2
    wireLength = 1000
    wiresPerPlane = 3

    leftMost = -(wirePitch/2)*wiresPerPlane

    for i in range(wiresPerPlane):
        wire1 = wire(Point(leftMost+i*wirePitch,-wireLength),Point(leftMost+i*wirePitch,wireLength),Point(leftMost+(i+1)*wirePitch,-wireLength),Point(leftMost+(i+1)*wirePitch,wireLength))
        wire1.translate(wirePitch/2,0)
        wire2 = wire(Point(leftMost+i*wirePitch,-wireLength),Point(leftMost+i*wirePitch,wireLength),Point(leftMost+(i+1)*wirePitch,-wireLength),Point(leftMost+(i+1)*wirePitch,wireLength))
        wire2.rotate(pi/3)
        wire3 = wire(Point(leftMost+i*wirePitch,-wireLength),Point(leftMost+i*wirePitch,wireLength),Point(leftMost+(i+1)*wirePitch,-wireLength),Point(leftMost+(i+1)*wirePitch,wireLength))
        wire2.rotate(2*pi/3)

        grid[0].append(wire1)
        grid[1].append(wire2)
        grid[2].append(wire3)

    return grid

grid = make3PlaneGrid()

# print (len(grid[0]))

for wire in grid[0]:
    print (wire)
#
# wire1 = wire(Point(-1, -6), Point(-1, 6), Point(1, 6), Point(1, -6))
# wire2 = wire(Point(-5, -1), Point(5, -1), Point(-5, 1), Point(5, 1))
# wire3 = wire(Point(-5, 5), Point(5, 5), Point(-5, 3), Point(5, 3))
#
# print(wire1.doesIntersect(wire2))
# # print(wire1.leftBound)
# # (wire1.doesIntersect(wire2))
# print(wire1.doesIntersect(wire3))
# print(wire2.doesIntersect(wire3))
#

# print(wire1)

# p1 = Point(-5,0)
# p2 = Point(5,0)
# p3 = p1.rotate(pi/3).translate(0.2333,0.233)
# p4 = p2.rotate(pi/3).translate(0.2333,0.233)


#
# l1 = Line(Point(-5,0), Point(5,0))
# l3 = l1.rotate(pi/3).translate(0.2333,0.233)
# l2 = Line(Point(0,-5), Point(0,5))

# print(l1.points)


# for i in range(100):
#     l1.intersection(l2)
#     l1.intersection(l3)
# intersect(l1.points[0],l1.points[1],l2.points[0],l2.points[1])
#
# a = [[1,2],[3,4]]
#
# print(list(product(*a)))
#
# rec1 = Polygon(Point(-1,-5),Point(-1,5),Point(1,5),Point(1,-5))
# rec2 = rec1.rotate(pi/3)


# rec2 = Polygon(Point(-5,-1),Point(-5,1),Point(5,1),Point(5,-1))
# rec3 = Polygon(Point(-5,3),Point(-5,5),Point(5,5),Point(5,3))
#
# print(rec1.intersection(rec2))
# print(rec2.intersection(rec3))
# print(rec1.intersection(rec3))
