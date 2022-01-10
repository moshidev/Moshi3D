#include "proj_final.h"
#include "positional_light.h"
#include "renderer_selector.h"

ProjFinal::ProjFinal() {
    static Material blanco_difuso{{1, 1, 1, 1}, {0, 0, 0, 1}, {0.5, 0.5, 0.5, 1}, 64};  // src: http://devernay.free.fr/cours/opengl/materials.html
    static Material negro_brillo{{0, 0, 0, 1}, {1, 1, 1, 1}, {0, 0, 0, 1}, 128};
    bouncy_ball_light = std::make_shared<PositionalLight>(Tupla3f{0,0,0}, Tupla4f{1.0,0.0,0.2,1}, Tupla4f{1.0,0.0,0.2,1}, Tupla4f{1.0,0.0,0.2,1});
    bouncy_ball_light->activate(true);

    bouncy_ball = std::make_unique<BouncyBall>(bouncy_ball_light);
    bouncy_ball->set_texture(std::make_shared<TextureObject>("resources/wall.jpg"));
    chipmunk = std::make_unique<Chipmunk>();
    room = std::make_unique<Room>(Tupla3f{30, 30, 10});
    peon_marmol = std::make_shared<RevolutionObject>("resources/peon.ply", 40);
    peon_marmol->set_texture(std::make_shared<TextureObject>("resources/marble.jpg"));
    peon_marmol->set_material(blanco_difuso);
    peon_negro = std::make_shared<RevolutionObject>("resources/peon.ply", 40);
    peon_negro->set_material(negro_brillo);
    cola_can = std::make_shared<RevolutionObject>("resources/lata-pcue.ply", 40);
    cola_can->set_texture(std::make_shared<TextureObject>("resources/text-lata-1.jpg"));
    aurora = std::make_shared<Rectangle>(Tupla2f{30, 10});
    aurora->set_texture(std::make_shared<TextureObject>("resources/aurora.jpg"));
    
    std::shared_ptr<CompositionNode> bouncy_ball_node = std::make_shared<CompositionNode>(bouncy_ball->get_root());
    root.add_child(bouncy_ball_node)->first.position = {0, 0.5, -1};
    root.add_child(std::make_shared<CompositionNode>(chipmunk->get_root()))->first.position = {0, 0, 2};
    root.add_child(std::make_shared<CompositionNode>(room->get_root()));
    CompositionNode::iterator it = root.add_child(std::make_shared<CompositionNode>(CompositionNode::Object{cola_can}));
    it->first.position = {0, 0, -12};
    it->first.scaling = {9.5, 9.5, 9.5};
    it->second->get_location().rotation = {0, -M_PI_2, 0};
    root.add_child(std::make_shared<CompositionNode>(CompositionNode::Object{aurora}))->first.position = {0, 5, -14};
    root.add_child(std::make_shared<CompositionNode>(CompositionNode::Object{peon_marmol}))->first.position = {-1.5, 1.5, -3};
    root.add_child(std::make_shared<CompositionNode>(CompositionNode::Object{peon_negro}))->first.position = {+1.5, 1.5, -3};
    
    apply_to_meshes([](Mesh3D& m){m.enable_shaded_mode(true);});
}

void ProjFinal::draw(Renderer& r) const {
    root.draw(r);
}

void ProjFinal::apply_lights(void) const {
    root.apply_lights();
}

void ProjFinal::increment_animation_aut(void) {
    auto func = [] (CompositionNode& c) {
        auto& a = c.get_animation();
        a.set_speed_factor(std::abs(a.get_speed_factor()));
        a.increment_anim_loop();
    };
    root.execute_preorder(func);
}

void ProjFinal::increment_animation_man(void) {
    auto func = [this] (CompositionNode& c) {
        auto& a = c.get_animation();
        a.set_speed_factor(std::abs(a.get_speed_factor()));
        a.increment_anim_loop(manual_step_size);
    };
    root.execute_preorder(func);
}

void ProjFinal::multiply_speed_factor(float factor) {
    auto func = [factor] (CompositionNode& c) {
        auto& a = c.get_animation();
        a.set_speed_factor(factor*std::abs(a.get_speed_factor()));
    };
    root.execute_preorder(func);
}

void ProjFinal::apply_to_meshes(const std::function<void(Mesh3D&)>& func) {
    chipmunk->apply_to_meshes(func);
    bouncy_ball->apply_to_meshes(func);
    room->apply_to_meshes(func);
    func(*peon_marmol);
    func(*peon_negro);
    func(*aurora);
    func(*cola_can);
}