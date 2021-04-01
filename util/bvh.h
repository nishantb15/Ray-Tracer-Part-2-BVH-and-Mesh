#ifndef BVH_H
#define BVH_H

#include "util.h"

#include "hittable.h"
#include "hittable_list.h"
#include <algorithm>


class bvh_node : public hittable {
    public:
        bvh_node();

        bvh_node(const hittable_list& list, double time0, double time1, int k)
            : bvh_node(list.objects, 0, list.objects.size(), time0, time1, k)
        {}

        bvh_node(
            const std::vector<shared_ptr<hittable>>& src_objects,
            size_t start, size_t end, double time0, double time1, int k);

        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

        virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;

    public:
        shared_ptr<hittable> left;
        shared_ptr<hittable> right;
        aabb box;
		int k;
};

/*	Constructs a bounding box for a BVH.
*	@time0: t0 time interval for moving objects
*	@time1: t1 time interval for moving objects
*	@output_box: output bounding box
*	Returns an AABB.
*/
bool bvh_node::bounding_box(double time0, double time1, aabb& output_box) const {
    output_box = box;
    return true;
}

/*	Determines if a ray hits the BVH.
*	@r: Ray to test
*	@t_min: min value of t
*	@t_max: max value of t
*	@rec: hit record to store the data
*	Returns true if ray hits BVH, false otherwise.
*/
bool bvh_node::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	//std::cout << "first here" << std::endl;    
	if (!box.hit(r, t_min, t_max))
        return false;

    bool hit_left = left->hit(r, t_min, t_max, rec);
    bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left || hit_right;
}

/* Used to sort boxes based on an axis
*	@a: The first box
*	@b: The second box
*	@axis: The axis to compare on
*	returns true if a < b on the axis = axis
*/
inline bool box_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b, int axis) {
    aabb box_a;
    aabb box_b;

    if (!a->bounding_box(0,0, box_a) || !b->bounding_box(0,0, box_b))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    return box_a.min()[axis] < box_b.min()[axis];
}

/* These 3 functions are used to sort bounding boxes
*	@a: The first box
*	@b: The second box
*	returns true if box_compare(a,b,n) is true where n is the integer corresponding to an axis
*/
bool box_x_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
    return box_compare(a, b, 0);
}

bool box_y_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
    return box_compare(a, b, 1);
}

bool box_z_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
    return box_compare(a, b, 2);
}

/*	Constructor for BVH
*	@src_objects: The objects in the world
*	@start: the index to start at (inclusive)
*	@end: The index to end at (exclusive)
*	@time0: t0 for moving objects
*	@time1: t1 for moving objects
*	@k: max depth to recurse
*/
bvh_node::bvh_node(const std::vector<shared_ptr<hittable>>& src_objects, size_t start, size_t end, double time0, double time1, int k) {
    auto objects = src_objects; // Create a modifiable array of the source scene objects
	if (k <= 0) {
		// we've reached the max depth, stop recursing
		aabb box_left, box_right;
		if (start == end-1) {
			left = right = objects[start];
		} else {
			left = make_shared<hittable_list>(objects, start, end-1);
			right = make_shared<hittable_list>(objects,end-1,end);
		}
		if (  !left->bounding_box (time0, time1, box_left) || !right->bounding_box(time0, time1, box_right))
        	std::cerr << "No bounding box in bvh_node constructor.\n";

    	box = surrounding_box(box_left, box_right);
		return;
	}

    int axis = random_int(0,2);
    auto comparator = (axis == 0) ? box_x_compare
                    : (axis == 1) ? box_y_compare
                                  : box_z_compare;

    size_t object_span = end - start;

	//std::cout << object_span << " = object_span" << std::endl;
    if (object_span == 1) {
        left = right = objects[start];
    } else if (object_span == 2) {
        if (comparator(objects[start], objects[start+1])) {
            left = objects[start];
            right = objects[start+1];
        } else {
            left = objects[start+1];
            right = objects[start];
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span/2;
        left = make_shared<bvh_node>(objects, start, mid, time0, time1, k-1);
        right = make_shared<bvh_node>(objects, mid, end, time0, time1, k-1);
    }

    aabb box_left, box_right;

    if (  !left->bounding_box (time0, time1, box_left)
       || !right->bounding_box(time0, time1, box_right)
    )
        std::cerr << "No bounding box in bvh_node constructor.\n";

    box = surrounding_box(box_left, box_right);
	//std::cout << "boxmin = " << box.min() << std::endl;
	//std::cout << "boxmax = " << box.max() << std::endl;
}
#endif
