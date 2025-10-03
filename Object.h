#pragma once

#include "ConsoleRenderer.h"
#include "Transform.h"

namespace aie
{

    class Object
    {
    public:
        // TODO: Should we really name it the same name as the type?
        Transform MyTransform;
        Geometry* Geo;

        Shader* Shad;

        Object();

        virtual void Tick(float deltaTime) {}
        virtual void Draw() const;
    };

}