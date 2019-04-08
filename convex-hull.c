/* * * * * * *
 * Implementation of the Inside Hull algorithm for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2019
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Insert Name Here>
 */

//                   WRITE YOUR IMPLEMENTATION HERE
//
// You should fill in the function definitions for orientation() and
// inside_hull() in this file.
//
// Don't be shy to add any extra functions or types you may need.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "convex-hull.h"
#include "deque.h"

#define ORIENT_R 'r'
#define ORIENT_L 'l'
#define ORIENT_C 'c'

void initialise_queue(Deque *deq, Point *p);
bool has_colinear_points(Point *polygon, int n);
bool top_two_turns_left(Deque *deq, Point third_point);
bool bot_two_turns_left(Deque *deq, Point third_point);
void write_to_hull(Deque *deq, Point* hull);
// Returns the orientation of Point p2 in relation to the line segment p0p1.
// If p2 is to the left of p0p1 then it returns LEFT ('l'), if p2 is to the
// right it returns RIGHT ('r').
// If p0, p1 and p2 are collinear then COLLINEAR ('c') is returned.
char orientation(Point p0, Point p1, Point p2) {
  // u is vector from p0 to p1
  Point u;
  u.x = p1.x - p0.x;
  u.y = p1.y - p0.y;

  // v is vector from p0 to p2
  Point v;
  v.x = p2.x - p0.x;
  v.y = p2.y - p0.y;

  float cross_uv = point_cross_product(u, v);
  if (cross_uv > 0 ) {
    return ORIENT_L;
  } else if (cross_uv < 0) {
    return ORIENT_R;
  } else {
    return ORIENT_C;
  }
}

// Takes a polygon (i.e. an array of points) given in counter-clockwise order
// with n points.
//
// Stores the points of the convex hull into the hull array (the last point
// should NOT be the same as the first point), and returns the number of
// points which are in the convex hull.
//
// If three successive points in the polygon are collinear then the algorithm
// should terminate and COLLINEAR_POINTS should be returned.
//
// If an error occurs this function should return INSIDE_HULL_ERROR.
int inside_hull(Point *polygon, int n, Point *hull) {
  if (n < 3) {
    fprintf(stderr, "Error: Insufficient number of points in polygon");
    return(INSIDE_HULL_ERROR);
  }

  if (has_colinear_points(polygon, n)) {
    fprintf(stderr, "Error: Colinear Points Found");
    return(COLLINEAR_POINTS);
  }

  Deque *deq = new_deque();

  initialise_queue(deq, polygon);

  int i = 3;
  while (i < n) {
    Point currentPoint = polygon[i];

    if (top_two_turns_left(deq, currentPoint) && bot_two_turns_left(deq, currentPoint)) {
      i++;
      continue;
    }

    while (top_two_turns_left(deq, currentPoint) == false) {
      deque_pop(deq);
    }
    deque_push(deq, currentPoint);

    while (bot_two_turns_left(deq, currentPoint) == false) {
      deque_remove(deq);
    }
    deque_insert(deq, currentPoint);
    i++;
  }

  deque_write_to_hull(deq, hull);
  return (deque_size(deq) - 1);

}


//Checks for colinear points in list of points
bool has_colinear_points(Point *polygon, int n) {
  for (int i = 0; i < n; i++) {
    char orient = orientation(polygon[i %n], polygon[(i+1)%n], polygon[(i+2)%n]);
    if (orient == ORIENT_C) {
      return true;
    }
  }
  return false;
}

//
void initialise_queue(Deque *deq, Point *p) {
  if(orientation(p[0], p[1], p[2]) == ORIENT_L) {
    // init with {p2 p0 p1 p2}
    deque_insert(deq, p[2]);
    deque_insert(deq, p[1]);
    deque_insert(deq, p[0]);
    deque_insert(deq, p[2]);
  } else {
    // init with {p2 p1 p0 p2}
    deque_insert(deq, p[2]);
    deque_insert(deq, p[0]);
    deque_insert(deq, p[1]);
    deque_insert(deq, p[2]);
  }
}

// Returns true if third point is to the left of the vector from the two bot points of deque
bool bot_two_turns_left(Deque *deq, Point third_point) {
  char turn = orientation(deque_peek_bottom(deq, 0), deque_peek_bottom(deq, 1), third_point);
  if (turn == ORIENT_L) {
    return true;
  }
  return false;
}

// Returns true if third point is to the left of the vector from the two top points of deque
bool top_two_turns_left(Deque *deq, Point third_point) {
  char turn = orientation(deque_peek_top(deq, 1), deque_peek_top(deq, 0), third_point);
  if (turn == ORIENT_L) {
    return true;
  }
  return false;
}

