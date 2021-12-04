#include "mouse.h"

Mouse::Mouse()
:leg_mesh{std::make_shared<Cylinder>(8, 8, 1, 0.5)}
{
    auto root = composition.get_root();
    composition.add_child(root, build_leg(leg_mesh));
    leg_mesh->enable_chess_mode(true);
}

void Mouse::build_default_animation(Animation& anim, const Tupla3f& rot_point) {
    anim.atributes.loop = true;
    PointRotation pr_a{M_PI_4, {1,0,0}, rot_point};
    PointRotation pr_b{-M_PI_4, {1,0,0}, rot_point};
    auto func = [](float p) {return 1-p*p;};
    TransformationTimeline<PointRotation>::KeyFrame kf_a{0, pr_a, func};
    TransformationTimeline<PointRotation>::KeyFrame kf_b{1, pr_b, func};
    TransformationTimeline<PointRotation>::KeyFrame kf_c{2, pr_a, func};
    anim.rotation_tt.add_key_frame(kf_a);
    anim.rotation_tt.add_key_frame(kf_b);
    anim.rotation_tt.add_key_frame(kf_c);
}

CompositionNode Mouse::build_leg(const std::shared_ptr<Renderizable>& leg) {
    CompositionNode::Object obj{leg};
    obj.atributes.name = "mouse_obj_leg";

    CompositionNode c;
    c.add_object(obj);
    c.get_atributes().name = "mouse_leg_comp";
    build_default_animation(c.get_animation(), {0,0,0});
    return c;
}

void Mouse::draw(const Renderer& r) const {
    composition.draw(r);
}