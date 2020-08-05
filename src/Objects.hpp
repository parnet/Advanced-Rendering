#include <iostream>                     // C++ Standard I/O
#include <cmath>                        // C++ Standard Mathematical Functions

#define  GLM_FORCE_RADIANS

#include <glm/glm.hpp>                  // Vector/Matrix Functions by GLM
#include <glm/gtc/matrix_transform.hpp> // Matrix Functions by GLM
#include "../libs/lodepng/lodepng.h"                // PNG File Handling by loadpng
#include "Polysolv.h"                   // Polynom Root Finder found somewhere in the Internet
#include "environment.h"


using namespace std;

/* Constant Declaration */
const float pi = 3.141592;

/* Type Declarations   */
using namespace std;

/* Class Definitions   */
class Color {
public:
    double r = 0.0;     // 0 <= r <= 1
    double g = 0.0;     // 0 <= g <= 1
    double b = 0.0;     // 0 <= b <= 1

    Color() = default;

    Color(double red, double green, double blue) {
        // todo if color < 0.0 ?
        r = (red < 1.0) ? red : 1.0;
        g = (green < 1.0) ? green : 1.0;
        b = (blue < 1.0) ? blue : 1.0;
    };
};


class GeometricObject {
private:
protected:
public:
    double phong_factor = 1.0;
    double * cache = nullptr;
    int cachesize = 0;
    glm::mat4 inverse_modelling_matrix = glm::mat4(1.0f);
    glm::mat4 normal_matrix = glm::mat4(1.0f);
    Color mat_color = Color(1.0, 1.0, 1.0);

    virtual int trace_ray(glm::vec4 origin, glm::vec4 direction) = 0;

    virtual glm::vec4 get_normal(glm::vec4 origin, glm::vec4 direction, double t) = 0;

    virtual void clean() = 0;
};

class Torus : public GeometricObject {
private:
    double rad_R = 1.0;
    double rad_r = 0.1;

public:
    Torus() = default;

    explicit Torus(double r) {
        rad_r = r;
    };

    int trace_ray(glm::vec4 origin, glm::vec4 direction) override {
        cache = new double[5];
        int number; //Number of intersections
        double coefficient[5];
        double root[4] = {0.0, 0.0, 0.0, 0.0};

        origin = inverse_modelling_matrix * origin;       //Transformation aus der Szene
        direction = inverse_modelling_matrix * direction;    // in die Objektkoordinaten
        //cout << "origin: " << origin.x << "  " << origin.y << "  "  << origin.z << "  " << endl;
        //cout << "direction: "  << direction.x  << "  " << direction.y  << "  "  << direction.z  << "  " << endl;

        /* Calculate terms for intersection calculation */
        double a2 = origin.x * origin.x
                    + origin.y * origin.y
                    + origin.z * origin.z;
        double u2 = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;
        double au = origin.x * direction.x + origin.y * direction.y + origin.z * direction.z;

        double r2 = rad_r * rad_r;
        double R2 = rad_R * rad_R;

        /* Coefficients of intersection polynom                             */
        /* see correction of Glassner, An Introduction of Raytracing, p. 93 */
        coefficient[0] = u2 * u2;
        coefficient[1] = 4 * au * u2;
        coefficient[2] = 2 * u2 * (a2 - R2 - r2)
                         + 4 * au * au
                         + 4 * R2 * direction.z * direction.z;
        coefficient[3] = 4 * au * (a2 - R2 - r2)
                         + 8 * R2 * origin.z * direction.z;
        coefficient[4] = (a2 - R2 - r2) * (a2 - R2 - r2)
                         - 4 * R2 * (r2 - origin.z * origin.z);

        number = Solve_Polynomial(4, coefficient, root, TRUE, 1.0e-5);
        if (number > 0) {
            for (unsigned char i = 0; i < number; i++)
                cache[i] = root[i];
            //printf ("Anzahl: %d  Schnittpunkte: %f, %f, %f, %f\n", number, t[0], t[1], t[2], t[3]);
        };
        this->cachesize = number;
        return number;
    };

