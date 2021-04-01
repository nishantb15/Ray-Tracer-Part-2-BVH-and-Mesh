#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
        sphere() : kd(vec3(0,0,0)) {}
        sphere(vec3 cen, double r, vec3 kdu) : center(cen), radius(r), kd(kdu) {};

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
		virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;

    public:
        vec3 center;
        double radius;
		vec3 kd;
};

#endif
