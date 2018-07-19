#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
// #include <CGAL/Cartesian.h>
#include <CGAL/aff_transformation_tags.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/centroid.h>
#include <CGAL/number_utils.h>
#include <list>
#include <cmath>
#include <iostream>
#include <algorithm>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
// typedef CGAL::Cartesian<double> Kernel;
typedef CGAL::Aff_transformation_2<Kernel>              Transformation;
typedef CGAL::Polygon_2<Kernel>                           Polygon_2;
typedef CGAL::Polygon_with_holes_2<Kernel>                Polygon_with_holes_2;
typedef Kernel::Point_2 Point_2;
typedef std::list<Polygon_with_holes_2>                   Pwh_list_2;
typedef CGAL::Vector_2<Kernel> Vector;
typedef CGAL::Direction_2<Kernel> Direction;

CGAL_EXPORT extern const CGAL::Translation TRANSLATION;
CGAL_EXPORT extern const CGAL::Scaling SCALING;

#include "print_utils.h"


// #### ##    ## ######## ######## ########   ######  ########  ######  ######## ####  #######  ##    ##
//  ##  ###   ##    ##    ##       ##     ## ##    ## ##       ##    ##    ##     ##  ##     ## ###   ##
//  ##  ####  ##    ##    ##       ##     ## ##       ##       ##          ##     ##  ##     ## ####  ##
//  ##  ## ## ##    ##    ######   ########   ######  ######   ##          ##     ##  ##     ## ## ## ##
//  ##  ##  ####    ##    ##       ##   ##         ## ##       ##          ##     ##  ##     ## ##  ####
//  ##  ##   ###    ##    ##       ##    ##  ##    ## ##       ##    ##    ##     ##  ##     ## ##   ###
// #### ##    ##    ##    ######## ##     ##  ######  ########  ######     ##    ####  #######  ##    ##


bool doesIntersect(Polygon_2 &polygon1, Polygon_2 &polygon2){
        return (CGAL::do_intersect(polygon1, polygon2));
}

Polygon_2 intersection(Polygon_2 &polygon1, Polygon_2 &polygon2)
{
        Pwh_list_2 result;
        Polygon_with_holes_2 outputPolygon;

        CGAL::intersection (polygon1, polygon2, std::back_inserter(result) );

        for(auto it = result.begin(); it != result.end(); it++) {
                outputPolygon = *it;
        }

        return outputPolygon.outer_boundary();
}

//  ######   ########  #######  ##     ##          ######   ######## ##    ##
// ##    ##  ##       ##     ## ###   ###         ##    ##  ##       ###   ##
// ##        ##       ##     ## #### ####         ##        ##       ####  ##
// ##   #### ######   ##     ## ## ### ## ####### ##   #### ######   ## ## ##
// ##    ##  ##       ##     ## ##     ##         ##    ##  ##       ##  ####
// ##    ##  ##       ##     ## ##     ##         ##    ##  ##       ##   ###
//  ######   ########  #######  ##     ##          ######   ######## ##    ##

std::vector< std::vector<Polygon_2> > generate3PlaneGeometry(int wirePitch, int wireLength, int wiresPerPlane, int noOfPlanes){
        std::vector< std::vector<Polygon_2> > grid(noOfPlanes,std::vector<Polygon_2> (wiresPerPlane));

        //The left coordinate of the left most wire
        double leftMost = -(wirePitch/2.0)*wiresPerPlane;

        //transformations for the first 3 planes
        Vector direction0 = Vector(wirePitch/2,0);
        double angle1 = M_PI/3;
        double angle2 = 2 * (M_PI/3);

        // Vector direction0 = Vector(0,0);
        // double angle1 = M_PI/2;
        // double angle2 = 2 * (M_PI/2);

        //approximation to eliminate too many cells

        Transformation translate0(TRANSLATION, direction0);
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

std::vector< std::vector<Polygon_2> > generate2PlaneGeometry(int wirePitch, int wireLength, int wiresPerPlane, int noOfPlanes){
        std::vector< std::vector<Polygon_2> > grid(noOfPlanes,std::vector<Polygon_2> (wiresPerPlane));

        //The left coordinate of the left most wire
        double leftMost = -(wirePitch/2.0)*wiresPerPlane;

        //transformations for the first 3 planes
        double angle1 = M_PI/3;

        Transformation translate0(TRANSLATION, Vector(0,0));
        Transformation rotate1(cos(angle1), -sin(angle1), sin(angle1), cos(angle1), 1);

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
        }

        return grid;
}


//  ######   #######   #######  ########  ########  #### ##    ##    ###    ######## ########
// ##    ## ##     ## ##     ## ##     ## ##     ##  ##  ###   ##   ## ##      ##    ##
// ##       ##     ## ##     ## ##     ## ##     ##  ##  ####  ##  ##   ##     ##    ##
// ##       ##     ## ##     ## ########  ##     ##  ##  ## ## ## ##     ##    ##    ######
// ##       ##     ## ##     ## ##   ##   ##     ##  ##  ##  #### #########    ##    ##
// ##    ## ##     ## ##     ## ##    ##  ##     ##  ##  ##   ### ##     ##    ##    ##
//  ######   #######   #######  ##     ## ########  #### ##    ## ##     ##    ##    ########


int wireNoToTrueWireNo(int wiresPerPlane,int planeNo, int wireNo){
        return wiresPerPlane*planeNo + wireNo;
}

std::pair<int,int> trueWireNotoWireNo(int wiresPerPlane, int trueWireNo){
        int wireNo = trueWireNo % wiresPerPlane;
        int planeNo = trueWireNo/wiresPerPlane;

        return std::make_pair(planeNo,wireNo);
}