    glm::vec4 get_normal(glm::vec4 origin, glm::vec4 direction, double t) override {
        glm::vec4 normal = glm::vec4(0.0, 0.0, 0.0, 0.0);
        glm::vec4 intersection;
        glm::vec4 temp; // Intersections

        origin = inverse_modelling_matrix * origin;       //Transformation aus der Szene
        direction = inverse_modelling_matrix * direction;    // in die Objektkoordinaten

        /* Calculate nearest intersection  */
        intersection.x = origin.x + direction.x * t;
        intersection.y = origin.y + direction.y * t;
        intersection.z = origin.z + direction.z * t;
        // cout << "Anzahl: "  << number << endl;
        // cout << "t: " << t[0] << "  " << t[1] << "  " << t[2] << endl;
        // cout << "Schnitt: " << intersection.x << " " << intersection.y << " " << intersection.z << endl;

        /* To calculate a Torus normal:
            1. Project intersection onto xy-plane,
            2. Scale it, so that it is projected on the perimeter with radius R,
            3. The normal is the difference vector between intersection and projection,
            4. Scale normal with radius r (Normalization).              */
        double dist_xy_plane = sqrt(intersection.x * intersection.x
                                    + intersection.y * intersection.y);
        temp.x = intersection.x / (dist_xy_plane / rad_R);
        temp.y = intersection.y / (dist_xy_plane / rad_R);
        normal.x = intersection.x - temp.x;
        normal.y = intersection.y - temp.y;
        normal.z = intersection.z;
        normal = glm::normalize(
                normal_matrix * normal);           //Transformation in die Szene mit transponiert-inverser Matrix
        //cout << " "<< normal.x << " " << normal.y << " " << normal.z << endl;
        return normal;
    };

    void clean() override {
        delete this->cache;
    };
};

class Sphere : public GeometricObject {
private:
public:
    Sphere() = default;

    int trace_ray(glm::vec4 origin, glm::vec4 direction) override {
        cache = new double[2];
        int number; //Number of intersections
        double coefficient[3];
        double root[2] = {0.0, 0.0};
        double tmp;
        origin = inverse_modelling_matrix * origin; //Transformation aus der Szene
        direction = inverse_modelling_matrix * direction; // in die Objektkoordinaten

        /* Calculate terms for intersection calculation */

        // t^2 * a2 + 2*t*au + a2 - 1 = 0
        double a2 = origin.x * origin.x
                    + origin.y * origin.y
                    + origin.z * origin.z;

        double u2 = direction.x * direction.x
                    + direction.y * direction.y
                    + direction.z * direction.z;

        double au = origin.x * direction.x
                    + origin.y * direction.y
                    + origin.z * direction.z;

        /* Coefficients of intersection polynom             see lecture notes                */
        coefficient[0] = u2;
        coefficient[1] = 2 * au;
        coefficient[2] = a2 - 1;
        number = Solve_Polynomial(2, coefficient, root, TRUE, 1.0e-5);
        if (number > 0) {
            if (number == 1){
                root[1] = root[0]; // assign point for csg interval (open, close)
                number++;
            } else if (root[0] > root[1]) { // swap so that t[i] < t[j] for all i < j
                tmp = root[1];
                root[1] = root[0];
                root[0] = tmp;
            };

            for (unsigned char i = 0; i < number; i++)
                cache[i] = root[i];
            //printf ("Anzahl: %d  Schnittpunkte: %f, %f, %f, %f\n", number, t[0], t[1], t[2], t[3]);
        };
        this->cachesize = number;
        return number;
    };

    glm::vec4 get_normal(glm::vec4 origin, glm::vec4 direction, double t) override {
        glm::vec4 normal = glm::vec4(0.0, 0.0, 0.0, 0.0);
        glm::vec4 intersection;
        glm::vec4 temp;// Intersections

        origin = inverse_modelling_matrix * origin; //Transformation aus der Szene
        direction = inverse_modelling_matrix * direction; // in die Objektkoordinaten

        /* Calculate nearest intersection  */
        intersection.x = origin.x + direction.x * t;
        intersection.y = origin.y + direction.y * t;
        intersection.z = origin.z + direction.z * t;
        // cout << "Anzahl: "  << number << endl;
        // cout << "t: " << t[0] << "  " << t[1] << "  " << t[2] << endl;
        // cout << "Schnitt: " << intersection.x << " " << intersection.y << " " << intersection.z << endl;
        /* Calculate a Sphere normal */
        normal.x = intersection.x;
        normal.y = intersection.y;
        normal.z = intersection.z;
        normal = glm::normalize(
                normal_matrix * normal);           //Transformation in die Szene mit transponiert-inverser Matrix

        //cout << " "<< normal.x << " " << normal.y << " " << normal.z << endl;
        return normal;
    };

    void clean() override {
        delete this->cache;
    };
};

class Cone : public GeometricObject {
private:
public:
    Cone() = default;

