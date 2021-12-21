#include "bouncy_ball.h"
#include "tuplasg.h"
#include "translation.h"
#include "scaling.h"

BouncyBall::BouncyBall(unsigned n, float r) {
    std::shared_ptr<PositionalLight> light = std::make_shared<PositionalLight>(Tupla3f{0,0,0});
    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(n, n, r);
    light->activate(true);
    sphere->enable_shaded_mode(true);
    ball = build_ball(root, sphere, light);
}

BouncyBall::BouncyBall(const std::shared_ptr<PositionalLight>& light, unsigned n, float r) {
    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(n, n, r);
    sphere->enable_shaded_mode(true);
    ball = build_ball(root, sphere, light);
}

BouncyBall::BouncyBall(const std::shared_ptr<Sphere>& sphere) {
    std::shared_ptr<PositionalLight> light = std::make_shared<PositionalLight>(Tupla3f{0,0,0});
    light->activate(true);
    ball = build_ball(root, sphere, light);
}

BouncyBall::BouncyBall(const std::shared_ptr<Sphere>& sphere, const std::shared_ptr<PositionalLight>& light) {
    ball = build_ball(root, sphere, light);
}

void BouncyBall::draw(const Renderer& r) const {
    root.draw(r);
}

void BouncyBall::apply_lights(void) const {
    root.apply_lights();
}

void BouncyBall::increment_animation_aut(void) {
    ball->second->get_animation().increment_anim_loop();
}

CompositionNode::iterator BouncyBall::build_ball(CompositionNode& parent, const std::shared_ptr<Sphere>& sphere, const std::shared_ptr<PositionalLight>& light) {
    CompositionNode::Object obj{sphere, light};
    CompositionNode::iterator ball;
    ball = parent.add_child(std::make_shared<CompositionNode>(obj));
    set_ball_bouncing(ball->second->get_animation(), 0, 3, 2);
    return ball;   
}

void BouncyBall::set_ball_bouncing(Animation& anim, float percentaje_offset, float distance, float speed_factor) {
    auto func_up = [] (float p) { return 1-(p-1)*(p-1); };
    auto func_down = [] (float p) { return p*p; };
    TransformationTimeline<Translation>::KeyFrame post_a{0, Tupla3f{0,0,0}, func_up};
    TransformationTimeline<Translation>::KeyFrame post_b{1, Tupla3f{0,distance,0}, func_down};
    TransformationTimeline<Translation>::KeyFrame post_c{2, Tupla3f{0,0,0}};
    TransformationTimeline<Scaling>::KeyFrame poss_a{0, Tupla3f{1,0.5,1}};
    TransformationTimeline<Scaling>::KeyFrame poss_b{0.2, Tupla3f{1,1.25,1}};
    TransformationTimeline<Scaling>::KeyFrame poss_c{0.3, Tupla3f{1,1,1}};
    TransformationTimeline<Scaling>::KeyFrame poss_d{1.8, Tupla3f{1,1,1}};
    TransformationTimeline<Scaling>::KeyFrame poss_f{2, Tupla3f{1,0.5,1}};
    anim.translation_tt.add_key_frame(post_a);
    anim.translation_tt.add_key_frame(post_b);
    anim.translation_tt.add_key_frame(post_c);
    anim.scaling_tt.add_key_frame(poss_a);
    anim.scaling_tt.add_key_frame(poss_b);
    anim.scaling_tt.add_key_frame(poss_c);
    anim.scaling_tt.add_key_frame(poss_d);
    anim.scaling_tt.add_key_frame(poss_f);
    anim.set_percentaje(percentaje_offset);
    anim.set_speed_factor(speed_factor);
}