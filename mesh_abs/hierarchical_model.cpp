#include "hierarchical_model.h"

HierarchicalModel::~HierarchicalModel()
{   }

void HierarchicalModel::touch(mesh_id_t mesh_id, const Mesh3D& m) {
    rel_meshId_mesh[mesh_id] = &m;
}

void HierarchicalModel::touch(transformation_id_t transformation_id, const Transformation& t) {
    rel_transformationId_transformation[transformation_id] = &t;
}

void HierarchicalModel::touch(hierarchical_model_id_t hierarchical_model_id, const HierarchicalModel& hm) {
    rel_hierarchicalModelId_hierarchicalModel[hierarchical_model_id] = &hm;
}

void HierarchicalModel::set_node_meshes(node_id_t node_id, const std::vector<mesh_id_t>& meshes_ids) {
    rel_nodeId_nodeData[node_id].mesh_ids = meshes_ids;
}

void HierarchicalModel::set_node_transformations(node_id_t node_id, const std::vector<transformation_id_t>& transformations_ids) {
    rel_nodeId_nodeData[node_id].transformation_ids = transformations_ids;
}

void HierarchicalModel::set_node_hierarchical_models(node_id_t node_id, const std::vector<hierarchical_model_id_t>& hierarchical_model_ids) {
    rel_nodeId_nodeData[node_id].hierarchical_model_ids = hierarchical_model_ids;
}

void HierarchicalModel::draw_node(const RootedDAG<node_id_t>::iterator& it, const Renderer& r) const {
    const auto& node = rel_nodeId_nodeData.at(*it);
    for (const auto& t_id: node.transformation_ids) {
        rel_transformationId_transformation.at(t_id)->apply();
    }
    for (const auto& m_id : node.mesh_ids) {
        rel_meshId_mesh.at(m_id)->draw(r);
    }
    for (const auto& hm_id : node.hierarchical_model_ids) {
        rel_hierarchicalModelId_hierarchicalModel.at(hm_id)->draw(r);
    }
}

RootedDAG<HierarchicalModel::node_id_t>::iterator HierarchicalModel::draw_childs(const RootedDAG<node_id_t>::iterator& it, const Renderer& r) const {
    auto ret = it;
    auto child = it.get_first_child();
    while (child != node_DAG.end()) {
        Transformation::push_matrix();
        draw_node(child, r);
        ret = child;
        child = child.get_first_child();
    }
    return ret;
}

void HierarchicalModel::draw(const Renderer& r) const {
    auto it = node_DAG.get_root();
    auto parent = it;
    auto rbrother = it;
    Transformation::push_matrix();
    while (parent != node_DAG.end() || rbrother != node_DAG.end()) {
        parent = rbrother.get_last_parent();
        if (rbrother != node_DAG.end()) {
            draw_node(rbrother, r);
            rbrother = draw_childs(rbrother, r).get_rbrother();
        }
        else {
            rbrother = parent;
            Transformation::pop_matrix();
        }
    }
    Transformation::pop_matrix();
}