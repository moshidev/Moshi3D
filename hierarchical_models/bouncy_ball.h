/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_BOUNCY_BALL_H_
#define MOSHI3D_BOUNCY_BALL_H_

#include "composition_node.h"
#include "positional_light.h"
#include "renderizable.h"
#include "sphere.h"
#include <memory>

class BouncyBall : public Renderizable {
    CompositionNode root;
    CompositionNode::iterator ball;
    float manual_step_size {0.1};
    std::shared_ptr<Sphere> ball_mesh;

    static CompositionNode::iterator build_ball(CompositionNode& parent, const std::shared_ptr<Sphere>& sphere, const std::shared_ptr<PositionalLight>& light);
    static void set_ball_bouncing(Animation& anim, float percentaje_offset, float distance, float speed_factor);

public:
    BouncyBall(unsigned n=60, float r=1);
    BouncyBall(const BouncyBall& b) = default;
    BouncyBall(const std::shared_ptr<PositionalLight>& light, unsigned n=60, float r=1);
    BouncyBall(const std::shared_ptr<Sphere>& sphere);
    BouncyBall(const std::shared_ptr<Sphere>& sphere, const std::shared_ptr<PositionalLight>& light);

    void draw(const Renderer& r) const;
    void apply_lights(void) const;
    void increment_animation_aut(void);
    void increment_animation_man(void);
    void multiply_speed_factor(float factor);
    void apply_to_meshes(const std::function<void(Mesh3D&)>& func);
};

#endif /* MOSHI3D_BOUNCY_BALL_H_ */