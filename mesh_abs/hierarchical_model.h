/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_HIERARCHICAL_MODEL_H_
#define MOSHI3D_HIERARCHICAL_MODEL_H_

#include "mesh.h"
#include "transformation.h"
#include "rooted_DAG.hpp"
#include "renderizable.h"
#include <unordered_map>
#include <vector>

class HierarchicalModel : public Renderizable {
public:
    virtual ~HierarchicalModel() = 0;
    void draw(const Renderer& r, const std::vector<const Transformation*>& tv={}) const;

protected:
    typedef unsigned mesh_id_t;
    typedef unsigned transformation_id_t;
    typedef unsigned hierarchical_model_id_t;
    typedef unsigned node_id_t;

    HierarchicalModel() {}
    HierarchicalModel(const HierarchicalModel& h) = delete; // Copy constructor not implemented in RootedDAG

    void touch(mesh_id_t mesh_id, const Mesh3D& m);
    void touch(transformation_id_t transformation_id, const Transformation& t);
    void touch(hierarchical_model_id_t hierarchical_model_id, const HierarchicalModel& hm);
    void set_node_meshes(node_id_t id, const std::vector<mesh_id_t>& meshes);   
    void set_node_transformations(node_id_t id, const std::vector<transformation_id_t>& transformations);
    void set_node_hierarchical_models(node_id_t node_id, const std::vector<hierarchical_model_id_t>& hierarchical_model_ids);

    RootedDAG<node_id_t> node_DAG;
private:
    struct NodeData {
        std::vector<mesh_id_t> mesh_ids;
        std::vector<transformation_id_t> transformation_ids;
        std::vector<hierarchical_model_id_t> hierarchical_model_ids;
    };
    
    std::unordered_map<mesh_id_t, const Mesh3D*> rel_meshId_mesh;
    std::unordered_map<transformation_id_t, const Transformation*> rel_transformationId_transformation;
    std::unordered_map<hierarchical_model_id_t, const HierarchicalModel*> rel_hierarchicalModelId_hierarchicalModel;

    std::unordered_map<node_id_t, NodeData> rel_nodeId_nodeData;

    void draw_node(const RootedDAG<node_id_t>::iterator& it, const Renderer& r, const std::vector<const Transformation*>& tv={}) const;
    RootedDAG<node_id_t>::iterator draw_childs(const RootedDAG<node_id_t>::iterator& it, const Renderer& r, const std::vector<const Transformation*>& tv={}) const;
};

#endif /* MOSHI3D_HIERARCHICAL_MODEL_H_*/