#define FALSE 0
#define TRUE  1

#define IMAGE_WIDTH  2048
#define IMAGE_HEIGHT 2048

#define BACKGROUND_COLOR_R 100
#define BACKGROUND_COLOR_G 100
#define BACKGROUND_COLOR_B 100
#define BACKGROUND_COLOR_A 255


#define EYE_POINT_X   0.0
#define EYE_POINT_Y   0.0
#define EYE_POINT_Z   6.0

#define CANVAS_ORIG_X  -1.25
#define CANVAS_ORIG_Y  -1.25
#define CANVAS_ORIG_Z   3.0

#define CANVAS_UP_X   0.0
#define CANVAS_UP_Y   2.5
#define CANVAS_UP_Z   0.0

#define CANVAS_RIGHT_X  2.5
#define CANVAS_RIGHT_Y  0.0
#define CANVAS_RIGHT_Z  0.0

#define TORUS_r     0.7

#define AMBIENT_INTENSITY 0.3

#define DIFFUSE_DIR_X     0.0
#define DIFFUSE_DIR_Y     0.0
#define DIFFUSE_DIR_Z     3.0

#define SPECULAR_X    6.0
#define SPECULAR_Y    2.0
#define SPECULAR_Z    3.0

#define PHONG_FACTOR      30.0


#include "Objects.hpp"                  //Class Definitions and Include-Files for HSRT
#include "environment.h"


