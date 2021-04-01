#include "triangle.h"

/* Determines if a ray intersects a triangle using Moeller-Trumbore
*	intersection algorithm.  v1,v2,v3 must be defined in a CCW order
*	@r: Ray to cast
*	@t_min: min value of t
*	@t_max: max value of t
*	@rec: The hit record to store the info
*	returns true if ray intersects the triangle, false otherwise
*/
bool triangle::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	double epsilon = 1e-5;
	vec3 edge1 = v2 - v1;
	vec3 edge2 = v3 - v1;
	vec3 n = cross(edge1,edge2);
	vec3 h = cross(r.direction(),edge2);
	double a = dot(edge1,h);
	if (a > -epsilon && a < epsilon) {
		// ray is parallel to triangle
		return false;
	}

	double f = 1.0/a;
	vec3 s = r.origin() - v1;
	double u = f * dot(s,h);
	if (u < 0 || u > 1) {
		return false;
	}

	vec3 q = cross(s,edge1);
	double v = f * dot(r.direction(),q);
	if (v < 0 || u + v > 1) {
		return false;
	}

	double t = f * dot(edge2,q);
	if (t < 0 || t < t_min || t_max < t) {
		return false;
	}
	if (t > epsilon) {
		rec.t = t;
    	rec.p = r.at(rec.t);
    	rec.n = normalize(n);
		rec.kd = kd;
		rec.ks = ks;
		return true;
	}

	return false;
}

/*	Constructs a bounding box for a triangle.
*	@time0: t0 time interval for moving objects
*	@time1: t1 time interval for moving objects
*	@output_box: output bounding box
*	Returns an AABB.
*/
bool triangle::bounding_box(double time0, double time1, aabb& output_box) const {
	double minx = fmin(v1[0],fmin(v2[0],v3[0]));
	double miny = fmin(v1[1],fmin(v2[1],v3[1]));
	double minz = fmin(v1[2],fmin(v2[2],v3[2]));

	double maxx = fmax(v1[0],fmax(v2[0],v3[0]));
	double maxy = fmax(v1[1],fmax(v2[1],v3[1]));
	double maxz = fmax(v1[2],fmax(v2[2],v3[2]));
	double eps = 1e-5;
	
	vec3 min = vec3(minx-eps,miny-eps,minz-eps);
	vec3 max = vec3(maxx+eps,maxy+eps,maxz+eps);
	//std::cout << "min = " << min << std::endl;
	//std::cout << "max = " << max << std::endl;
	output_box = aabb(min,max);
	return true;
}
