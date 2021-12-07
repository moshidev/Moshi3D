#include "mouse.h"
#include "rotation.h"
#include <limits>
#include "cube.h"
#include "objply.h"

Mouse::Mouse()
:leg_mesh{std::make_shared<Cylinder>(2, 8, 1, 0.15)}
{
    std::shared_ptr<Cube> cube {std::make_shared<Cube>(2)};
    std::shared_ptr<ObjPLY> mice {std::make_shared<ObjPLY>("resources/pie_kirby_mesh.ply")};
    leg_mesh->enable_chess_mode(true);
    mice->enable_chess_mode(true);
    cube->enable_chess_mode(true);
    auto root = composition.get_root();
    (*root).atributes.duration = std::numeric_limits<float>::max();
    (*root).atributes.location.position = {0,1,0};
    set_moving_animation_trunk((*root).animation, M_PI_4/8);
    auto trunk = composition.emplace_child(root, build_trunk(mice));
    CompositionNode leg {build_leg(leg_mesh, M_PI_4/2)};
    CompositionNode topr_leg;
    CompositionNode topl_leg;
    CompositionNode downr_leg;
    CompositionNode downl_leg;
    topr_leg.atributes.location.position = {+0.25,0,-0.5};
    topr_leg.atributes.init_time = 0;
    topl_leg.atributes.location.position = {-0.25,0,-0.5};
    topl_leg.atributes.init_time = 1.9;
    downr_leg.atributes.location.position = {+0.5,0,+0.5};
    downr_leg.atributes.init_time = 1;
    downl_leg.atributes.location.position = {-0.5,0,+0.5};
    downl_leg.atributes.init_time = 2.9;
    auto top_right_it = composition.emplace_child(trunk, topr_leg);
    auto top_left_it = composition.emplace_child(trunk, topl_leg);
    auto down_right_it = composition.emplace_child(trunk, downr_leg);
    auto down_left_it = composition.emplace_child(trunk, downl_leg);
    auto leg_it = composition.emplace_child(top_right_it, leg);
    composition.add_child_to_parent(top_left_it, leg_it);
    composition.add_child_to_parent(down_right_it, leg_it);
    composition.add_child_to_parent(down_left_it, leg_it);
}

void Mouse::set_moving_animation_leg(Animation& anim, float peak_angle) {
    Rotation rot_a{{0,0}};
    Rotation rot_b{{peak_angle,0}};
    Rotation rot_c{{-peak_angle,0}};
    auto func_a = [] (float p) { return 1-(p-1)*(p-1);};
    auto func_b = [] (float p) { return p*p;};
    anim.rotation_tt.add_key_frame({0, rot_a, func_a});
    anim.rotation_tt.add_key_frame({1, rot_b, func_b});
    anim.rotation_tt.add_key_frame({2, rot_a, func_a});
    anim.rotation_tt.add_key_frame({3, rot_c, func_b});
    anim.rotation_tt.add_key_frame({4, rot_a});
    anim.loop = true;
}

CompositionNode Mouse::build_leg(const std::shared_ptr<Cylinder>& leg, float peak_angle) {
    CompositionNode::Object obj{leg};
    obj.atributes.name = "mouse_leg_mesh";
    obj.atributes.location.rotation_polar = {-M_PI,0};

    CompositionNode c;
    c.emplace_object(obj);
    c.atributes.name = "mouse_leg";
    c.atributes.duration = std::numeric_limits<float>::max();
    c.atributes.loop = true;
    set_moving_animation_leg(c.animation, peak_angle);
    return c;
}

void Mouse::set_moving_animation_trunk(Animation& anim, float peak_angle) {
    Rotation rot_a{{-peak_angle/2,0}};
    Rotation rot_b{{peak_angle/2,0}};
    auto func_a = [] (float p) { return 1-(p-1)*(p-1);};
    auto func_b = [] (float p) { return p*p;};
    anim.rotation_tt.add_key_frame({0, rot_b, func_b});
    anim.rotation_tt.add_key_frame({1, rot_a, func_a});
    anim.rotation_tt.add_key_frame({2, rot_b});
    anim.loop = true;
}

CompositionNode Mouse::build_trunk(const std::shared_ptr<Renderizable>& trunk) {
    CompositionNode::Object obj{trunk};
    obj.atributes.name = "mouse_trunk_mesh";
    obj.atributes.location.position = {0.2,-1.25,-2};
    obj.atributes.location.rotation_polar = {M_PI_2, M_PI};
    obj.atributes.location.scaling = {0.45,0.45,0.45};

    CompositionNode c;
    c.emplace_object(obj);
    c.atributes.location.position = {0,0,0};
    c.atributes.name = "mouse_trunk";
    c.atributes.duration = std::numeric_limits<float>::max();
    c.atributes.loop = true;

    return c;
}

void Mouse::draw(const Renderer& r, float time_point) const {
     composition.draw(r, time_point);
}

/*
auto trunk = composition.emplace_child(root, build_trunk(cube, M_PI_4/14));
    auto leg_topr = composition.emplace_child(root, build_leg(leg_mesh, M_PI_4/2));
    auto leg_topl = composition.emplace_child(root, build_leg(leg_mesh, M_PI_4/2));
    auto leg_downr = composition.emplace_child(root, build_leg(leg_mesh, M_PI_4/2));
    auto leg_downl = composition.emplace_child(root, build_leg(leg_mesh, M_PI_4/2));
    (*leg_topr).atributes.location.position = {0.25, 0, -1};
    (*leg_topl).atributes.init_time = 1.9;
    (*leg_topl).atributes.location.position = {-0.25, 0, -1};
    (*leg_downr).atributes.init_time = 3;
    (*leg_downr).atributes.location.position = {0.5, 0, 1};
    (*leg_downl).atributes.init_time = 0.9;
    (*leg_downl).atributes.location.position = {-0.5, 0, 1};
*/