    int trace_ray(glm::vec4 origin, glm::vec4 direction) override {
        cache = new double[4];

        int number; //Number of intersections
        double coefficient[3];
        double root[2] = {0.0, 0.0};
        double dummy;
        origin = inverse_modelling_matrix * origin;       //Transformation aus der Szene
        direction = inverse_modelling_matrix * direction;    // in die Objektkoordinaten
        //cout << "origin: " << origin.x << "  " << origin.y << "  "  << origin.z << "  " << endl;
        //cout << "direction: "  << direction.x  << "  " << direction.y  << "  "  << direction.z  << "  " << endl;

        /* Calculate terms for intersection calculation */
        double a2 = origin.x * origin.x
                    + origin.y * origin.y
                    - origin.z * origin.z;

        double u2 = direction.x * direction.x
                    + direction.y * direction.y
                    - direction.z * direction.z;

        double au = origin.x * direction.x
                    + origin.y * direction.y
                    - origin.z * direction.z;

        /* Coefficients of intersection polynom             see lecture notes                */
        coefficient[0] = u2;
        coefficient[1] = 2 * au;
        coefficient[2] = a2;
        number = Solve_Polynomial(2, coefficient, root, TRUE, 1.0e-5);

        // do not use values for the upper half of the cone and do not extend further than a const value
        if (number > 1) {
            if (root[1] < 0.0 || origin.z + root[1] * direction.z > 0.0  || origin.z + root[1] * direction.z < -1.0) {
                root[1] = 0.0;
                number--;
            }
        }
        if (number > 0) {
            if (root[0] < 0.0 || origin.z + root[0] * direction.z > 0.0  || origin.z + root[0] * direction.z < -1.0 ) {
                root[0] = 0.0;
                number--;
            }
        }


        double tc = (-1.0 - origin.z) / direction.z;
        double ia = origin.x + tc*direction.x;
        double ib = origin.y + tc*direction.y;
        if(ia*ia + ib*ib <= 1.0){
            root[number] = tc;
            //std::cout << "x1." << tc;
            number++;
        }




        if(number == 1){
            root[1] = root[0];
            number++;
        }
        if(number > 1) { // sort intersectionpoints to get the minimal distance to the viewer
            if (root[0] > root[1]) {
                //std::cout << "#";
                dummy = root[1];
                root[1] = root[0];
                root[0] = dummy;
            } else {
                //std::cout << "!";
            }
        }
        if(number > 0){
            for (unsigned char i = 0; i < number; i++) {
                cache[i] = root[i];
            }

            if(origin.z + root[0] * direction.z >= 0.0) {
                //std::cout << root[0] << "\t" << origin.z + root[0] * direction.z << std::endl;
                //printf ("Anzahl: %d  Schnittpunkte: %f, %f, %f, %f\n", number, cache[0], cache[1], cache[2], cache[3]);

            }
        }
        this->cachesize = number;
        return number;
    };

    glm::vec4 get_normal(glm::vec4 origin, glm::vec4 direction, double t) override {
        glm::vec4 normal = glm::vec4(0.0, 0.0, 0.0, 0.0);
        glm::vec4 intersection;
        glm::vec4 temp;// Intersections

        //print("org", origin);
        //print("dir", direction);
        //std::cout << t << std::endl;
        origin = inverse_modelling_matrix * origin; //Transformation aus der Szene
        direction = inverse_modelling_matrix * direction; // in die Objektkoordinaten


        /* Calculate nearest intersection  */
        intersection.x = origin.x + direction.x * t;
        intersection.y = origin.y + direction.y * t;
        intersection.z = origin.z + direction.z * t;

        //print("intr",intersection);
        /* Calculate a Cone normal */
        if(intersection.z <= -1.0 + 1e-7){
            normal.x = 0;
            normal.y = 0;
            normal.z = -1;
        } else {
            normal.x = intersection.x;
            normal.y = intersection.y;
            normal.z = -intersection.z;
        }
        //print("nrm", normal);
        //print("nrmm", normal_matrix);
        normal = glm::normalize(
                normal_matrix * normal);           //Transformation in die Szene mit transponiert-inverser Matrix
        //print("nrm", normal);
        return normal;
    };

    void clean() override {
        delete this->cache;
    };
};

class Cube : public GeometricObject {
private:
public:
    Cube() = default;

