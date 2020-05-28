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


int main (int argc, char* argv[]) {
    const int width = IMAGE_WIDTH;
    const int height = IMAGE_HEIGHT;

    unsigned char *image = new unsigned char[width * height * 4];


  int red, green, blue;

  int number;

  GeometricObject *p_Object  =  new torus(TORUS_r);
  //GeometricObject *p_Object  =  new Sphere();             //Object Creation

  glm::mat4 matrix;

  matrix =   glm::scale( glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))* glm::rotate (glm::mat4(1.0f), 0.0f*pi, glm::vec3(1.0f, 1.0f, 1.0f));



  p_Object->inverse_modelling_matrix =      glm::translate(matrix, glm::vec3 (0.0f, 0.0f, 0.0f));
  p_Object->normal_matrix            =      glm::transpose (matrix);


  p_Object->mat_color    = Color (1.0,0,0);
  p_Object->phong_factor = PHONG_FACTOR;



 /* Transform pixel increment to canvas increment; scanline order is decreasing y-coordinate */


 glm::vec3  CanvasOrigin = glm::vec3 ( CANVAS_ORIG_X, CANVAS_ORIG_Y, CANVAS_ORIG_Z);
 glm::vec3  CanvasUp     = glm::vec3 ( CANVAS_UP_X,  CANVAS_UP_Y,  CANVAS_UP_Z);
 glm::vec3  CanvasRight  = glm::vec3 ( CANVAS_RIGHT_X,  CANVAS_RIGHT_Y, CANVAS_RIGHT_Z);
 glm::vec3  StepUp       = glm::vec3 ( CanvasUp.x / IMAGE_HEIGHT,  CanvasUp.y / IMAGE_HEIGHT,  CanvasUp.z / IMAGE_HEIGHT);
 glm::vec3  StepRight    = glm::vec3 ( CanvasRight.x / IMAGE_WIDTH, CanvasRight.y / IMAGE_WIDTH, CanvasRight.z/ IMAGE_WIDTH);

 glm::vec4  EyePoint     = glm::vec4 ( EYE_POINT_X, EYE_POINT_Y,  EYE_POINT_Z, 1.0);
 glm::vec4  Dir          = glm::vec4 ( 0.0, 0.0, 0.0, 0.0);                          //  Direction of ray:   X = startpoint + t*direction
 glm::vec4  Normal       = glm::vec4 (0.0, 0.0, 0.0, 0.0);

 double t[4]            =  { 0.0, 0.0, 0.0, 0.0 };                                  //  Array of vector/intersection parameters


  /* Set Background Color */

  for (unsigned short row = 0; row < height; row++) {
      for (unsigned short column = 0; column < width; column++) {
          image[4*width*row + 4*column+0] = BACKGROUND_COLOR_R;
          image[4*width*row + 4*column+1] = BACKGROUND_COLOR_G;
          image[4*width*row + 4*column+2] = BACKGROUND_COLOR_B;
          image[4*width*row + 4*column+3] = BACKGROUND_COLOR_A;
      }
  }

  cout << "/****   Program started!  *****/" << endl;

  for (unsigned short row = 0; row < height; ++row)  {
      for (unsigned short column = 0; column < width; ++column)      {
         Dir = glm::vec4(
                CanvasOrigin.x + 0.5*StepRight.x + column*StepRight.x + (IMAGE_HEIGHT-0.5-row)*StepUp.x - EyePoint.x,
                CanvasOrigin.y + 0.5*StepRight.y + column*StepRight.y + (IMAGE_HEIGHT-0.5-row)*StepUp.y - EyePoint.y,
                CanvasOrigin.z + 0.5*StepRight.z + column*StepRight.z + (IMAGE_HEIGHT-0.5-row)*StepUp.z - EyePoint.z,
                0.0
                );


         number = p_Object->trace_ray(EyePoint, Dir, t);           // intersect ray with object



         //cout<<number<<endl;



         if ( number > 0 )
            {
              double dotprod;
              double diffuse_intensity;
              double specular_intensity;
              glm::vec4 Intersection;
              glm::vec4 H;

              Normal = p_Object->get_normal(EyePoint, Dir, t[0]);            //  Normal of nearest object


              /* Diffuse Reflexion */
              dotprod = glm::dot(Normal, glm::normalize(glm::vec4(DIFFUSE_DIR_X, DIFFUSE_DIR_Y, DIFFUSE_DIR_Z, 0.0f)));
              diffuse_intensity = dotprod >= AMBIENT_INTENSITY ? dotprod : AMBIENT_INTENSITY;



              /* Calculation of Specular Reflexion by Phong resp. Blinn */

              /* Vector H = L+V/|L+V|; V = direction from intersection to eyepoint = - Dir, L = direction from intersection to light source */
              Intersection = EyePoint + (float) t[0] * Dir;
              H = glm::normalize(glm::vec4(SPECULAR_X, SPECULAR_Y,SPECULAR_Z, 1.0f) - Intersection - Dir);

              dotprod = glm::dot(Normal, H);

              if ( dotprod > 0)
                 {
                     specular_intensity = pow (dotprod, p_Object->phong_factor);
                 }
              else
                 specular_intensity = 0.0;



              /* Write Image File */
              red   =   p_Object->mat_color.r*255*diffuse_intensity+255*specular_intensity <= 255 ? p_Object->mat_color.r*255*diffuse_intensity+255*specular_intensity:255;
              green =   p_Object->mat_color.g*255*diffuse_intensity+255*specular_intensity <= 255 ? p_Object->mat_color.g*255*diffuse_intensity+255*specular_intensity:255;
              blue  =   p_Object->mat_color.b*255*diffuse_intensity+255*specular_intensity <= 255 ? p_Object->mat_color.b*255*diffuse_intensity+255*specular_intensity:255;
              image[4*width*row + 4*column+0] = red;
              image[4*width*row + 4*column+1] = green;
              image[4*width*row + 4*column+2] = blue;
              image[4*width*row + 4*column+3] = BACKGROUND_COLOR_A;
            } //end of "if (dotprod >0)"
      } //end of column loop
  } //end of row loop

  lodepng_encode32_file("Image.png",image,width,height);
  cout << "Image Drawn! File Written!" << endl;

  return 0;
};



