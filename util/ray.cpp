#include <cmath>
#include <iostream>
#include "ray.h"

/* Empty Constructor
*/
ray::ray() {
	o = vec3();
	d = vec3();
}

/* Constructor
*	@origin: origin point of the ray
*	@direction: direction of the ray
*/
ray::ray(const vec3& origin, const vec3& direction) {
	o = origin;
	d = direction;
}

/*
*	Returns the direction of the ray.
*/
vec3 ray::direction() const {
	return d;
}

/*
* Returns the origin of the ray.
*/
vec3 ray::origin() const {
	return o;
}

/* Gets the point on the ray at time t.
*	@t: the time value
*	returns the point on the ray at time t.
*/
vec3 ray::at(double t) const {
	return o + (t*d);
}
