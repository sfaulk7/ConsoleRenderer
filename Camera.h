#pragma once

#include "Object.h"

namespace aie
{

    class Camera : public Object
    {
    public:
        float VerticalFov;

        float NearPlane;
        float FarPlane;

        Camera();

        glm::mat4 ViewMat();
        glm::mat4 ProjMat();
    };

}