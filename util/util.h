#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <limits>
#include <memory>

/*vec3 raycast(ray r) {
	double t0,t1 = 0;
	t0 = -100000000000000;
	vec3 center = vec3(0,0,-101);
	int radius = 100;
	if (sphere_hit(center,radius,r,t0)) {
		double x = t0;
		/*
		* vec3 L = lightPos - hitpoint
		* vec3 N = hitpoint - center of sphere
		* Color = ka*la + kd*(L . N)*ld
		*/
		/*return phong(r,x,r.at(x) - center,vec3(0.2,0.3,0.8),vec3(0.2,0.2,1));
	}

	double t3 = 0;
	vec3 n = vec3();
	if (hit_triangle(vec3(100-100-100,0-100,-5), vec3(0-100-100,200-100,-5), vec3(-100-100-100,0-100,-5), r, t3,n)) {
		vec3 kd = vec3(0,0,1);
		return phong(r,t3,n,kd,vec3(1,1,1));
	}

	double t2 = 0;
	n = vec3(0,-1,0);
	if (hit_plane(vec3(0,20,100),n,r,t2)) {
		return phong(r,t2,n,vec3(0,1,0),vec3(1,1,1));
	}

	vec3 unit_direction = normalize(r.direction());
    double t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}*/

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degToRad(double degrees) {
    return degrees * pi / 180.0;
}

#include <cstdlib>

inline double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

inline int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return static_cast<int>(random_double(min, max+1));
}

// Common Headers

#include "ray.h"
#include "vec3.h"

#endif
