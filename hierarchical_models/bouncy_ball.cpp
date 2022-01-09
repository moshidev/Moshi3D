#include "bouncy_ball.h"
#include "tuplasg.h"
#include "translation.h"
#include "scaling.h"

BouncyBall::BouncyBall(unsigned n, float r) {
    std::shared_ptr<PositionalLight> light = std::make_shared<PositionalLight>(Tupla3f{0,0,0});
    ball_mesh = std::make_shared<Sphere>(n, n, r);
    light->activate(true);
    ball_mesh->enable_shaded_mode(true);
    ball = build_ball(root, ball_mesh, light);
}

BouncyBall::BouncyBall(const std::shared_ptr<PositionalLight>& light, unsigned n, float r) {
    ball_mesh = std::make_shared<Sphere>(n, n, r);
    ball_mesh->enable_shaded_mode(true);
    ball = build_ball(root, ball_mesh, light);
}

BouncyBall::BouncyBall(const std::shared_ptr<Sphere>& sphere) {
    std::shared_ptr<PositionalLight> light = std::make_shared<PositionalLight>(Tupla3f{0,0,0});
    light->activate(true);
    ball_mesh = sphere;
    ball = build_ball(root, ball_mesh, light);
}

BouncyBall::BouncyBall(const std::shared_ptr<Sphere>& sphere, const std::shared_ptr<PositionalLight>& light) {
    ball_mesh = sphere;
    ball = build_ball(root, ball_mesh, light);
}

void BouncyBall::draw(const Renderer& r) const {
    root.draw(r);
}

void BouncyBall::apply_lights(void) const {
    root.apply_lights();
}

void BouncyBall::set_texture(const std::shared_ptr<TextureObject>& texture) {
    ball_mesh->set_texture(texture);
}

void BouncyBall::set_material(const Material& material) {
    ball_mesh->set_material(material);
}

void BouncyBall::increment_animation_aut(void) {
    ball->second->get_animation().increment_anim_loop();
}

void BouncyBall::increment_animation_man(void) {
    ball->second->get_animation().increment_anim(manual_step_size);
}

void BouncyBall::multiply_speed_factor(float factor) {
    auto& a = ball->second->get_animation();
    a.set_speed_factor(factor * a.get_speed_factor());
}

void BouncyBall::apply_to_meshes(const std::function<void(Mesh3D&)>& func) {
    func(*ball_mesh);
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