    int trace_ray(glm::vec4 origin, glm::vec4 direction) override {
        cache = new double[4];
        int number; //Number of intersections
        double tmp;
        origin = inverse_modelling_matrix * origin;       //Transformation aus der Szene
        direction = inverse_modelling_matrix * direction;    // in die Objektkoordinaten
        //cout << "origin: " << origin.x << "  " << origin.y << "  "  << origin.z << "  " << endl;
        //cout << "direction: "  << direction.x  << "  " << direction.y  << "  "  << direction.z  << "  " << endl;

        /* Calculate terms for intersection calculation */
        number = 0;
        double ia;
        double ib;
        double tc;

        tc = (1.0 - origin.x) / direction.x;
        ia = origin.y + tc*direction.y;
        ib = origin.z + tc*direction.z;
        if(ia >= 0 && ia <= 1.0 && ib >= 0 && ib <= 1.0){
            cache[number] = tc;
            //std::cout << "x1." << tc;
            number++;
        }

        tc = (0.0 - origin.x) / direction.x;
        ia = origin.y + tc*direction.y;
        ib = origin.z + tc*direction.z;
        if(ia >= 0 && ia <= 1.0 && ib >= 0 && ib <= 1.0){
            cache[number] = tc;
            //std::cout << "x0.";
            number++;
        }


        tc = (1.0 - origin.y) / direction.y;
        ia = origin.x + tc*direction.x;
        ib = origin.z + tc*direction.z;
        if(ia >= 0 && ia <= 1.0 && ib >= 0 && ib <= 1.0){
            cache[number] = tc;
            //std::cout << "y1.";
            number++;
        }

        tc = (0.0 - origin.y) / direction.y;
        ia = origin.x + tc*direction.x;
        ib = origin.z + tc*direction.z;
        if(ia >= 0 && ia <= 1.0 && ib >= 0 && ib <= 1.0){
            cache[number] = tc;
            //std::cout << "y0.";
            number++;
        }


        tc = (1.0 - origin.z) / direction.z;
        ia = origin.y + tc*direction.y;
        ib = origin.x + tc*direction.x;
        if(ia >= 0 && ia <= 1.0 && ib >= 0 && ib <= 1.0){
            cache[number] = tc;
            //std::cout << "z1.";
            number++;
        }

        tc = (0.0 - origin.z) / direction.z;
        ia = origin.y + tc*direction.y;
        ib = origin.x + tc*direction.x;
        if(ia >= 0 && ia <= 1.0 && ib >= 0 && ib <= 1.0){
            cache[number] = tc;
            //std::cout << "z0.";
            number++;
        }

        if (number > 0) {
            //printf ("Anzahl: %d  Schnittpunkte: %f, %f, %f, %f\n", number, t[0], t[1], t[2], t[3]);
            if(cache[1] < cache[0]){
                tmp = cache[1];
                cache[1] = cache[0];
                cache[0] = tmp;
            }
        };
        this->cachesize = number;
        return number;
    };

    glm::vec4 get_normal(glm::vec4 origin, glm::vec4 direction, double t) override {
        double eps = 1e-4;
        glm::vec4 normal = glm::vec4(0.0, 0.0, 0.0, 0.0);
        glm::vec4 intersection;
        glm::vec4 temp;// Intersections

        origin = inverse_modelling_matrix * origin; //Transformation aus der Szene
        direction = inverse_modelling_matrix * direction; // in die Objektkoordinaten

        /* Calculate nearest intersection  */
        intersection.x = origin.x + direction.x * t;
        intersection.y = origin.y + direction.y * t;
        intersection.z = origin.z + direction.z * t;

        //print(intersection);
        normal.x = +0.0;
        normal.y = +0.0;
        normal.z = +0.0;

        if (fabs(intersection.x) < eps) { // x component approx 0.0
            normal.x = -1.0;
        } else if (fabs(intersection.x - 1.0) < eps) { // xcomponent approx 1.0
            normal.x = +1.0;
        } else if (fabs(intersection.y < eps)) {
            normal.y = -1.0;
        } else if (fabs(intersection.y - 1.0) < eps) {
            normal.y = +1.0;
        } else if (fabs(intersection.z < eps)) {
            normal.z = -1.0;
        } else if (fabs(intersection.z - 1.0) < eps) {
            normal.z = +1.0;
        }
        //print(normal);
        /* Calculate a Sphere normal */
        normal = glm::normalize(normal_matrix * normal);           //Transformation in die Szene mit transponiert-inverser Matrix
        return normal;
    };

    void clean() override {
        delete this->cache;
    };
};




class CenteredCube : public GeometricObject {
private:
public:
    CenteredCube() = default;