int main(int argc, char *argv[]) {
    const int width = IMAGE_WIDTH;
    const int height = IMAGE_HEIGHT;
    auto *image = new unsigned char[width * height * 4];
    int red, green, blue;
    int number;

    // create a scene to store all geometric objects
    std::vector<GeometricObject *> scene;
    glm::mat4 matrix;

    /*{   // create first object (torus)
        GeometricObject *p_Object = new Torus(TORUS_r);
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
                 * glm::rotate(glm::mat4(1.0f), 0.5f * pi, glm::vec3(0.0f, 0.7f, -0.5f));

        auto translationmatrix = glm::translate(matrix, glm::vec3(+0.5f, +0.0f, +0.0f));
        auto conmatrix = translationmatrix;

        p_Object->inverse_modelling_matrix = translationmatrix;
        p_Object->normal_matrix = glm::transpose(matrix);
        p_Object->mat_color = Color(0.3, 1.0, 1);
        p_Object->phong_factor = PHONG_FACTOR;
        scene.emplace_back(p_Object);

    }*/
    /*{ // create first cube
        GeometricObject *p_Object = new Cube();//new Torus(TORUS_r);
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
                 * glm::rotate(glm::mat4(1.0f), 0.5f * pi, glm::vec3(0.0f, 0.7f, -0.5f));

        auto translationmatrix = glm::translate(matrix, glm::vec3(+0.5f, +0.0f, +0.0f));
        auto conmatrix = translationmatrix;

        p_Object->inverse_modelling_matrix = translationmatrix;
        p_Object->normal_matrix = glm::transpose(matrix);
        p_Object->mat_color = Color(0.3, 1.0, 1);
        p_Object->phong_factor = PHONG_FACTOR;
        scene.emplace_back(p_Object);
    }*/

    /*{
        GeometricObject *p_Sphere = new Sphere();
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
                 * glm::rotate(glm::mat4(1.0f), 0.0f * pi, glm::vec3(1.0f, 1.0f, 1.0f));

        p_Sphere->inverse_modelling_matrix = glm::translate(matrix, glm::vec3(0.0f, 0.0f, 0.0f));
        p_Sphere->normal_matrix = glm::transpose(matrix);
        p_Sphere->mat_color = Color(1, 1, 0);
        p_Sphere->phong_factor = PHONG_FACTOR;

        scene.emplace_back(p_Sphere);
    }*/
    /*{ // create Cylinder
        GeometricObject *p_Cyl = new Cylinder();
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 1.0f))
                 * glm::rotate(glm::mat4(1.0f), 0.5f * pi, glm::vec3(0.5f, 1.0f, 1.0f));

        p_Cyl->inverse_modelling_matrix = glm::translate(matrix, glm::vec3(-0.5f, 0.0f, 0.0f));
        p_Cyl->normal_matrix = glm::transpose(matrix);
        p_Cyl->mat_color = Color(1.0, 0.5, 0.1);
        p_Cyl->phong_factor = PHONG_FACTOR;
        scene.emplace_back(p_Cyl);
    }*/
    //CSGTree * lleaf = new CSGTree(p_Sphere);
    //CSGTree * rleaf = new CSGTree(p_Cyl);

    //CSGTree * tree = new CSGTree(OP::MINUS, lleaf, rleaf);
    //scene.emplace_back(tree);*/

    /*{
        GeometricObject *p_Cone = new Cone();
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
                 * glm::rotate(glm::mat4(1.0f), 1.0f * pi, glm::vec3(1.0f, 1.0f, 1.0f));

        p_Cone->inverse_modelling_matrix = glm::translate(matrix, glm::vec3(0.5f, 0.0f, 0.0f));
        p_Cone->normal_matrix = glm::transpose(matrix);
        p_Cone->mat_color = Color(0.7, 0.2, 0.1);
        p_Cone->phong_factor = PHONG_FACTOR;
        scene.emplace_back(p_Cone);
    }*/

    { // rounded cube
    /*    GeometricObject *p_CubeA = new Sphere();//new Torus(TORUS_r);
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
                * glm::rotate(glm::mat4(1.0f), 0.0f * pi, glm::vec3(0.1f, 0.7f, 0.5f));

        auto translationmatrix = glm::translate(matrix, glm::vec3(+0.0f, +0.0f, +0.0f));

        p_CubeA->inverse_modelling_matrix = translationmatrix;
        p_CubeA->normal_matrix = glm::transpose(matrix);
        p_CubeA->mat_color = Color(0.3, 1.0, 1);
        p_CubeA->phong_factor = PHONG_FACTOR;

            // create second cube
        GeometricObject *p_CubeB = new Cube();//new Torus(TORUS_r);
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0/1.5, 1.0/1.5, 1.0/1.5))
                 * glm::rotate(glm::mat4(1.0f), 0.0f * pi, glm::vec3(0.0f, 0.7f, 0.5f));

        translationmatrix = glm::translate(matrix, glm::vec3(+0.75, +0.75, 0.75));


        p_CubeB->inverse_modelling_matrix = translationmatrix;
        p_CubeB->normal_matrix = glm::transpose(matrix);
        p_CubeB->mat_color = Color(0.3, 0.3, 1);
        p_CubeB->phong_factor = PHONG_FACTOR;

        CSGTree * lleaf = new CSGTree(p_CubeA);
        CSGTree * rleaf = new CSGTree(p_CubeB);
        CSGTree * tree = new CSGTree(OP::Intersection,lleaf,rleaf);

        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0/1.412, 1.0/1.412, 1.0/1.412))
                 * glm::rotate(glm::mat4(1.0f), 0.4f * pi, glm::vec3(-0.12f, 0.7f, 0.4f));

        translationmatrix = glm::translate(matrix, glm::vec3(+0.7071f, +0.7071f, 5.0));

        tree->mat_color = Color(0.3, 0.6, 1);
        tree->phong_factor = PHONG_FACTOR;
        tree->inverse_modelling_matrix = translationmatrix;
        tree->normal_matrix = glm::transpose(matrix);;
        scene.emplace_back(tree);
        //scene.emplace_back(p_CubeB);*/

    }


    /*{
        GeometricObject *p_ConeA = new Cone();
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
                 * glm::rotate(glm::mat4(1.0f), 1.0f * pi, glm::vec3(0.1f, 0.7f, 0.5f));

        auto translationmatrix = glm::translate(matrix, glm::vec3(+0.0f, +0.0f, +0.0f));

        p_ConeA->inverse_modelling_matrix = translationmatrix;
        p_ConeA->normal_matrix = glm::transpose(matrix);
        p_ConeA->mat_color = Color(0.3, 1.0, 1);
        p_ConeA->phong_factor = PHONG_FACTOR;

        scene.emplace_back(p_ConeA);
    }*/


    { //// rounded cube

        GeometricObject *p_CubeD = new CenteredCube();//new Torus(TORUS_r);
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f))
                 * glm::rotate(glm::mat4(1.0f), 0.0f * pi, glm::vec3(0.1f, 0.7f, 0.5f));

        auto translationmatrix = glm::translate(matrix, glm::vec3(+2.0f, +0.0f, +0.0f));

        p_CubeD->inverse_modelling_matrix = translationmatrix;
        p_CubeD->normal_matrix = glm::transpose(matrix);
        p_CubeD->mat_color = Color(0.3, 0.6, 1);
        p_CubeD->phong_factor = PHONG_FACTOR;

        GeometricObject *p_CubeC = new CenteredCube();//new Torus(TORUS_r);
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 1.0f))
                 * glm::rotate(glm::mat4(1.0f), 0.0f * pi, glm::vec3(0.1f, 0.7f, 0.5f));

         translationmatrix = glm::translate(matrix, glm::vec3(+1.0f, +0.0f, +0.0f));

        p_CubeC->inverse_modelling_matrix = translationmatrix;
        p_CubeC->normal_matrix = glm::transpose(matrix);
        p_CubeC->mat_color = Color(0.3, 0.6, 1);
        p_CubeC->phong_factor = PHONG_FACTOR;

            GeometricObject *p_CubeB = new CenteredCube();//new Torus(TORUS_r);
            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f))
                    * glm::rotate(glm::mat4(1.0f), 0.0f * pi, glm::vec3(0.1f, -0.7f, 0.5f));

            translationmatrix = glm::translate(matrix, glm::vec3(+0.0f, +0.0f, +0.0f));

            p_CubeB->inverse_modelling_matrix = translationmatrix;
            p_CubeB->normal_matrix = glm::transpose(matrix);
            p_CubeB->mat_color = Color(0.3, 0.6, 1);
            p_CubeB->phong_factor = PHONG_FACTOR;

                // create second cube
        GeometricObject *p_CubeA = new CenteredCube();//new Torus(TORUS_r);
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f))
                 * glm::rotate(glm::mat4(1.0f), 0.0f * pi, glm::vec3(0.1f, 0.7f, 0.5f));

        translationmatrix = glm::translate(matrix, glm::vec3(-1.0f, +0.0f, +0.0f));

        p_CubeA->inverse_modelling_matrix = translationmatrix;
        p_CubeA->normal_matrix = glm::transpose(matrix);
        p_CubeA->mat_color = Color(0.3, 0.6, 1);
        p_CubeA->phong_factor = PHONG_FACTOR;

            CSGTree * lleaf = new CSGTree(p_CubeA);
            CSGTree * rleaf = new CSGTree(p_CubeB);
            CSGTree * tree = new CSGTree(OP::Intersection,lleaf,rleaf);

            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0/1.412, 1.0/1.412, 1.0/1.412))
                     * glm::rotate(glm::mat4(1.0f), 0.4f * pi, glm::vec3(-0.12f, 0.7f, 0.4f));

            translationmatrix = glm::translate(matrix, glm::vec3(+0.7071f, +0.7071f, 5.0));

            tree->mat_color = Color(0.3, 0.6, 1);
            tree->phong_factor = PHONG_FACTOR;
            tree->inverse_modelling_matrix = translationmatrix;
            tree->normal_matrix = glm::transpose(matrix);;



        GeometricObject *pSphereA = new Sphere();//new Torus(TORUS_r);
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0f, 1.0f))
                 * glm::rotate(glm::mat4(1.0f), 0.0f * pi, glm::vec3(0.1f, 0.7f, 0.5f));

        translationmatrix = glm::translate(matrix, glm::vec3(0.25f, 0.75f, -0.25f));

        pSphereA->inverse_modelling_matrix = translationmatrix;
        pSphereA->normal_matrix = glm::transpose(matrix);
        pSphereA->mat_color = Color(0.3, 0.6, 1);
        pSphereA->phong_factor = PHONG_FACTOR;

        GeometricObject *pCylinder = new Cylinder();//new Torus(TORUS_r);
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.5, 1.5f, 0.7f))
                 * glm::rotate(glm::mat4(1.0f), 1.0f * pi, glm::vec3(1.0f, 0.0f, 1.0f));

        translationmatrix = glm::translate(matrix, glm::vec3(0.0f, +0.25f, 0.0f));

        pCylinder->inverse_modelling_matrix = translationmatrix;
        pCylinder->normal_matrix = glm::transpose(matrix);
        pCylinder->mat_color = Color(1.0, 0.6, 0.3);
        pCylinder->phong_factor = PHONG_FACTOR;
        //scene.emplace_back(pCylinder);

        CSGTree *lCA = new CSGTree(p_CubeA);
        CSGTree *lCB = new CSGTree(p_CubeB);
        CSGTree *lCC = new CSGTree(p_CubeC);
        CSGTree *lCD = new CSGTree(p_CubeD);
        CSGTree* ua = new CSGTree(OP::UNION, lCA, lCB);
        CSGTree* ub = new CSGTree(OP::UNION, lCC,lCD);
        CSGTree* uc = new CSGTree(OP::UNION, ua, ub);
        CSGTree *lSA = new CSGTree(pSphereA);
        CSGTree * uS = new CSGTree(OP::MINUS, uc,lSA);
        CSGTree *lCCC = new CSGTree(pCylinder);
        CSGTree *ttS = new CSGTree(OP::MINUS, lCCC,uS);

        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0f, 1.0f))
                 * glm::rotate(glm::mat4(1.0f), 0.85f * pi, glm::vec3(0.2f, 0.80f, 1.0f));
        translationmatrix = glm::translate(matrix, glm::vec3(0.25f, 0.75f, +0.0f));

        ttS->inverse_modelling_matrix = translationmatrix;
        ttS->normal_matrix = glm::transpose(matrix);

        ttS->mat_color = Color(0.3,0.6,1);
        ttS->phong_factor = PHONG_FACTOR -15;
        scene.emplace_back(ttS);

            //scene.emplace_back(p_CubeB);/

    }

    /* Transform pixel increment to canvas increment; scanline order is decreasing y-coordinate */
    glm::vec3 CanvasOrigin = glm::vec3(CANVAS_ORIG_X, CANVAS_ORIG_Y, CANVAS_ORIG_Z);
    glm::vec3 CanvasUp = glm::vec3(CANVAS_UP_X, CANVAS_UP_Y, CANVAS_UP_Z);
    glm::vec3 CanvasRight = glm::vec3(CANVAS_RIGHT_X, CANVAS_RIGHT_Y, CANVAS_RIGHT_Z);
    glm::vec3 StepUp = glm::vec3(CanvasUp.x / IMAGE_HEIGHT, CanvasUp.y / IMAGE_HEIGHT, CanvasUp.z / IMAGE_HEIGHT);
    glm::vec3 StepRight = glm::vec3(CanvasRight.x / IMAGE_WIDTH, CanvasRight.y / IMAGE_WIDTH,
                                    CanvasRight.z / IMAGE_WIDTH);

    glm::vec4 EyePoint = glm::vec4(EYE_POINT_X, EYE_POINT_Y, EYE_POINT_Z, 1.0);
    glm::vec4 direction = glm::vec4(0.0, 0.0, 0.0, 0.0);//  Direction of ray:   X = startpoint + parameterArray*direction
    glm::vec4 Normal = glm::vec4(0.0, 0.0, 0.0, 0.0);




    /* Set Background Color */

    for (unsigned short row = 0; row < height; row++) {
        for (unsigned short column = 0; column < width; column++) {
            image[4 * width * row + 4 * column + 0] = BACKGROUND_COLOR_R;
            image[4 * width * row + 4 * column + 1] = BACKGROUND_COLOR_G;
            image[4 * width * row + 4 * column + 2] = BACKGROUND_COLOR_B;
            image[4 * width * row + 4 * column + 3] = BACKGROUND_COLOR_A;
        }
    }

    cout << "/****   Program started!  *****/" << endl;
    for (unsigned short row = 0; row < height; ++row) {
        for (unsigned short column = 0; column < width; ++column) {
            direction = glm::vec4(
                    CanvasOrigin.x + 0.5 * StepRight.x + column * StepRight.x + (IMAGE_HEIGHT - 0.5 - row) * StepUp.x -
                    EyePoint.x,
                    CanvasOrigin.y + 0.5 * StepRight.y + column * StepRight.y + (IMAGE_HEIGHT - 0.5 - row) * StepUp.y -
                    EyePoint.y,
                    CanvasOrigin.z + 0.5 * StepRight.z + column * StepRight.z + (IMAGE_HEIGHT - 0.5 - row) * StepUp.z -
                    EyePoint.z,
                    0.0);

            GeometricObject * current = nullptr;
            double current_t;

            for(auto * obj : scene){
                number = obj->trace_ray(EyePoint, direction);
                if(number != 0){
                    if(current != nullptr){
                        //std::cout << parameterArray[0] << ", " << current_t << std::endl;
                        if(obj->cache[0] < current_t){
                            current = obj;
                            current_t = obj->cache[0];
                        }
                    } else {
                        current = obj;
                        current_t = obj->cache[0];
                    }
                }
            }
            //std::cout << std::endl;
            //cout << number << endl;
            //std::cout << "pos: " << row << "\parameterArray" << column << std::endl;
            //cout << parameterArray[0] << "\parameterArray" << parameterArray[1] << "\parameterArray" << parameterArray[2] << "\parameterArray" << parameterArray[3] << std::endl;

            if (current != nullptr) {
                double dotprod;
                double diffuse_intensity;
                double specular_intensity;
                glm::vec4 Intersection;
                glm::vec4 H;
                Normal = current->get_normal(EyePoint, direction, current_t);            //  Normal of nearest object
                //print(Normal);

                /* Diffuse Reflexion */
                dotprod = glm::dot(Normal,
                                   glm::normalize(glm::vec4(DIFFUSE_DIR_X, DIFFUSE_DIR_Y, DIFFUSE_DIR_Z, 0.0f)));
                diffuse_intensity = dotprod >= AMBIENT_INTENSITY ? dotprod : AMBIENT_INTENSITY;
                /* Calculation of Specular Reflexion by Phong resp. Blinn */

                /* Vector H = L+V/|L+V|; V = direction from intersection to eyepoint = - Dir, L = direction from intersection to light source */
                Intersection = EyePoint + (float) current_t * direction;
                H = glm::normalize(glm::vec4(SPECULAR_X, SPECULAR_Y, SPECULAR_Z, 1.0f) - Intersection - direction);

                dotprod = glm::dot(Normal, H);

                if (dotprod > 0) {
                    specular_intensity = pow(dotprod, current->phong_factor);
                } else {
                    specular_intensity = 0.0;
                }

                /* Write Image File */
                image[4 * width * row + 4 * column + 0] =
                        current->mat_color.r * 255 * diffuse_intensity + 255 * specular_intensity <= 255 ?
                        current->mat_color.r * 255 * diffuse_intensity + 255 * specular_intensity : 255;
                image[4 * width * row + 4 * column + 1] =
                        current->mat_color.g * 255 * diffuse_intensity + 255 * specular_intensity <= 255 ?
                        current->mat_color.g * 255 * diffuse_intensity + 255 * specular_intensity : 255;
                image[4 * width * row + 4 * column + 2] =
                        current->mat_color.b * 255 * diffuse_intensity + 255 * specular_intensity <= 255 ?
                        current->mat_color.b * 255 * diffuse_intensity + 255 * specular_intensity : 255;
                image[4 * width * row + 4 * column + 3] = BACKGROUND_COLOR_A;
            }
        }
    }
    // write image to file
    lodepng_encode32_file("Image.png", image, width, height);
    cout << "Image Drawn! File Written!" << endl;
    return 0;
};