/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_PROJFINAL_H_
#define MOSHI3D_PROJFINAL_H_

#include "composition_node.h"
#include "renderizable.h"
#include "revolution_object.h"
#include "bouncy_ball.h"
#include "rectangle.h"
#include "chipmunk.h"
#include "room.h"
#include <memory>

class ProjFinal : public Renderizable {
    CompositionNode root;
    std::unique_ptr<Room> room;
    std::unique_ptr<Chipmunk> chipmunk;
    std::unique_ptr<BouncyBall> bouncy_ball;
    std::shared_ptr<PositionalLight> bouncy_ball_light;
    std::shared_ptr<RevolutionObject> peon_marmol;
    std::shared_ptr<RevolutionObject> peon_negro;
    std::shared_ptr<RevolutionObject> cola_can;
    std::shared_ptr<Rectangle> aurora;
    float manual_step_size {0.1};

public:
    ProjFinal();

    void draw(Renderer& r) const;
    void apply_lights(void) const;
    void increment_animation_aut(void);
    void increment_animation_man(void);
    void multiply_speed_factor(float factor);
    void apply_to_meshes(const std::function<void(Mesh3D&)>& func);
    CompositionNode& select_object(int x, int y);
};

#endif /* MOSHI3D_PROJFINAL_H_ */