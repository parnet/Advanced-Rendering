#include <iostream>                     // C++ Standard I/O
#include <cmath>                        // C++ Standard Mathematical Functions

#define  GLM_FORCE_RADIANS

#include <glm/glm.hpp>                  // Vector/Matrix Functions by GLM
#include <glm/gtc/matrix_transform.hpp> // Matrix Functions by GLM
#include "../libs/lodepng/lodepng.h"                // PNG File Handling by loadpng
#include "Polysolv.h"                   // Polynom Root Finder found somewhere in the Internet


using namespace std;
//using namespace glm;
//using namespace png;


/* Constant Declaration */

const float pi = 3.141592;

/* Type Declarations   */


using namespace std;

/* Class Definitions   */

class Color {
public:

    double r;     // 0 <= r <= 1
    double g;     // 0 <= g <= 1
    double b;     // 0 <= b <= 1


    Color()                                                 // Default Construktor
    {
        r = 0.0;
        g = 0.0;
        b = 0.0;
    };

    Color(double red, double green, double blue)            // Construktor
    {
        r = (red < 1.0) ? red : 1.0;
        g = (green < 1.0) ? green : 1.0;
        b = (blue < 1.0) ? blue : 1.0;
    };


};


class GeometricObject {
private:
protected:
public:


    glm::mat4 inverse_modelling_matrix = glm::mat4(1.0f);
    glm::mat4 normal_matrix = glm::mat4(1.0f);

    Color mat_color = Color(1.0, 1.0, 1.0);
    double phong_factor = 1.0;

    virtual int trace_ray(glm::vec4 origin, glm::vec4 direction, double t[]) = 0;

    virtual glm::vec4 get_normal(glm::vec4 origin, glm::vec4 direction, double t) = 0;

};

class torus : public GeometricObject {

private:

    double rad_R = 1.0;
    double rad_r = 0.1;

public:

    torus() = default;

    explicit torus(double r) {
        rad_r = r;
    };

    int trace_ray(glm::vec4 origin, glm::vec4 direction, double t[]) {


        int number;                      //Number of intersections
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
                t[i] = root[i];

            //printf ("Anzahl: %d  Schnittpunkte: %f, %f, %f, %f\n", number, t[0], t[1], t[2], t[3]);

        };

        return number;

    };    // end of trace_ray




    glm::vec4 get_normal(glm::vec4 origin, glm::vec4 direction, double t) {
        glm::vec4 normal = glm::vec4(0.0, 0.0, 0.0, 0.0);
        glm::vec4 intersection;
        glm::vec4 temp;                     // Intersections

        origin = inverse_modelling_matrix * origin;       //Transformation aus der Szene
        direction = inverse_modelling_matrix * direction;    // in die Objektkoordinaten

        /* Calculate nearest intersection  */

        intersection.x = origin.x + direction.x * t;
        intersection.y = origin.y + direction.y * t;
        intersection.z = origin.z + direction.z * t;

        // cout << "Anzahl: "  << number << endl;
        // cout << "t: " << t[0] << "  " << t[1] << "  " << t[2] << endl;
        // cout << "Schnitt: " << intersection.x << " " << intersection.y << " " << intersection.z << endl;


        /* To calculate a torus normal:
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

    };     // end of get_normal


};

class Sphere : public GeometricObject {

private:


public:
    Sphere() = default;


    int trace_ray(glm::vec4 origin, glm::vec4 direction, double t[]) {


        int number;                      //Number of intersections

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
                    + origin.z * origin.z;
        double u2 = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;
        double au = origin.x * direction.x + origin.y * direction.y + origin.z * direction.z;





        /* Coefficients of intersection polynom             see lecture notes                */


        coefficient[0] = u2;
        coefficient[1] = 2 * au;
        coefficient[2] = a2 - 1;

        number = Solve_Polynomial(2, coefficient, root, TRUE, 1.0e-5);


        if (number > 0) {
            if (root[0] > root[1]) {
                dummy = root[1];
                root[1] = root[0];
                root[0] = dummy;
            };
            for (unsigned char i = 0; i < number; i++)
                t[i] = root[i];

            //printf ("Anzahl: %d  Schnittpunkte: %f, %f, %f, %f\n", number, t[0], t[1], t[2], t[3]);

        };

        return number;

    };    // end of trace_ray




    glm::vec4 get_normal(glm::vec4 origin, glm::vec4 direction, double t) {
        glm::vec4 normal = glm::vec4(0.0, 0.0, 0.0, 0.0);
        glm::vec4 intersection;
        glm::vec4 temp;                     // Intersections

        origin = inverse_modelling_matrix * origin;       //Transformation aus der Szene
        direction = inverse_modelling_matrix * direction;    // in die Objektkoordinaten

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

    };     // end of get_normal


};


