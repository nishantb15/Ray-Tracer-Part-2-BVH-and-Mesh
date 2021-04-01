#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include "hittable.h"
#include "vec3.h"

class TriangleMesh : public hittable {
	public:
		TriangleMesh(vec3 v1u, vec3 v2u, vec3 v3u, vec3 kdu, vec3 ksu, int v1ii, int v2ii, int v3ii)
		: v1(v1u), v2(v2u), v3(v3u), kd(kdu), ks(ksu), v1i(v1ii), v2i(v2ii), v3i(v3ii) {};

		virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;
		virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;
	private:
		vec3 v1;
		vec3 v2;
		vec3 v3;
		vec3 kd;
		vec3 ks;
		int v1i;
		int v2i;
		int v3i;
};
#endif
