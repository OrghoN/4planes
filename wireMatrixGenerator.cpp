#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/aff_transformation_tags.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/number_utils.h>
#include <list>
#include <cmath>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Aff_transformation_2<Kernel>              Transformation;
typedef CGAL::Polygon_2<Kernel>                           Polygon_2;
typedef CGAL::Polygon_with_holes_2<Kernel>                Polygon_with_holes_2;
typedef Kernel::Point_2 Point_2;
typedef std::list<Polygon_with_holes_2>                   Pwh_list_2;
typedef CGAL::Vector_2<Kernel> Vector;
typedef CGAL::Direction_2<Kernel> Direction;
CGAL_EXPORT extern const CGAL::Translation              TRANSLATION;

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


int main ()
{
        double angle = M_PI/3;
        Transformation rotate(cos(angle), -sin(angle), sin(angle), cos(angle), 1);
        Transformation translate(TRANSLATION, Vector(-2, 0));

        Polygon_2 w0;
        w0.push_back (Point_2 (1,-10));
        w0.push_back (Point_2 (1,10));
        w0.push_back (Point_2 (-1,10));
        w0.push_back (Point_2 (-1,-10));
        std::cout << "w0 = "; print_polygon (w0);

        Polygon_2 v2;
        v2.push_back (translate(Point_2 (10,-1)));
        v2.push_back (translate(Point_2 (10,1)));
        v2.push_back (translate(Point_2 (-10,1)));
        v2.push_back (translate(Point_2 (-10,-1)));
        std::cout << "v2 = "; print_polygon (v2);

        Polygon_2 u0;
        u0.push_back (rotate(Point_2 (1,-10)));
        u0.push_back (rotate(Point_2 (1,10)));
        u0.push_back (rotate(Point_2 (-1,10)));
        u0.push_back (rotate(Point_2 (-1,-10)));
        std::cout << "u0 = "; print_polygon (u0);

        Polygon_with_holes_2 intersect = intersection(w0, v2);
        print_polygon_with_holes(intersection(intersect, u0));

        return 0;
        // if ((CGAL::do_intersect(w0, v2)))
        //         std::cout << "The two polygons intersect in their interior." << std::endl;
        // else
        //         std::cout << "The two polygons do not intersect." << std::endl;
        // return 0;
}
