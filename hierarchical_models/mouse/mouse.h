/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_HIERARCHICAL_MODELS_MOUSE_H_
#define MOSHI3D_HIERARCHICAL_MODELS_MOUSE_H_

#include "renderizable.h"
#include "cylinder.h"
#include "composition.h"

class Mouse : public Renderizable {
    Composition composition;
    std::shared_ptr<Cylinder> leg_mesh;
    static void build_default_animation(Animation& anim, const Tupla3f& rot_point);
    static CompositionNode build_leg(const std::shared_ptr<Renderizable>& leg);
public: 
    Mouse();

    void draw(const Renderer& r) const;
};  

#endif /* MOSHI3D_HIERARCHICAL_MODELS_MOUSE_H_ */