    int trace_ray(glm::vec4 origin, glm::vec4 direction) override {
        cache = new double[4];
        int number; //Number of intersections
        double tmp;
        origin = inverse_modelling_matrix * origin;       //Transformation aus der Szene
        direction = inverse_modelling_matrix * direction;    // in die Objektkoordinaten
        //cout << "origin: " << origin.x << "  " << origin.y << "  "  << origin.z << "  " << endl;
        //cout << "direction: "  << direction.x  << "  " << direction.y  << "  "  << direction.z  << "  " << endl;

        /* Calculate terms for intersection calculation */
        number = 0;
        double ia;
        double ib;
        double tc;

        double upper = 1.0;
        double lower = -1.0;

        tc = (upper - origin.x) / direction.x;
        ia = origin.y + tc*direction.y;
        ib = origin.z + tc*direction.z;
        if(ia >=  lower && ia <= upper && ib >= lower && ib <= upper){
            cache[number] = tc;
            //std::cout << "x1." << tc;
            number++;
        }

        tc = (lower - origin.x) / direction.x;
        ia = origin.y + tc*direction.y;
        ib = origin.z + tc*direction.z;
        if(ia >= lower && ia <= upper && ib >= lower && ib <= upper){
            cache[number] = tc;
            //std::cout << "x0.";
            number++;
        }


        tc = (upper - origin.y) / direction.y;
        ia = origin.x + tc*direction.x;
        ib = origin.z + tc*direction.z;
        if(ia >= lower && ia <= upper && ib >= lower && ib <= upper){
            cache[number] = tc;
            //std::cout << "y1.";
            number++;
        }

        tc = (lower - origin.y) / direction.y;
        ia = origin.x + tc*direction.x;
        ib = origin.z + tc*direction.z;
        if(ia >= lower && ia <= upper && ib >= lower && ib <= upper){
            cache[number] = tc;
            //std::cout << "y0.";
            number++;
        }


        tc = (upper - origin.z) / direction.z;
        ia = origin.y + tc*direction.y;
        ib = origin.x + tc*direction.x;
        if(ia >= lower && ia <= upper && ib >= lower && ib <= upper){
            cache[number] = tc;
            //std::cout << "z1.";
            number++;
        }

        tc = (lower - origin.z) / direction.z;
        ia = origin.y + tc*direction.y;
        ib = origin.x + tc*direction.x;
        if(ia >= lower && ia <= upper && ib >= lower && ib <= upper){
            cache[number] = tc;
            //std::cout << "z0.";
            number++;
        }

        if (number > 0) {
            //printf ("Anzahl: %d  Schnittpunkte: %f, %f, %f, %f\n", number, t[0], t[1], t[2], t[3]);
            if(cache[1] < cache[0]){
                tmp = cache[1];
                cache[1] = cache[0];
                cache[0] = tmp;
            }
        };
        this->cachesize = number;
        return number;
    };

    glm::vec4 get_normal(glm::vec4 origin, glm::vec4 direction, double t) override {
        double eps = 1e-4;
        glm::vec4 normal = glm::vec4(0.0, 0.0, 0.0, 0.0);
        glm::vec4 intersection;
        glm::vec4 temp;// Intersections

        origin = inverse_modelling_matrix * origin; //Transformation aus der Szene
        direction = inverse_modelling_matrix * direction; // in die Objektkoordinaten

        /* Calculate nearest intersection  */
        intersection.x = origin.x + direction.x * t;
        intersection.y = origin.y + direction.y * t;
        intersection.z = origin.z + direction.z * t;

        //print(intersection);
        normal.x = +0.0;
        normal.y = +0.0;
        normal.z = +0.0;

        if (fabs(intersection.x+1.0) < eps) { // x component approx 0.0
            normal.x = -1.0;
        } else if (fabs(intersection.x - 1.0) < eps) { // xcomponent approx 1.0
            normal.x = +1.0;
        } else if (fabs(intersection.y + 1.0)< eps) {
            normal.y = -1.0;
        } else if (fabs(intersection.y - 1.0) < eps) {
            normal.y = +1.0;
        } else if (fabs(intersection.z + 1.0)< eps) {
            normal.z = -1.0;
        } else if (fabs(intersection.z - 1.0) < eps) {
            normal.z = +1.0;
        }
        //print(normal);
        /* Calculate a Sphere normal */
        normal = glm::normalize(normal_matrix * normal);           //Transformation in die Szene mit transponiert-inverser Matrix
        return normal;
    };

    void clean() override {
        delete this->cache;
    };
};

class Cylinder : public GeometricObject {
private:
public:
    Cylinder() = default;

