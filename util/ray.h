#ifndef RAY_H
#define RAY_H

#include "vec3.cpp"

class ray {
	private:
		vec3 o;
		vec3 d;

	public:
		ray();
		ray(const vec3& origin, const vec3& direction);

		vec3 direction() const;
		vec3 origin() const;
		vec3 at(double t) const;
};

#endif
