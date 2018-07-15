from sympy import Point, Line, Polygon, pi
import itertools
import numpy as np

def ccw(A, B, C):
    return (C.y - A.y) * (B.x - A.x) > (B.y - A.y) * (C.x - A.x)

def intersect(A, B, C, D):
    return ccw(A, C, D) != ccw(B, C, D) and ccw(A, B, C) != ccw(A, B, D)

class wire:

    def __init__(self, left0, left1, right0, right1,planeNo,wireNo,trueWireNo):
        self.leftBound = Line(left0, left1)
        self.rightBound = Line(right0, right1)
        self.planeNo = planeNo
        self.wireNo = wireNo
        self.trueWireNo = trueWireNo

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
        return str([self.planeNo,self.wireNo,self.trueWireNo])
        # return str([self.leftBound, self.rightBound])

def make3PlaneGrid():
    grid = [[],[],[]]

    wirePitch = 2
    wireLength = 1000
    wiresPerPlane = 3

    leftMost = -(wirePitch/2)*wiresPerPlane

    for wireNo in range(wiresPerPlane):
        wire1 = wire(Point(leftMost+wireNo*wirePitch,-wireLength),Point(leftMost+wireNo*wirePitch,wireLength),Point(leftMost+(wireNo +1)*wirePitch,-wireLength),Point(leftMost+(wireNo +1)*wirePitch,wireLength),0,wireNo,wireNo+0*wiresPerPlane)
        wire1.translate(wirePitch/2,0)
        wire2 = wire(Point(leftMost+wireNo*wirePitch,-wireLength),Point(leftMost+wireNo*wirePitch,wireLength),Point(leftMost+(wireNo +1)*wirePitch,-wireLength),Point(leftMost+(wireNo +1)*wirePitch,wireLength),1,wireNo,wireNo+1*wiresPerPlane)
        wire2.rotate(pi/3)
        wire3 = wire(Point(leftMost+wireNo*wirePitch,-wireLength),Point(leftMost+wireNo*wirePitch,wireLength),Point(leftMost+(wireNo +1)*wirePitch,-wireLength),Point(leftMost+(wireNo +1)*wirePitch,wireLength),2,wireNo,wireNo+2*wiresPerPlane)
        wire2.rotate(2*pi/3)

        grid[0].append(wire1)
        grid[1].append(wire2)
        grid[2].append(wire3)

    return grid

def make2PlaneGrid():
    grid = [[],[]]

    wirePitch = 2
    wireLength = 1000
    wiresPerPlane = 3

    leftMost = -(wirePitch/2)*wiresPerPlane

    for wireNo in range(wiresPerPlane):
        wire1 = wire(Point(leftMost+wireNo*wirePitch,-wireLength),Point(leftMost+wireNo*wirePitch,wireLength),Point(leftMost+(wireNo +1)*wirePitch,-wireLength),Point(leftMost+(wireNo +1)*wirePitch,wireLength),0,wireNo,wireNo+0*wiresPerPlane)
        wire2 = wire(Point(leftMost+wireNo*wirePitch,-wireLength),Point(leftMost+wireNo*wirePitch,wireLength),Point(leftMost+(wireNo +1)*wirePitch,-wireLength),Point(leftMost+(wireNo +1)*wirePitch,wireLength),1,wireNo,wireNo+1*wiresPerPlane)
        wire2.rotate(pi/2)

        grid[0].append(wire1)
        grid[1].append(wire2)

    return grid


# grid = make3PlaneGrid()
grid = make2PlaneGrid()

def makeMatrixFromGeometry(grid):
    cells = []

    potentialCells = list(itertools.product(*grid))
    for potentialCell in potentialCells:
        goodCell = True
        potentialIntersections = list(itertools.combinations(potentialCell,2))
        for intersection in potentialIntersections:
            if not intersection[0].doesIntersect(intersection[1]):
                goodCell = False
                break
        if goodCell:
            cell = []
            for wire in potentialCell:
                cell.append(wire.trueWireNo)
            cells.append(cell)

    # print(cells)

    matrix = np.zeros((grid[-1][-1].trueWireNo+1,len(cells)), dtype = int)
    for cellNo, cell in enumerate(cells):
        for wire in cell:
            matrix[wire][cellNo] = 1

    return matrix

makeMatrixFromGeometry(grid)
#
# p1 = Point(-5,0)
# p2 = Point(5,0)
# p3 = Point(-5,-5)
# p4 = Point(5,5)
#
# print(intersect(p1,p2,p3,p4))
