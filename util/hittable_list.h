#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
    public:
        hittable_list() {}
        hittable_list(shared_ptr<hittable> object) { add(object); }
	
		/*	constructs a hittable list
		*	@src_objects: Vector to initialize from
		*	@start: start index of vector (inclusive)
		*	@end: end index of vector (exclusive)
		*/
		hittable_list(std::vector<shared_ptr<hittable>>& src_objects, int start, int end) {
			for (int i = start; i < end; i++) {
				add(src_objects[i]);
			}
		}

        void clear() { objects.clear(); }
        void add(shared_ptr<hittable> object) { objects.push_back(object); }

        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;
		virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;


    public:
        std::vector<shared_ptr<hittable>> objects;
};

#endif
