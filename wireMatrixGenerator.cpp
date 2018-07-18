#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/aff_transformation_tags.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/number_utils.h>
#include <list>
#include <cmath>
#include <algorithm>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Aff_transformation_2<Kernel>              Transformation;
typedef CGAL::Polygon_2<Kernel>                           Polygon_2;
typedef CGAL::Polygon_with_holes_2<Kernel>                Polygon_with_holes_2;
typedef Kernel::Point_2 Point_2;
typedef std::list<Polygon_with_holes_2>                   Pwh_list_2;
typedef CGAL::Vector_2<Kernel> Vector;
typedef CGAL::Direction_2<Kernel> Direction;
CGAL_EXPORT extern const CGAL::Translation TRANSLATION;

#include "print_utils.h"

Polygon_with_holes_2 intersection(Polygon_2 &polygon1, Polygon_2 &polygon2)
{
        Pwh_list_2 result;
        Polygon_with_holes_2 outputPolygon;

        CGAL::intersection (polygon1, polygon2, std::back_inserter(result) );

        for(auto it = result.begin(); it != result.end(); it++) {
                outputPolygon = *it;
        }

        return outputPolygon;
}

Polygon_with_holes_2 intersection(Polygon_with_holes_2 &polygon1, Polygon_2 &polygon2)
{
        Pwh_list_2 result;
        Polygon_with_holes_2 outputPolygon;

        CGAL::intersection (polygon1, polygon2, std::back_inserter(result) );

        for(auto it = result.begin(); it != result.end(); it++) {
                outputPolygon = *it;
        }

        return outputPolygon;
}

std::vector<std::vector<int> > cart_product (const std::vector<std::vector<int> >& v) {
        std::vector<std::vector<int> > s = {{}};
        for (auto& u : v) {
                std::vector<std::vector<int> > r;
                for (auto& x : s) {
                        for (auto y : u) {
                                r.push_back(x);
                                r.back().push_back(y);
                        }
                }
                s.swap(r);
        }
        return s;
}

std::vector< std::vector<Polygon_2> > generate3PlaneGeometry(int wirePitch, int wireLength, int wiresPerPlane, int noOfPlanes){
        std::vector< std::vector<Polygon_2> > grid(noOfPlanes,std::vector<Polygon_2> (wiresPerPlane));

        //The left coordinate of the left most wire
        double leftMost = -(wirePitch/2)*wiresPerPlane;

        //transformations for the first 3 planes
        double angle1 = M_PI/3;
        double angle2 = 2 * M_PI/3;

        Transformation translate0(TRANSLATION, Vector(wirePitch/2,0));
        Transformation rotate1(cos(angle1), -sin(angle1), sin(angle1), cos(angle1), 1);
        Transformation rotate2(cos(angle2), -sin(angle2), sin(angle2), cos(angle2), 1);

        for(int wireNo = 0; wireNo < wiresPerPlane; wireNo++) {
                // Plane 0
                grid[0][wireNo].push_back(translate0(Point_2(leftMost + (wireNo + 1) * wirePitch, -wireLength)));
                grid[0][wireNo].push_back(translate0(Point_2(leftMost + (wireNo + 1) * wirePitch, wireLength)));
                grid[0][wireNo].push_back(translate0(Point_2(leftMost + wireNo * wirePitch, wireLength)));
                grid[0][wireNo].push_back(translate0(Point_2(leftMost + wireNo * wirePitch, -wireLength)));

                // Plane 1
                grid[1][wireNo].push_back(rotate1(Point_2(leftMost + (wireNo + 1) * wirePitch, -wireLength)));
                grid[1][wireNo].push_back(rotate1(Point_2(leftMost + (wireNo + 1) * wirePitch, wireLength)));
                grid[1][wireNo].push_back(rotate1(Point_2(leftMost + wireNo * wirePitch, wireLength)));
                grid[1][wireNo].push_back(rotate1(Point_2(leftMost + wireNo * wirePitch, -wireLength)));

                // Plane 2
                grid[2][wireNo].push_back(rotate2(Point_2(leftMost + (wireNo + 1) * wirePitch, -wireLength)));
                grid[2][wireNo].push_back(rotate2(Point_2(leftMost + (wireNo + 1) * wirePitch, wireLength)));
                grid[2][wireNo].push_back(rotate2(Point_2(leftMost + wireNo * wirePitch, wireLength)));
                grid[2][wireNo].push_back(rotate2(Point_2(leftMost + wireNo * wirePitch, -wireLength)));
        }

        return grid;
}


int main ()
{

        int wirePitch = 2;
        int wireLength = 1000;
        int wiresPerPlane = 3;
        int noOfPlanes = 3;

        std::vector< std::vector<Polygon_2> > grid = generate3PlaneGeometry(wirePitch,wireLength,wiresPerPlane,noOfPlanes);
        std::cout << grid.size()<< " | " << grid[0].size() << std::endl;
        print_polygon(grid[0][0]);
        print_polygon(grid[1][0]);
        print_polygon(grid[2][0]);


        // std::vector<std::vector<int> > test{{1}, {4,5,6}, {8,9}};
        // std::vector<std::vector<int> > res = cart_product(test);
        //
        // for(size_t i = 0; i < res.size(); i++) {
        //         for (size_t j = 0; j < res[i].size(); j++) {
        //                 std::cout << res[i][j] << "\t";
        //         }
        //         std::cout << std::endl;
        // }





        //
        //
        //
        // double angle = M_PI/3;
        // Transformation rotate(cos(angle), -sin(angle), sin(angle), cos(angle), 1);
        // Transformation translate(TRANSLATION, Vector(-2, 0));
        //
        // Polygon_2 w0;
        // w0.push_back (Point_2 (1,-10));
        // w0.push_back (Point_2 (1,10));
        // w0.push_back (Point_2 (-1,10));
        // w0.push_back (Point_2 (-1,-10));
        // std::cout << "w0 = "; print_polygon (w0);
        //
        // Polygon_2 v2;
        // v2.push_back (translate(Point_2 (10,-1)));
        // v2.push_back (translate(Point_2 (10,1)));
        // v2.push_back (translate(Point_2 (-10,1)));
        // v2.push_back (translate(Point_2 (-10,-1)));
        // std::cout << "v2 = "; print_polygon (v2);
        //
        // Polygon_2 u0;
        // u0.push_back (rotate(Point_2 (1,-10)));
        // u0.push_back (rotate(Point_2 (1,10)));
        // u0.push_back (rotate(Point_2 (-1,10)));
        // u0.push_back (rotate(Point_2 (-1,-10)));
        // std::cout << "u0 = "; print_polygon (u0);
        //
        // Polygon_with_holes_2 intersect = intersection(w0, v2);
        // print_polygon_with_holes(intersection(intersect, u0));








        return 0;
        // if ((CGAL::do_intersect(w0, v2)))
        //         std::cout << "The two polygons intersect in their interior." << std::endl;
        // else
        //         std::cout << "The two polygons do not intersect." << std::endl;
        // return 0;
}