    int trace_ray(glm::vec4 origin, glm::vec4 direction) override {
        cache = new double[2];
        int number; //Number of intersections
        double coefficient[3];
        double root[2] = {0.0, 0.0};
        double dummy;
        origin = inverse_modelling_matrix * origin;       //Transformation aus der Szene
        direction = inverse_modelling_matrix * direction;    // in die Objektkoordinaten
        //cout << "origin: " << origin.x << "  " << origin.y << "  "  << origin.z << "  " << endl;
        //cout << "direction: "  << direction.x  << "  " << direction.y  << "  "  << direction.z  << "  " << endl;

        /* Calculate terms for intersection calculation */
        double a2 = origin.x * origin.x
                    + origin.y * origin.y;

        double u2 = direction.x * direction.x
                    + direction.y * direction.y;

        double au = origin.x * direction.x
                    + origin.y * direction.y;

        /* Coefficients of intersection polynom             see lecture notes                */
        coefficient[0] = u2;
        coefficient[1] = 2 * au;
        coefficient[2] = a2 - 1;
        number = Solve_Polynomial(2, coefficient, root, TRUE, 1.0e-5);

        if (number > 1) {
            if (origin.z + direction.z * root[1] > 1.0 || origin.z + direction.z * root[1] < -1.0) {
                root[1] = 0.0;
                number--;
            }
        }
        if(number > 0){
            if (origin.z + direction.z * root[0] > 1.0 || origin.z + direction.z * root[0] < -1.0) {
                root[0] = root[1];
                root[1] = 0.0;
                number--;
            }
        }

        double tc = (-1.0 - origin.z) / direction.z;
        double ia = origin.x + tc*direction.x;
        double ib = origin.y + tc*direction.y;
        if(ia*ia + ib*ib <= 1.0){
            root[number] = tc;
            //std::cout << "x1." << tc;
            number++;
        }

        tc = (+1.0 - origin.z) / direction.z;
        ia = origin.x + tc*direction.x;
        ib = origin.y + tc*direction.y;
        if(ia*ia + ib*ib <= 1.0){
            root[number] = tc;
            //std::cout << "x1." << tc;
            number++;
        }

         if(number > 1) {
             if (root[0] > root[1]) {
                    dummy = root[1];
                    root[1] = root[0];
                    root[0] = dummy;
                };
            }

            for (unsigned char i = 0; i < number; i++) {
                cache[i] = root[i];
            }
            if (number != 0) {
                //printf("Anzahl: %d  Schnittpunkte: %f, %f, %f, %f\n", number, t[0], t[1], t[2], t[3]);
            }
        this->cachesize = number;
        return number;
    };

    glm::vec4 get_normal(glm::vec4 origin, glm::vec4 direction, double t) override {
        glm::vec4 normal = glm::vec4(0.0, 0.0, 0.0, 0.0);
        glm::vec4 intersection;
        glm::vec4 temp;// Intersections

        origin = inverse_modelling_matrix * origin; //Transformation aus der Szene
        direction = inverse_modelling_matrix * direction; // in die Objektkoordinaten

        /* Calculate nearest intersection  */
        intersection.x = origin.x + direction.x * t;
        intersection.y = origin.y + direction.y * t;
        intersection.z = origin.z + direction.z * t;

        if (intersection.z >= +1-1e-7){
            normal.x = 0;
            normal.y = 0;
            normal.z = -1;
        } else  if (intersection.z <= -1+1e-7){
            normal.x = 0;
            normal.y = 0;
            normal.z = -1;
        }  else {
            normal.x = intersection.x;
            normal.y = intersection.y;
            normal.z = 0;
        }
        /* Calculate a Sphere normal */

        normal = glm::normalize(
                normal_matrix * normal);           //Transformation in die Szene mit transponiert-inverser Matrix

        return normal;
    };

    void clean() override {
        delete this->cache;
    };
};

enum OP {
    NONE,
    UNION,
    MINUS,
    Intersection
};


class CSGTree : public GeometricObject {
public:
    OP operation = NONE;
    GeometricObject *obj = nullptr;
    CSGTree *left = nullptr;
    CSGTree *right = nullptr;


    CSGTree(OP operation, CSGTree *left, CSGTree *right) : GeometricObject() {
        this->operation = operation;
        this->left = left;
        this->right = right;
    }

    CSGTree(GeometricObject *object) : GeometricObject() {
        this->obj = object;
    }

