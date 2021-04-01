#include "plane.h"

/* Determines if a ray intersects a plane.
*	@r: Ray to cast
*	@t_min: min value of t
*	@t_max: max value of t
*	@rec: The hit record to store the info
*	returns true if the ray intersects the plane, false otherwise.
*/
bool plane::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	// (p-a) . n = 0
	// (o + td - a) . n = 0
	// t = (an - on)/dn = (a-o)n/dn
	vec3 o = r.origin();
	vec3 d = r.direction();
	double denom = dot(d,n);
	//std::cout << denom << std::endl;
	if (denom > 1e-6 || denom < -1e-6) {
		double t = dot((p - o),n)/denom;
		if (t < 0) return false;
		rec.t = t;
    	rec.p = r.at(rec.t);
    	rec.n = normalize(n);
		rec.kd = kd;
		//std::cout << "here" << std::endl;
		return true;
	}
	return false;
}

/*	Constructs a bounding box for a sphere.
*	@time0: t0 time interval for moving objects
*	@time1: t1 time interval for moving objects
*	@output_box: output bounding box
*	Returns an AABB.
*/
bool plane::bounding_box(double time0, double time1, aabb& output_box) const {
	return true;
}
