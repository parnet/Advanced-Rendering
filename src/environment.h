//
// Created by Parnet on 2020-06-04.
//

#ifndef ADVRENDERING_ENVIRONMENT_H
#define ADVRENDERING_ENVIRONMENT_H


#include <glm/vec4.hpp>
#include <iostream>
#include <glm/mat4x4.hpp>

void print(glm::vec4 & vec);

void print(glm::mat4 & mat);

void print(std::string str, glm::vec4 & vec);

void print(std::string str, glm::mat4 & mat);
#endif //ADVRENDERING_ENVIRONMENT_H