    int _union(const double * param_a, size_t n_a, const double * param_b, size_t n_b){
        size_t pos_a = 0;
        bool open_a = false;
        size_t pos_b = 0;
        bool open_b = false;
        bool open_r = false;
        bool open_r_last = false;

        size_t n_r = 0;
        if(n_a == 0){
            cache = new double[n_b];
            for(size_t i = 0; i < n_b;i++){
                cache[i] = param_b[i];
            }
            n_r = n_b;
        } else if (n_b == 0){
            cache= new double[n_a];
            for(size_t i = 0; i < n_a;i++){
                cache[i] = param_a[i];
            }
            n_r = n_a;
        } else {
            cache = new double[n_a+n_b];
            double pval = 0;
            while(pos_a < n_a && pos_b < n_b){
                if(param_a[pos_a] == param_b[pos_b]){ // move both
                    pval = param_a[pos_a];
                    open_a = !open_a;
                    open_b = !open_b;
                    pos_a++;
                    pos_b++;

                }else if(param_a[pos_a] < param_b[pos_b]){ // move a
                    open_a = !open_a;
                    pval = param_a[pos_a];
                    pos_a++;
                } else { // move b
                    open_b = !open_b;
                    pval = param_b[pos_b];
                    pos_b++;
                }
                open_r = open_a || open_b;
                if(open_r != open_r_last){
                    cache[n_r] = pval;
                    n_r++;
                    open_r_last = open_r;
                }
            }
            while(pos_a < n_a){
                open_a = !open_a;
                pval = param_a[pos_a];
                pos_a++;
                open_r = open_a || open_b;
                if(open_r != open_r_last){
                    cache[n_r] = pval;
                    n_r++;
                    open_r_last = open_r;
                }
            }
            while(pos_b < n_b){
                open_b = !open_b;
                pval = param_b[pos_b];
                pos_b++;


                open_r = open_a || open_b;
                if(open_r != open_r_last){
                    cache[n_r] = pval;
                    n_r++;
                    open_r_last = open_r;
                }
            }
        }
        return n_r;
    }

    int _minus(const  double * param_a, size_t n_a, const double * param_b, size_t n_b){
        size_t pos_a = 0;
        bool open_a = false;
        size_t pos_b = 0;
        bool open_b = false;
        bool open_r = false;
        bool open_r_last = false;
        size_t n_r = 0;
        if(n_a == 0){
            //std::cout << "op :: left is empty";
            cache = new double[0];
            n_r = 0;
        } else if (n_b == 0){
            //std::cout << "op :: right is empty";
            cache = new double[n_a];
            for(size_t i = 0; i < n_a; i++){
                cache[i] = param_a[i];
                //std::cout << "#";
            }
            n_r = n_a;
        } else {
            //std::cout << "op :: merging";
            cache = new double[n_a+n_b];
            double pval = 0;
            while(pos_a < n_a && pos_b < n_b){
                if(param_a[pos_a] == param_b[pos_b]){ // move both
                    pval = param_a[pos_a];
                    open_a = !open_a;
                    open_b = !open_b;
                    pos_a++;
                    pos_b++;

                }else if(param_a[pos_a] < param_b[pos_b]){ // move a
                    open_a = !open_a;
                    pval = param_a[pos_a];
                    pos_a++;
                } else { // move b
                    open_b = !open_b;
                    pval = param_b[pos_b];
                    pos_b++;
                }
                open_r = open_a && !open_b;
                if(open_r != open_r_last){
                    cache[n_r] = pval;
                    n_r++;
                    open_r_last = open_r;
                }

            }
            while(pos_a < n_a){
                open_a = !open_a;
                pval = param_a[pos_a];
                pos_a++;


                open_r = open_a && !open_b;
                if(open_r != open_r_last){
                    cache[n_r] = pval;
                    n_r++;
                    open_r_last = open_r;
                }
            }
            while(pos_b < n_b){
                open_b = !open_b;
                pval = param_b[pos_b];
                pos_b++;


                open_r = open_a && !open_b;
                if(open_r != open_r_last){
                    cache[n_r] = pval;
                    n_r++;
                    open_r_last = open_r;
                }
            }
        }
        return n_r;
    }

    int _intersect(const double * param_a, size_t n_a, const double * param_b, size_t n_b){
        size_t pos_a = 0;
        bool open_a = false;
        size_t pos_b = 0;
        bool open_b = false;
        bool open_r = false;
        bool open_r_last = false;

        size_t n_r = 0;
        if(n_a == 0 || n_b == 0){
            cache = new double[0];
            n_r = 0;
        } else {
            cache = new double[n_a+n_b];
            double pval = 0;
            while(pos_a < n_a && pos_b < n_b){
                if(param_a[pos_a] == param_b[pos_b]){ // move both
                    pval = param_a[pos_a];
                    open_a = !open_a;
                    open_b = !open_b;
                    pos_a++;
                    pos_b++;

                }else if(param_a[pos_a] < param_b[pos_b]){ // move a
                    open_a = !open_a;
                    pval = param_a[pos_a];
                    pos_a++;
                } else { // move b
                    open_b = !open_b;
                    pval = param_b[pos_b];
                    pos_b++;
                }
                open_r = open_a && open_b;
                if(open_r != open_r_last){
                    cache[n_r] = pval;
                    n_r++;
                    open_r_last = open_r;
                }

            }
            while(pos_a < n_a){
                open_a = !open_a;
                pval = param_a[pos_a];
                pos_a++;


                open_r = open_a && open_b;
                if(open_r != open_r_last){
                    cache[n_r] = pval;
                    n_r++;
                    open_r_last = open_r;
                }
            }
            while(pos_b < n_b){
                open_b = !open_b;
                pval = param_b[pos_b];
                pos_b++;


                open_r = open_a && open_b;
                if(open_r != open_r_last){
                    cache[n_r] = pval;
                    n_r++;
                    open_r_last = open_r;
                }
            }
            /*
            for(size_t i = 0; i < n_r; i++){
                std::cout << cache[i] << ", ";
            }
            std::cout << std::endl;*/
        }
        return n_r;

    }

