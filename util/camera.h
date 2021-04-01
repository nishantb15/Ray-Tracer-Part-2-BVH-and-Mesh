#ifndef CAMERA_H
#define CAMERA_H

#include "util.h"

class camera {
    public:
		/* Constructor for camera class
		*	@ar: aspect ratio
		*	@c_origin: camera_origin in World space
		*	@lookat: normalized view direction in world space
		*	@up: up direction in world space
		*	@fl: focal length
		*	@o: orthographic or not?
		*/
        camera(double ar, vec3 c_origin, vec3 lookat, vec3 up, double fl, bool o) {
            aspect_ratio = ar;
            d = fl;	
			viewdir = lookat; // viewdir
			camera_origin = c_origin;
			ortho = o;
			this->up = up;
        }

		/* Gets the ray in the direction of x,y,z
		*	@x: x direction
		*	@y: y direction
		*/
        ray get_ray(double x, double y) const {
			vec3 vd = viewdir;
            const vec3 w = -vd/vd.length();
			const vec3 u = (cross(up,w))/(cross(up,w)).length();
			const vec3 v = cross(w,u);
			double z = -d;

			vec3 origin = vec3();
			vec3 dir = vec3();
			if (ortho) {
				origin = vec3(x,y,z);	// camera space
				dir = vec3(0,0,-1);		// world space
			} else {
				// perspective projection
				vec3 pw = (u*x) + (v*y) + (w*z);	// convert to world coordinates
				origin = camera_origin;
				dir = normalize(pw - origin);
			}
			return ray(origin, dir);
        }

    private:
        vec3 camera_origin;
		vec3 up;
		vec3 viewdir;
		double d;
		double aspect_ratio;
		bool ortho;
		
};

/*class camera {
    public:
        camera() {
            auto aspect_ratio = 16.0 / 9.0;
            auto viewport_height = 2.0;
            auto viewport_width = aspect_ratio * viewport_height;
            auto focal_length = 1;

            origin = vec3(0, 0, 0);
            horizontal = vec3(viewport_width, 0.0, 0.0);
            vertical = vec3(0.0, viewport_height, 0.0);
            lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
        }

        ray get_ray(double u, double v) const {
            return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        }

    private:
        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
};*/
#endif
