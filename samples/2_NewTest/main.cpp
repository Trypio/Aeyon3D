
#include "../../engine/include/Transform.hpp"
#include "../../engine/include/Actor.hpp"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/euler_angles.hpp>

#define VARNAME(var) #var

using namespace aeyon;

void printTransform(const Transform& t, const std::string& name)
{
    std::cout << name << ".position = " << glm::to_string(t.getPosition()) << std::endl;
    std::cout << name << ".localPosition = " << glm::to_string(t.getLocalPosition()) << std::endl;
    std::cout << name << ".rotation = " << glm::to_string(t.getRotation()) << std::endl;
    std::cout << name << ".localRotation = " << glm::to_string(t.getLocalRotation()) << std::endl;
    std::cout << name << ".eulerAngles = " << glm::to_string(t.getEulerAngles()) << std::endl;
    std::cout << name << ".localEulerAngles = " << glm::to_string(t.getLocalEulerAngles()) << std::endl;
    std::cout << name << ".scale = " << glm::to_string(t.getScale()) << std::endl;
    std::cout << name << ".localScale = " << glm::to_string(t.getLocalScale()) << std::endl;
    std::cout << std::endl;
}


int main(int argc, char* argv[])
{
    Transform t1, t2;

    t1.setPosition({-3.0f, 0.0f, 0.0f});
    t1.setRotation({0.0f, 0.0f, 0.0f});
    t1.setLocalScale(glm::vec3(1.0f, 1.0f, 1.0f));

    //t1.rotate({45.0f, 90.0f, 0.0f});
    t1.setLocalRotation({45.0f, 90.0f, 0.0f});

//    printTransform(t1, VARNAME(t1));

//    t2.setParent(&t1);
//
//    printTransform(t2, VARNAME(t2));

    std::cout << glm::to_string(glm::degrees(glm::eulerAngles(glm::quat(glm::eulerAngleZYX(glm::radians(45.0f), (glm::radians(90.0f)), (glm::radians(0.0f))))))) << std::endl;


	return 0;
}