//  ######  ######## ##       ##                ######   ######## ##    ##
// ##    ## ##       ##       ##               ##    ##  ##       ###   ##
// ##       ##       ##       ##               ##        ##       ####  ##
// ##       ######   ##       ##       ####### ##   #### ######   ## ## ##
// ##       ##       ##       ##               ##    ##  ##       ##  ####
// ##    ## ##       ##       ##               ##    ##  ##       ##   ###
//  ######  ######## ######## ########          ######   ######## ##    ##

std::vector<std::vector<int> > cart_product (const std::vector<std::vector<int> > &v) {
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


//  ######  ######## ##       ##                ######   ######## ##    ##
// ##    ## ##       ##       ##               ##    ##  ##       ###   ##
// ##       ##       ##       ##               ##        ##       ####  ##
// ##       ######   ##       ##       ####### ##   #### ######   ## ## ##
// ##       ##       ##       ##               ##    ##  ##       ##  ####
// ##    ## ##       ##       ##               ##    ##  ##       ##   ###
//  ######  ######## ######## ########          ######   ######## ##    ##


std::vector< std::vector<int> > generateCells(std::vector< std::vector<Polygon_2> > &geometry){
        int wiresPerPlane = geometry[0].size();
        int noOfPlanes = geometry.size();

        std::vector< std::vector<int> > gridI(noOfPlanes,std::vector<int> (wiresPerPlane));

        std::vector< std::vector<int> > cells;
        std::vector< std::vector<int> > potentialCells;

        //generation of grid using true wireNumber
        for(int planeNo = 0; planeNo < noOfPlanes; planeNo++) {
                for (int wireNo = 0; wireNo < wiresPerPlane; wireNo++) {
                        gridI[planeNo][wireNo] = wireNoToTrueWireNo(wiresPerPlane,planeNo,wireNo);
                }
        }

        potentialCells = cart_product(gridI);
        bool goodCell;

        for(int potentialCellNo = 0; potentialCellNo < potentialCells.size(); potentialCellNo++) {
                goodCell = true;
                Polygon_2 cellIntersection;
                if (doesIntersect(geometry[std::get<0>(trueWireNotoWireNo(wiresPerPlane,potentialCells[potentialCellNo][0]))][std::get<1>(trueWireNotoWireNo(wiresPerPlane,potentialCells[potentialCellNo][0]))],geometry[std::get<0>(trueWireNotoWireNo(wiresPerPlane,potentialCells[potentialCellNo][1]))][std::get<1>(trueWireNotoWireNo(wiresPerPlane,potentialCells[potentialCellNo][1]))])) {
                        cellIntersection = intersection(geometry[std::get<0>(trueWireNotoWireNo(wiresPerPlane,potentialCells[potentialCellNo][0]))][std::get<1>(trueWireNotoWireNo(wiresPerPlane,potentialCells[potentialCellNo][0]))],geometry[std::get<0>(trueWireNotoWireNo(wiresPerPlane,potentialCells[potentialCellNo][1]))][std::get<1>(trueWireNotoWireNo(wiresPerPlane,potentialCells[potentialCellNo][1]))]);
                        if(potentialCells[potentialCellNo].size()>2) {
                                for(int trueWireID = 2; trueWireID < potentialCells[potentialCellNo].size(); trueWireID++) {
                                        if(doesIntersect(cellIntersection,geometry[std::get<0>(trueWireNotoWireNo(wiresPerPlane,potentialCells[potentialCellNo][trueWireID]))][std::get<1>(trueWireNotoWireNo(wiresPerPlane,potentialCells[potentialCellNo][trueWireID]))])) {
                                                cellIntersection = intersection(cellIntersection,geometry[std::get<0>(trueWireNotoWireNo(wiresPerPlane,potentialCells[potentialCellNo][trueWireID]))][std::get<1>(trueWireNotoWireNo(wiresPerPlane,potentialCells[potentialCellNo][trueWireID]))]);
                                        }
                                        else{
                                                goodCell = false;
                                        }
                                }
                        }
                }
                else{
                        goodCell = false;
                }
                if(goodCell && cellIntersection.area()>0.0000000000001) {
                        cells.push_back(potentialCells[potentialCellNo]);
                }
        }
        return cells;
}


// ##     ##    ###    #### ##    ##
// ###   ###   ## ##    ##  ###   ##
// #### ####  ##   ##   ##  ####  ##
// ## ### ## ##     ##  ##  ## ## ##
// ##     ## #########  ##  ##  ####
// ##     ## ##     ##  ##  ##   ###
// ##     ## ##     ## #### ##    ##


int main (int argc, const char * argv[])
{

        int wirePitch = 2;
        int wireLength = 1000;
        int wiresPerPlane = ((argc>1) ? strtol(argv[1],NULL,10) : 3);
        int noOfPlanes = 3;

        std::vector< std::vector<Polygon_2> > grid = generate3PlaneGeometry(wirePitch,wireLength,wiresPerPlane,noOfPlanes);
//         std::vector< std::vector<Polygon_2> > grid = generate2PlaneGeometry(wirePitch,wireLength,wiresPerPlane,noOfPlanes);

        std::vector< std::vector<int> > cells = generateCells(grid);

        std::cout << cells.size() << std::endl;

        // for(size_t i = 0; i < cells.size(); i++) {
        //         for (size_t j = 0; j < cells[i].size(); j++) {
        //                 std::cout << cells[i][j] << "\t";
        //         }
        //         std::cout << std::endl;
        // }

}
