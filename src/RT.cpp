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


    /*{ //// scene
        GeometricObject *p_CubeD = new CenteredCube();//new Torus(TORUS_r);
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(4.0f, 1.0f, 4.0f))
                 * glm::rotate(glm::mat4(1.0f), 0.0f * pi, glm::vec3(0.1f, 0.7f, 0.5f));

        auto translationmatrix = glm::translate(matrix, glm::vec3(+1.5f, +0.0f, +0.0f));
        p_CubeD->inverse_modelling_matrix = translationmatrix;
        p_CubeD->normal_matrix = glm::transpose(matrix);
        p_CubeD->mat_color = Color(0.3, 0.6, 1);
        p_CubeD->phong_factor = PHONG_FACTOR;

        GeometricObject *p_CubeC = new CenteredCube();//new Torus(TORUS_r);
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(4.0f, 4.0f, 4.0f))
                 * glm::rotate(glm::mat4(1.0f), 0.0f * pi, glm::vec3(0.1f, 0.7f, 0.5f));

        translationmatrix = glm::translate(matrix, glm::vec3(+0.5f, +0.0f, +0.0f));
        p_CubeC->inverse_modelling_matrix = translationmatrix;
        p_CubeC->normal_matrix = glm::transpose(matrix);
        p_CubeC->mat_color = Color(0.3, 0.6, 1);
        p_CubeC->phong_factor = PHONG_FACTOR;

        GeometricObject *p_CubeB = new CenteredCube();//new Torus(TORUS_r);
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(4.0f, 4.0f, 4.0f))
                * glm::rotate(glm::mat4(1.0f), 0.0f * pi, glm::vec3(0.1f, -0.7f, 0.5f));

        translationmatrix = glm::translate(matrix, glm::vec3(-0.5f, +0.0f, +0.0f));
        p_CubeB->inverse_modelling_matrix = translationmatrix;
        p_CubeB->normal_matrix = glm::transpose(matrix);
        p_CubeB->mat_color = Color(0.3, 0.6, 1);
        p_CubeB->phong_factor = PHONG_FACTOR;

        GeometricObject *p_CubeA = new CenteredCube();//new Torus(TORUS_r);
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(4.0f, 1.0f, 4.0f))
                 * glm::rotate(glm::mat4(1.0f), 0.0f * pi, glm::vec3(0.1f, 0.7f, 0.5f));

        translationmatrix = glm::translate(matrix, glm::vec3(-1.5f, +0.0f, +0.0f));
        p_CubeA->inverse_modelling_matrix = translationmatrix;
        p_CubeA->normal_matrix = glm::transpose(matrix);
        p_CubeA->mat_color = Color(0.3, 0.6, 1);
        p_CubeA->phong_factor = PHONG_FACTOR;



        GeometricObject *pSphereA = new Sphere();//new Torus(TORUS_r);
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0f, 1.0f))
                 * glm::rotate(glm::mat4(1.0f), 0.0f * pi, glm::vec3(0.1f, 0.7f, 0.5f));

        translationmatrix = glm::translate(matrix, glm::vec3(0.0f, 0.75f, -0.25f));

        pSphereA->inverse_modelling_matrix = translationmatrix;
        pSphereA->normal_matrix = glm::transpose(matrix);
        pSphereA->mat_color = Color(0.3, 0.6, 1);
        pSphereA->phong_factor = PHONG_FACTOR;


        GeometricObject *pCylinder = new Cylinder();//new Torus(TORUS_r);
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.5, 2.5, 0.4))
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

    }*/

    /*{
        GeometricObject *p_Planet = new Sphere();
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f))
                 * glm::rotate(glm::mat4(1.0f), 0.0f * pi, glm::vec3(0.1f, 0.7f, 0.5f));

        auto translationmatrix = glm::translate(matrix, glm::vec3(-10.0f, +0.0f, +30.0f));

        p_Planet->inverse_modelling_matrix = translationmatrix;
        p_Planet->normal_matrix = glm::transpose(matrix);
        p_Planet->mat_color = Color(0.3, 1.0, 1);
        p_Planet->phong_factor = PHONG_FACTOR;

        scene.emplace_back(p_Planet);

        GeometricObject *p_Ring = new Torus();
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 4.f))
                 * glm::rotate(glm::mat4(1.0f), 4.f/3.f * pi, glm::vec3(1.0f, 0.0f, 0.0f));

        translationmatrix = glm::translate(matrix, glm::vec3(-10.0f, +0.0f, +30.0f));

        p_Ring->inverse_modelling_matrix = translationmatrix;
        p_Ring->normal_matrix = glm::transpose(matrix);
        p_Ring->mat_color = Color(0.3, 1.0, 1);
        p_Ring->phong_factor = PHONG_FACTOR;

        scene.emplace_back(p_Ring);

        GeometricObject *p_secRing = new Torus(0.075);
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.23f, 0.23f, 4.f))
                 * glm::rotate(glm::mat4(1.0f), 4.f/3.f * pi, glm::vec3(1.0f, 0.0f, 0.0f));

        translationmatrix = glm::translate(matrix, glm::vec3(-10.0f, +0.0f, +30.0f));

        p_secRing->inverse_modelling_matrix = translationmatrix;
        p_secRing->normal_matrix = glm::transpose(matrix);
        p_secRing->mat_color = Color(0.3, 1.0, 1);
        p_secRing->phong_factor = PHONG_FACTOR;

        scene.emplace_back(p_secRing);

    }*/

    { // Bridge
        CSGTree *cBridgeModule = nullptr;
        CSGTree *cPropulsorLeftModule = nullptr;
        CSGTree *cPropulsorRightModule = nullptr;
        CSGTree *cHangarModule = nullptr;
        GeometricObject *p_Bridge = new Cylinder();
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 14.0f))
                 * glm::rotate(glm::mat4(1.0f), 0.5f * pi, glm::vec3(1.0f, 0.0f, 0.0f));

        auto translationmatrix = glm::translate(matrix, glm::vec3(0.0f, 0.0f, 0.0f));

        p_Bridge->inverse_modelling_matrix = translationmatrix;
        p_Bridge->normal_matrix = glm::transpose(matrix);
        p_Bridge->mat_color = Color(0.3, 1.0, 1);
        p_Bridge->phong_factor = PHONG_FACTOR;
        //scene.emplace_back(p_Bridge);

        GeometricObject *p_cutout = new Torus(0.7);
        auto a = dynamic_cast<Torus *>(p_cutout);
        a->rad_R = 0.5;
        a->rad_r = 1.0;
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.78f, 0.78f, 0.78f))
                 * glm::rotate(glm::mat4(1.0f), 0.5f * pi, glm::vec3(1.0f, 0.0f, 0.0f));

        translationmatrix = glm::translate(matrix, glm::vec3(0.0f, 1.215f, 0.0f));

        p_cutout->inverse_modelling_matrix = translationmatrix;
        p_cutout->normal_matrix = glm::transpose(matrix);
        p_cutout->mat_color = Color(1.0, 0.0, 0);
        p_cutout->phong_factor = PHONG_FACTOR;

        //scene.emplace_back(p_cutout);

        auto *cBridge = new CSGTree(p_Bridge);
        auto *cCutout = new CSGTree(p_cutout);
        auto *cA = new CSGTree(OP::MINUS, cBridge, cCutout);

        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0f, 1.0f))
                 * glm::rotate(glm::mat4(1.0f), -0.3f * pi, glm::vec3(1.0f, 1.0f, 0.0f));
        translationmatrix = glm::translate(matrix, glm::vec3(0.0f, 0.0f, +0.0f));

        cA->mat_color = Color(0.3, 0.6, 1);
        cA->phong_factor = PHONG_FACTOR - 15;

        GeometricObject *p_BridgeSupplT = new Cylinder();
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 14.0f))
                 * glm::rotate(glm::mat4(1.0f), 0.5f * pi, glm::vec3(1.0f, 0.0f, 0.0f));

        translationmatrix = glm::translate(matrix, glm::vec3(0.0f, -2 * 0.071428f, 0.0f));

        p_BridgeSupplT->inverse_modelling_matrix = translationmatrix;
        p_BridgeSupplT->normal_matrix = glm::transpose(matrix);
        p_BridgeSupplT->mat_color = Color(0, 1.0, 0);
        p_BridgeSupplT->phong_factor = PHONG_FACTOR;

        GeometricObject *p_secRing = new Sphere();
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2, 0.2f))
                 * glm::rotate(glm::mat4(1.0f), 0 * pi, glm::vec3(1.0, 0.0f, 0.0f));

        translationmatrix = glm::translate(matrix, glm::vec3(0.0, 4.857f, 0.0f));

        p_secRing->inverse_modelling_matrix = translationmatrix;
        p_secRing->normal_matrix = glm::transpose(matrix);
        p_secRing->mat_color = Color(0.3, 1.0, 1);
        p_secRing->phong_factor = PHONG_FACTOR;

        auto *cUppBridge = new CSGTree(p_BridgeSupplT);
        auto *cIntersect = new CSGTree(p_secRing);
        auto *cUpperPart = new CSGTree(OP::Intersection, cUppBridge, cIntersect);

        /*matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0f, 1.0f))
                 * glm::rotate(glm::mat4(1.0f), -0.3f * pi, glm::vec3(1.0f, 1.0f, 0.0f));
        translationmatrix = glm::translate(matrix, glm::vec3(0.0f, 0.0f, +0.0f));

        cBridgeModule->mat_color = Color(0.3, 0.6, 1);
        cBridgeModule->phong_factor = PHONG_FACTOR - 15;*/
        cBridgeModule = new CSGTree(OP::UNION, cUpperPart, cA);

        // Propulsor Left
        {
            GeometricObject *p_propulsor = new Cylinder();
            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(8.756756757, 8.756756757, 0.875675))
                     * glm::rotate(glm::mat4(1.0f), 0.5f * pi, glm::vec3(0.0f, 1.0f, 0.0f));

            auto translationmatrix = glm::translate(matrix, glm::vec3(0.0f, 0.f, 0.0f));

            p_propulsor->inverse_modelling_matrix = translationmatrix;
            p_propulsor->normal_matrix = glm::transpose(matrix);
            p_propulsor->mat_color = Color(0, 1.0, 0);
            p_propulsor->phong_factor = PHONG_FACTOR;

            GeometricObject *p_propulsorFront = new Sphere();
            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(8.756756757, 8.756756757, 8.756756757))
                     * glm::rotate(glm::mat4(1.0f), 0 * pi, glm::vec3(1.0, 0.0f, 0.0f));

            translationmatrix = glm::translate(matrix, glm::vec3(1.141976190, 0.0f, 0.0f));

            p_propulsorFront->inverse_modelling_matrix = translationmatrix;
            p_propulsorFront->normal_matrix = glm::transpose(matrix);
            p_propulsorFront->mat_color = Color(0.0, 0.5, 1);
            p_propulsorFront->phong_factor = PHONG_FACTOR;

            GeometricObject *p_propulsorCutout = new CenteredCube();
            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.756756757, 8.756756757, 8.756756757))
                     * glm::rotate(glm::mat4(1.0f), -0.25f * pi, glm::vec3(0.0, 0.0f, 1.0f));

            translationmatrix = glm::translate(matrix, glm::vec3(-1.141976190, 0.0f, 0.0f));

            p_propulsorCutout->inverse_modelling_matrix = translationmatrix;
            p_propulsorCutout->normal_matrix = glm::transpose(matrix);
            p_propulsorCutout->mat_color = Color(0.5, 0.5, 1);
            p_propulsorCutout->phong_factor = PHONG_FACTOR;

            GeometricObject *p_propulsorEngine = new Sphere();
            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(10, 10, 10))
                     * glm::rotate(glm::mat4(1.0f), 0 * pi, glm::vec3(1.0, 0.0f, 0.0f));

            translationmatrix = glm::translate(matrix, glm::vec3(-0.95, 0.0f, 0.0f));

            p_propulsorEngine->inverse_modelling_matrix = translationmatrix;
            p_propulsorEngine->normal_matrix = glm::transpose(matrix);
            p_propulsorEngine->mat_color = Color(0.8, 0.7, 0.2);
            p_propulsorEngine->phong_factor = PHONG_FACTOR;

            auto *cPropulsor = new CSGTree(p_propulsor);
            auto *cPropulsorFront = new CSGTree(p_propulsorFront);
            auto *cPropulsorEngine = new CSGTree(p_propulsorEngine);
            auto *cPropulsorCutout = new CSGTree(p_propulsorCutout);

            auto *cPropulsorBody = new CSGTree(OP::MINUS, cPropulsor, cPropulsorCutout);
            auto *cPropulsorDecor = new CSGTree(OP::UNION, cPropulsorFront, cPropulsorEngine);

            cPropulsorLeftModule = new CSGTree(OP::UNION, cPropulsorBody, cPropulsorDecor);

            cPropulsorLeftModule->mat_color = Color(0.9, 0.9, 0.9);
            cPropulsorLeftModule->phong_factor = PHONG_FACTOR;

            //matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1))
            //                     * glm::rotate(glm::mat4(1.0f), 2.0f / 3.0f * pi, glm::vec3(1.0, 0.7f, 0.0f));

            //translationmatrix = glm::translate(matrix, glm::vec3(0.0, 0.0f, 0.0f));
            //cPropulsorLeftModule->inverse_modelling_matrix = translationmatrix;
            //cPropulsorLeftModule->normal_matrix = glm::transpose(matrix);
        }

        // Propulsor Right
        {
            GeometricObject *p_propulsor = new Cylinder();
            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(8.756756757, 8.756756757, 0.875675))
                     * glm::rotate(glm::mat4(1.0f), 0.5f * pi, glm::vec3(0.0f, 1.0f, 0.0f));

            auto translationmatrix = glm::translate(matrix, glm::vec3(0.0f, 0.f, 0.0f));

            p_propulsor->inverse_modelling_matrix = translationmatrix;
            p_propulsor->normal_matrix = glm::transpose(matrix);
            p_propulsor->mat_color = Color(0, 1.0, 0);
            p_propulsor->phong_factor = PHONG_FACTOR;

            GeometricObject *p_propulsorFront = new Sphere();
            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(8.756756757, 8.756756757, 8.756756757))
                     * glm::rotate(glm::mat4(1.0f), 0 * pi, glm::vec3(1.0, 0.0f, 0.0f));

            translationmatrix = glm::translate(matrix, glm::vec3(1.141976190, 0.0f, 0.0f));

            p_propulsorFront->inverse_modelling_matrix = translationmatrix;
            p_propulsorFront->normal_matrix = glm::transpose(matrix);
            p_propulsorFront->mat_color = Color(0.0, 0.5, 1);
            p_propulsorFront->phong_factor = PHONG_FACTOR;

            GeometricObject *p_propulsorCutout = new CenteredCube();
            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.756756757, 8.756756757, 8.756756757))
                     * glm::rotate(glm::mat4(1.0f), -0.25f * pi, glm::vec3(0.0, 0.0f, 1.0f));

            translationmatrix = glm::translate(matrix, glm::vec3(-1.141976190, 0.0f, 0.0f));

            p_propulsorCutout->inverse_modelling_matrix = translationmatrix;
            p_propulsorCutout->normal_matrix = glm::transpose(matrix);
            p_propulsorCutout->mat_color = Color(0.5, 0.5, 1);
            p_propulsorCutout->phong_factor = PHONG_FACTOR;

            GeometricObject *p_propulsorEngine = new Sphere();
            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(10, 10, 10))
                     * glm::rotate(glm::mat4(1.0f), 0 * pi, glm::vec3(1.0, 0.0f, 0.0f));

            translationmatrix = glm::translate(matrix, glm::vec3(-0.95, 0.0f, 0.0f));

            p_propulsorEngine->inverse_modelling_matrix = translationmatrix;
            p_propulsorEngine->normal_matrix = glm::transpose(matrix);
            p_propulsorEngine->mat_color = Color(0.8, 0.7, 0.2);
            p_propulsorEngine->phong_factor = PHONG_FACTOR;

            CSGTree *cPropulsor = new CSGTree(p_propulsor);
            CSGTree *cPropulsorFront = new CSGTree(p_propulsorFront);
            CSGTree *cPropulsorEngine = new CSGTree(p_propulsorEngine);
            CSGTree *cPropulsorCutout = new CSGTree(p_propulsorCutout);

            CSGTree *cPropulsorBody = new CSGTree(OP::MINUS, cPropulsor, cPropulsorCutout);
            CSGTree *cPropulsorDecor = new CSGTree(OP::UNION, cPropulsorFront, cPropulsorEngine);

            cPropulsorRightModule = new CSGTree(OP::UNION, cPropulsorBody, cPropulsorDecor);

            cPropulsorRightModule->mat_color = Color(0.9, 0.9, 0.9);
            cPropulsorRightModule->phong_factor = PHONG_FACTOR;

            //matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1))
            //* glm::rotate(glm::mat4(1.0f), 2.0f / 3.0f * pi, glm::vec3(1.0, 0.7f, 0.0f));

            //translationmatrix = glm::translate(matrix, glm::vec3(0.0, 0.0f, 0.0f));
            //cPropulsorRightModule->inverse_modelling_matrix = translationmatrix;
            //cPropulsorRightModule->normal_matrix = glm::transpose(matrix);
        }

        {
            GeometricObject *p_HangarMain = new Cone();
            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.842105263, 2.842105263, 0.399506781 / 2))
                     * glm::rotate(glm::mat4(1.0f), 0.5f * pi, glm::vec3(0.0f, 1.0f, 0.0f));

            auto translationmatrix = glm::translate(matrix, glm::vec3(+5.0f, 0.f, 0.0f));

            p_HangarMain->inverse_modelling_matrix = translationmatrix;
            p_HangarMain->normal_matrix = glm::transpose(matrix);
            p_HangarMain->mat_color = Color(1, 0.5, 0);
            p_HangarMain->phong_factor = PHONG_FACTOR;

            GeometricObject *p_HangerHull = new Cone();
            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(3.600000000, 3.600000000, 1.588235294 / 2))
                     * glm::rotate(glm::mat4(1.0f), -0.5f * pi, glm::vec3(0.0, 1.0f, 0.0f));

            translationmatrix = glm::translate(matrix, glm::vec3(-1.25, 0.0f, 0.0f));

            p_HangerHull->inverse_modelling_matrix = translationmatrix;
            p_HangerHull->normal_matrix = glm::transpose(matrix);
            p_HangerHull->mat_color = Color(0.0, 0.5, 1);
            p_HangerHull->phong_factor = PHONG_FACTOR;

            GeometricObject *p_HangerHullintersection = new CenteredCube();
            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.8, 2.8, 0.8039702233))
                     * glm::rotate(glm::mat4(1.0f), 0.5f * pi, glm::vec3(0.0, 2.0f, 0.0f));

            translationmatrix = glm::translate(matrix, glm::vec3(+1, 0.0f, 0.0f));

            p_HangerHullintersection->inverse_modelling_matrix = translationmatrix;
            p_HangerHullintersection->normal_matrix = glm::transpose(matrix);
            p_HangerHullintersection->mat_color = Color(0.5, 0.5, 1);
            p_HangerHullintersection->phong_factor = PHONG_FACTOR;

            //scene.emplace_back(p_HangerHullintersection);
            auto *cHangerMain = new CSGTree(p_HangarMain);
            auto *cHangerHull = new CSGTree(p_HangerHull);
            auto *cHangarHullIntersection = new CSGTree(p_HangerHullintersection);

            auto *cHangarBody = new CSGTree(OP::UNION, cHangerMain, cHangerHull);
            auto *cHangarDecor = new CSGTree(OP::Intersection, cHangarBody, cHangarHullIntersection);


            GeometricObject *p_HangarCutout = new Cylinder();
            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.963636364, 3.681818182, 1))
                     * glm::rotate(glm::mat4(1.0f), 0 * pi, glm::vec3(1.0, 0.0f, 0.0f));

            translationmatrix = glm::translate(matrix, glm::vec3(2.3, 0.3f, .0f));

            p_HangarCutout->inverse_modelling_matrix = translationmatrix;
            p_HangarCutout->normal_matrix = glm::transpose(matrix);
            p_HangarCutout->mat_color = Color(0.2, 0.7, 1.0);
            p_HangarCutout->phong_factor = PHONG_FACTOR;

            auto *cHangerCutout = new CSGTree(p_HangarCutout);
            cHangarModule = new CSGTree(OP::MINUS, cHangarDecor, cHangerCutout);

            // todo satellit / antenne
        }

        {


            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.5, 1.5f, 1.5f))
                     * glm::rotate(glm::mat4(1.0f), 0 * pi, glm::vec3(1.0f, 1.0f, 0.0f));
            translationmatrix = glm::translate(matrix, glm::vec3(0.85f, 1.74f / 3.0f, +0.0f));
            cHangarModule->mat_color = Color(0.3, 0.6, 1);
            cHangarModule->phong_factor = PHONG_FACTOR;
            cHangarModule->inverse_modelling_matrix = translationmatrix;
            cHangarModule->normal_matrix = glm::transpose(matrix);


            double dy = -0.2;
            double dx = 2.4;
            double dz = 1.0;

            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0f, 1.0f))
                     * glm::rotate(glm::mat4(1.0f), 1 * pi, glm::vec3(0.0f, 1.0f, 0.0f));
            translationmatrix = glm::translate(matrix, glm::vec3(dx, dy, dz));
            cPropulsorLeftModule->mat_color = Color(0.3, 0.3, 0.6);
            cPropulsorLeftModule->phong_factor = PHONG_FACTOR;
            cPropulsorLeftModule->inverse_modelling_matrix = translationmatrix;
            cPropulsorLeftModule->normal_matrix = glm::transpose(matrix);

            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0f, 1.0f))
                     * glm::rotate(glm::mat4(1.0f), 1 * pi, glm::vec3(0.0f, 1.0f, 0.0f));
            translationmatrix = glm::translate(matrix, glm::vec3(dx, dy, -dz));
            cPropulsorRightModule->mat_color = Color(0.6, 0.3, 6);
            cPropulsorRightModule->phong_factor = PHONG_FACTOR;
            cPropulsorRightModule->inverse_modelling_matrix = translationmatrix;
            cPropulsorRightModule->normal_matrix = glm::transpose(matrix);

            auto *cAx = new CSGTree(OP::UNION, cBridgeModule, cHangarModule);
            auto *cBx = new CSGTree(OP::UNION, cPropulsorLeftModule, cPropulsorRightModule);

            auto *cTx = new CSGTree(OP::UNION, cAx, cBx);


            double dhx = 0;
            double dhy = 0;
            double dhz = 0;
            double sx = 10;
            double sy = 0.5;
            double sz = 1.0;

            GeometricObject *pConnPropulsorHangarLeft = new Cube();
            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(sx, sy, sz))
                     * glm::rotate(glm::mat4(1.0f), 0.25f * pi, glm::vec3(1.0f, 0.0f, 0.0f));

            translationmatrix = glm::translate(matrix, glm::vec3(dhx, dhy, dhz));
            pConnPropulsorHangarLeft->inverse_modelling_matrix = translationmatrix;
            pConnPropulsorHangarLeft->normal_matrix = glm::transpose(matrix);
            pConnPropulsorHangarLeft->mat_color = Color(1, 0.5, 0);
            pConnPropulsorHangarLeft->phong_factor = PHONG_FACTOR;

            GeometricObject *pConnPropulsorHangarRight = new Cube();
            matrix = glm::scale(glm::mat4(1.0f), glm::vec3(sx, sy, sz))
                     * glm::rotate(glm::mat4(1.0f), -0.25f * pi, glm::vec3(1.0f, 0.0f, 0.0f));

            translationmatrix = glm::translate(matrix, glm::vec3(-dhx, dhy, dhz));
            pConnPropulsorHangarRight->inverse_modelling_matrix = translationmatrix;
            pConnPropulsorHangarRight->normal_matrix = glm::transpose(matrix);
            pConnPropulsorHangarRight->mat_color = Color(1, 0.5, 0);
            pConnPropulsorHangarRight->phong_factor = PHONG_FACTOR;

            //scene.emplace_back(pConnPropulsorHangarLeft);

            auto *cConnPHL = new CSGTree(pConnPropulsorHangarLeft);
            auto *cConnPHR = new CSGTree(pConnPropulsorHangarRight);

            auto * cATx = new CSGTree(OP::UNION, cConnPHL, cConnPHR);
            auto * cCx = new CSGTree(OP::UNION, cATx, cTx);

            short rotation = 0; // 1 top, 2 front , 3, 4


            if (rotation == 1) {
                matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.5, 1.5f, 1.5f))
                         * glm::rotate(glm::mat4(1.0f), -0.5f * pi, glm::vec3(1.0f, 0.0f, 0.0f));
                translationmatrix = glm::translate(matrix, glm::vec3(0.0f, 1.74f / 2.0f, +0.0f));
                cCx->mat_color = Color(0.8, 0.8, 0.8);
                cCx->phong_factor = PHONG_FACTOR;
                cCx->inverse_modelling_matrix = translationmatrix;
                cCx->normal_matrix = glm::transpose(matrix);
            } else if (rotation == 2) {
                matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.5, 1.5f, 1.5f))
                         * glm::rotate(glm::mat4(1.0f), +0.5f * pi, glm::vec3(0.0f, 1.0f, 0.0f));
                translationmatrix = glm::translate(matrix, glm::vec3(0.0f, 1.74f / 2.0f, +0.0f));
                cCx->mat_color = Color(0.8, 0.8, 0.8);
                cCx->phong_factor = PHONG_FACTOR;
                cCx->inverse_modelling_matrix = translationmatrix;
                cCx->normal_matrix = glm::transpose(matrix);
            } else if (rotation == 3) {
                matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.5, 1.5f, 1.5f))
                         * glm::rotate(glm::mat4(1.0f), 0.0f * pi, glm::vec3(0.0f, 0.0f, 1.0f));
                translationmatrix = glm::translate(matrix, glm::vec3(0.0f, 1.74f / 2.0f, +0.0f));
                cCx->mat_color = Color(0.8, 0.8, 0.8);
                cCx->phong_factor = PHONG_FACTOR;
                cCx->inverse_modelling_matrix = translationmatrix;
                cCx->normal_matrix = glm::transpose(matrix);
            } else if (rotation == 4) {
                matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.5, 1.5f, 1.5f))
                         * glm::rotate(glm::mat4(1.0f), -0.25f * pi, glm::vec3(1.0f, 1.0f, 0.0f));
                translationmatrix = glm::translate(matrix, glm::vec3(0.0f, 1.74f / 2.0f, +0.0f));
                cCx->mat_color = Color(0.8, 0.8, 0.8);
                cCx->phong_factor = PHONG_FACTOR;
                cCx->inverse_modelling_matrix = translationmatrix;
                cCx->normal_matrix = glm::transpose(matrix);
            }
            scene.emplace_back(cCx);
        }
    }




    /* Transform pixel increment to canvas increment; scanline order is decreasing y-coordinate */
    glm::vec3 CanvasOrigin = glm::vec3(CANVAS_ORIG_X, CANVAS_ORIG_Y, CANVAS_ORIG_Z);
    glm::vec3 CanvasUp = glm::vec3(CANVAS_UP_X, CANVAS_UP_Y, CANVAS_UP_Z);
    glm::vec3 CanvasRight = glm::vec3(CANVAS_RIGHT_X, CANVAS_RIGHT_Y, CANVAS_RIGHT_Z);
    glm::vec3 StepUp = glm::vec3(CanvasUp.x / IMAGE_HEIGHT, CanvasUp.y / IMAGE_HEIGHT, CanvasUp.z / IMAGE_HEIGHT);
    glm::vec3 StepRight = glm::vec3(CanvasRight.x / IMAGE_WIDTH, CanvasRight.y / IMAGE_WIDTH,
                                    CanvasRight.z / IMAGE_WIDTH);

    glm::vec4 EyePoint = glm::vec4(EYE_POINT_X, EYE_POINT_Y, EYE_POINT_Z, 1.0);
    glm::vec4 direction = glm::vec4(0.0, 0.0, 0.0,
                                    0.0);//  Direction of ray:   X = startpoint + parameterArray*direction
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

            GeometricObject *current = nullptr;
            double current_t;

            for (auto *obj : scene) {
                number = obj->trace_ray(EyePoint, direction);
                if (number != 0) {
                    if (current != nullptr) {
                        //std::cout << parameterArray[0] << ", " << current_t << std::endl;
                        if (obj->cache[0] < current_t) {
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