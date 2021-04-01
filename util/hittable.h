#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "aabb.h"

struct hit_record {
    vec3 p;
    vec3 n;
    double t;
	vec3 kd;
	vec3 ks;
	int v1i;
	int v2i;
	int v3i;
};

class hittable {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
		virtual bool bounding_box(double time0, double time1, aabb& output_box) const = 0;
};

#endif
