#ifndef VEC3_H
#define VEC3_H
class vec3 {
	private:
		double v[3];

	public:
		vec3();
		vec3(double v1, double v2, double v3);
		//vec3(vec3& v2);
		double x();
		double y();
		double z();
		double length();
		double length_squared();
		
		vec3 operator-() const;
        double operator[](int i) const;
        double& operator[](int i);

        vec3& operator+=(const vec3 &v1);
        vec3& operator*=(const double t);
        vec3& operator/=(const double t);
};

std::ostream& operator<<(std::ostream &out, const vec3 &v1);
vec3 operator+(const vec3 &u1, const vec3 &u2);
vec3 operator-(const vec3 &u1, const vec3 &u2);
vec3 operator*(const vec3 &u1, const vec3 &u2);
vec3 operator*(double t, const vec3 &v1);
vec3 operator*(const vec3 &v, double t);
vec3 operator/(vec3 v, double t);
double dot(const vec3 &u1, const vec3 &u2);
vec3 cross(const vec3 &u1, const vec3 &u2);
vec3 normalize(vec3 v);

// Affine transformations
vec3 translate(vec3 point, double dx, double dy, double dz);
vec3 uniformTranslate(vec3 point, double d);
vec3 scale(vec3 point, double a, double b, double c);
vec3 uniformScale(vec3 point, double s);
vec3 rotateX(vec3 point, double theta);
vec3 rotateY(vec3 point, double theta);
vec3 rotateZ(vec3 point, double theta);
vec3 rotate(vec3 point, double theta, int axis);
vec3 rotateAboutPoint(vec3 point, double theta, int axis);
#endif
