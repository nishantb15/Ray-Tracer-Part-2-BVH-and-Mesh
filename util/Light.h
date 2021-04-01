#ifndef LIGHT_H
#define LIGHT_H

class Light {
	public:
		Light() {}
		Light(vec3 lightPos, vec3 ldu, vec3 lsu) : lightPosition(lightPos), ld(ldu), ls(lsu) {};
		vec3 getPosition() {
			return lightPosition;
		}

		vec3 getDiffuse() {
			return ld;
		}

		vec3 getSpecular() {
			return ls;
		}

	private:
		vec3 lightPosition;
		vec3 ld;
		vec3 ls;
};
#endif
