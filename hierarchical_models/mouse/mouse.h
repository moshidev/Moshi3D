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

    static void set_moving_animation_leg(Animation& anim, float peak_angle);
    static void set_moving_animation_trunk(Animation& anim, float peak_angle);
    static CompositionNode build_leg(const std::shared_ptr<Cylinder>& leg, float peak_angle);
    static CompositionNode build_trunk(const std::shared_ptr<Renderizable>& trunk);

public:
    Mouse();

    void draw(const Renderer& r, float time_point) const;
};  

#endif /* MOSHI3D_HIERARCHICAL_MODELS_MOUSE_H_ */