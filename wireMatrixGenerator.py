from sympy import Point, Line, Polygon, pi
import itertools

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
        print(ll,lr,rl,rr)
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
cells = []

# l1 = grid[0][0].leftBound
# l2 = grid[1][0].leftBound
#
# print(l1.intersection(l2))
# print(grid[0][0].doesIntersect(grid[1][0]))

potentialCells = list(itertools.product(*grid))
for potentialCell in potentialCells:
    goodCell = True
    print(potentialCell)
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

print(len(cells))














# gridNumbering = []
#
# for i in range(len(grid)):
#     gridNumbering.append([])
#     for k in range(len(grid[i])):
#         gridNumbering[i].append(str(i)+""+str(k))
#
#
# cells = []
# for potentialCell in potentialCells:
#     potentialIntersections = list(itertools.combinations(potentialCell,2))
#     cell = True
#     for intersection in potentialIntersections:
#         # if grid[int(intersection[0][1:])][int(intersection[0][:1])].doesIntersect(grid[int(intersection[1][1:])][int(intersection[1][:1])]):
#         #     print ("true")
#         if not grid[int(intersection[0][1:])][int(intersection[0][:1])].doesIntersect(grid[int(intersection[1][1:])][int(intersection[1][:1])]):
#             cell = False
#             continue
#     if cell:
#         cells.append(potentialCell)
#
# print (len(cells))
# a = [[0,1,2],[0,1,2],[0,1,2]]
# a = list(itertools.product(*a))
# print(a)
# print(list(itertools.combinations(a[5],2)))

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
