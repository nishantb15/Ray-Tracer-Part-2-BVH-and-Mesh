#include "sphere.h"

/* Determines if a ray hits a point
*	@r: Ray to cast
*	@t_min: min value of t
*	@t_max: max value of t
*	@rec: The hit record to store the info
*	returns true if the ray intersects the spheres, and false otherwise.
*/
bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	double root = -1000000000000;
    vec3 oc = r.origin() - center;
	double a = dot(r.direction(),r.direction());
	double b = 2* dot(oc, r.direction());
	double c = dot(oc,oc) - radius*radius;

	vec3 d = r.direction();
	double m = 4 * dot(d,d); // 4d^2
	vec3 n1 = oc - (dot(oc,d) * d);
	double n2 = dot(n1,n1);
	double discriminant = m * (radius*radius - n2); 
	//double discriminant = (b*b) - (4*a*c);	// can lead to loss of accuracy

	if (discriminant < 0) {
		return false;
	} else if (discriminant == 0) {
		// one unique solution
		root = -b / (2*a);
		if (root < t_min || t_max < root)
            return false;
	} else {
		// two unique solutions
		root = (-b - sqrt(discriminant))/(2*a);
	
		if (root < t_min || t_max < root) {
			root = (-b + sqrt(discriminant))/(2*a);
			if (root < t_min || t_max < root) {
				return false;
			}
		}
	}

	//std::cout << "root = " << root << std::endl;
    rec.t = root;
    rec.p = r.at(rec.t);
    rec.n = (rec.p - center) / radius;
	rec.kd = kd;
    return true;
}

/*	Constructs a bounding box for a sphere.
*	@time0: t0 time interval for moving objects
*	@time1: t1 time interval for moving objects
*	@output_box: output bounding box
*	Returns an AABB.
*/
bool sphere::bounding_box(double time0, double time1, aabb& output_box) const {
    output_box = aabb(
        center - vec3(radius, radius, radius),
        center + vec3(radius, radius, radius));
    return true;
}
