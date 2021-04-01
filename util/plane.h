#ifndef PLANE_H
#define PLANE_H

#include "hittable.h"
#include "vec3.h"

class plane : public hittable {
    public:
        plane() : kd(vec3(0,0,0)) {}
        plane(vec3 pu, vec3 nu, vec3 kdu) : p(pu), n(nu), kd(kdu) {};

        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;
		virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;

    public:
        vec3 p;
		vec3 n;
		vec3 kd;
};

#endif
