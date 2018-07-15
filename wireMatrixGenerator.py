from sympy import Point, Line, Polygon, pi
from itertools import product

class wire(object):
    def _init_ (self, left0, left1, right0, right1):
        self.leftBound = Line(left0, left1)
        self.rightBound = Line(right0, right1)

    def rotate(self, angle):
        self.leftBound = self.leftBound.rotate(angle)
        self.rightBound = self.rightBound.rotate(angle)

    def translate(self, x,y):
        self.leftBound = self.leftBound.translate(x,y)
        self.rightBound = self.rightBound.translate(x,y)

    def doesIntersect(self, wire):
        return _intersect(self.leftBound.points[0],self.leftBound.points[1],wire.leftBound.points[0],wire.leftBound.points[1]) and _intersect(self.leftBound.points[0],self.leftBound.points[1],wire.rightBound.points[0],wire.rightBound.points[1]) and _intersect(self.rightBound.points[0],self.rightBound.points[1],wire.leftBound.points[0],wire.leftBound.points[1]) and _intersect(self.rightBound.points[0],self.rightBound.points[1],wire.rightBound.points[0],wire.rightBound.points[1])

    def _ccw(A,B,C):
    	return (C.y-A.y)*(B.x-A.x) > (B.y-A.y)*(C.x-A.x)

    def _intersect(A,B,C,D):
    	return ccw(A,C,D) != ccw(B,C,D) and ccw(A,B,C) != ccw(A,B,D)

    def _str_(self):
        return [leftBound,rightBound]

wire1 = (Point(-1,-5),Point(-1,5),Point(1,5),Point(1,-5))
print(wire1)

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
