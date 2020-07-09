//
// Created by Parnet on 2020-06-04.
//

#include "environment.h"

void print(glm::vec4 &vec) {
    {
        std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
    }
}

void print(glm::mat4 &mat) {
    {
        for(size_t i = 0 ;  i < 4; i++) {
            std::cout << "|" << mat[i].x << ", " << mat[i].y << ", " << mat[i].z << ", " << mat[i].w << "|"
                      << std::endl;
        }
    }
}

void print(std::string str, glm::vec4 &vec) {
    std::cout << str << ": ";
    print(vec);
}

void print(std::string str, glm::mat4 &mat) {
    std::cout << "=== " << str <<" ===" << std::endl;
    print(mat);
}