    int trace_ray(glm::vec4 origin, glm::vec4 direction) override {
        if(this->left == nullptr){
            auto k = this->obj->trace_ray(origin,direction);
            this->cache = this->obj->cache;
            this->cachesize = this->obj->cachesize;
            //std::cout << "leaf number: " << k << std::endl;
            return k;
        }

        origin = inverse_modelling_matrix * origin;       //Transformation aus der Szene
        direction = inverse_modelling_matrix * direction;    // in die Objektkoordinaten

        int number_left = this->left->trace_ray(origin, direction);
        //std::cout << "number_left: " << number_left << std::endl;
        int number_right = this->right->trace_ray(origin, direction);
        //std::cout << "number_right: " << number_right << std::endl;
        int number = 0;
        if(operation == OP::MINUS){
            //std::cout << "operation mius" << std::endl;
            number = this->_minus(this->left->cache,number_left,this->right->cache,number_right);
        } else if(operation == OP::Intersection){
            //std::cout << "operation intersection" << std::endl;
            number = this->_intersect(this->left->cache,number_left,this->right->cache,number_right);
        } else if(operation == OP::UNION){
            //std::cout << "operation union" << std::endl;
            number = this->_union(this->left->cache,number_left,this->right->cache,number_right);
        }
        this->cachesize = number;
        return number;
    };

    glm::vec4 get_normal(glm::vec4 origin, glm::vec4 direction, double t) override {
        glm::vec4 normal = glm::vec4(0.0, 0.0, 0.0, 0.0);
        glm::vec4 intersection;
        glm::vec4 temp;// Intersections

        origin = inverse_modelling_matrix * origin; //Transformation aus der Szene
        direction = inverse_modelling_matrix * direction; // in die Objektkoordinaten


        /* Calculate nearest intersection  */
        if(this->left == nullptr){
            auto v =  this->obj->get_normal(origin,direction,t);
            normal = glm::normalize(normal_matrix * v);
            return normal;
        } else {
            if(this->operation == OP::MINUS){
                int i = 0;
                for(; i < this->left->cachesize; i++){
                    if(t == this->left->cache[i]){
                        //std::cout << "param found";
                        normal = this->left->get_normal(origin,direction,t);
                        break;
                    }
                }
                //std::cout << i <<".";
                if(i == this->left->cachesize) {
                    int j = 0;
                    for (; j < this->right->cachesize; j++) {
                        if (t == this->right->cache[j]) {
                            auto flip = glm::scale(glm::mat4(1.0f), glm::vec3(-1.0f, -1.0f, -1.0f));
                            normal = flip*this->right->get_normal(origin,direction,t);
                            break;
                        }
                    }
                    if(j == this->right->cachesize){
                        std::cout <<"?";
                    } else {
                        //std::cout <<"_";
                    }
                } else {
                    //std::cout <<"i";
                }
            } else if(this->operation == OP::UNION || this->operation == OP::Intersection){
                size_t i = 0;
                for(; i < this->left->cachesize; i++){
                    if(left->cache[i] == t){
                        normal = this->left->get_normal(origin,direction,t);
                        break;
                    }
                }
                if(i == this->left->cachesize){
                    int j = 0;
                    for(; j < this->right->cachesize; j++){
                        if(right->cache[j] == t){
                            normal = this->right->get_normal(origin,direction,t);
                            break;
                        }
                    }
                }

            }
        }

        //normal = glm::vec4(0.0, 0.0, 0.0, 0.0);
        /* Calculate a Sphere normal */
        normal = glm::normalize(normal_matrix * normal);           //Transformation in die Szene mit transponiert-inverser Matrix

        return normal;
    };

    void clean() override {
        delete[] this->cache;
        if(this->left != nullptr){
            this->left->clean();
            this->right->clean();
        } else {
            this->obj->clean();
        }
    }
};
