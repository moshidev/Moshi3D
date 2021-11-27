/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * MIT License.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 * 
 * @brief DAG with a single source.
 * @warning Keep in mind that this is not STL compatible, nor a truly generic data structure. For now it is a quick draft for getting the job done.
 */

#ifndef MOSHI3D_ROOTED_DAG_H_
#define MOSHI3D_ROOTED_DAG_H_

#include <memory>
#include <vector>
#include <stack>
#include <iostream>

template<typename _Tp>
class RootedDAG {
    struct NodeData {
        typedef std::vector<NodeData*> nodelist_container_t;
        nodelist_container_t parents;
        nodelist_container_t childs;
        _Tp data;
    };

    NodeData* root{nullptr};

    bool find_circular_dependency(const NodeData& child, const NodeData& parent) const {
        if (&child == &parent) {
            return true;
        }

        for (auto& p : parent.parents) {
            if (find_circular_dependency(child, *p)) {
                return true;
            }
        }

        return false;
    }

public:
    class iterator {    // Not STL compilant...
        friend class RootedDAG;

        NodeData* node_ptr{nullptr};
        std::stack<NodeData*> last_parent_ptr;
        
        iterator(NodeData& root)
        :node_ptr{&root}
        {
            const auto* childs_v = &node_ptr->childs;
            while (!childs_v->empty()) {
                last_parent_ptr.push(node_ptr);
                node_ptr = childs_v->front();
                childs_v = &node_ptr->childs; // después de esto la raíz deja de tener hijos
            }
        }

        iterator(const iterator& it, NodeData& child)
        :node_ptr{&child}, last_parent_ptr{it.last_parent_ptr}
        {   }

        iterator() {    }

    public:
        inline _Tp& operator*() {
            return node_ptr->data;
        }
        inline bool operator<(const iterator& i) const {
            return node_ptr < i.node_ptr;
        }
        inline bool operator==(const iterator& i) const {
            return node_ptr == i.node_ptr;
        }
        inline bool operator!=(const iterator& i) const {
            return node_ptr != i.node_ptr;
        }
        iterator& operator++() {
            // Miramos a ver si nos quedan hermanos por visitar. Si nos quedan hermanos por visitar
            // nos desplazamos al hermano y a lo más a la izquierda del árbol posible
            if (!last_parent_ptr.empty()) {
                const auto& parent_child_v = last_parent_ptr.top()->childs;
                auto it_brother = ++std::find(parent_child_v.begin(), parent_child_v.end(), node_ptr);
                if (it_brother != parent_child_v.end()) {
                    node_ptr = *it_brother;

                    const auto* childs_v = &node_ptr->childs;
                    while (!childs_v->empty()) {
                        last_parent_ptr.push(node_ptr);
                        node_ptr = childs_v->front();
                        childs_v = &node_ptr->childs;
                    }

                    return *this;
                }
                else {  // Si no pues subimos un nivel y ya
                    node_ptr = last_parent_ptr.top();
                    last_parent_ptr.pop();
                }
            }
            else {  // Si estamos en la raiz es que el recorrido en preorden ha terminado
                node_ptr = nullptr;
            }

            return *this;
        }
    };

    iterator make_child(iterator& _parent) {
        NodeData* parent{_parent.node_ptr};
        NodeData* child{new NodeData()};
        parent->childs.push_back(child);
        child->parents.push_back(parent);
        return {_parent, *child};
    }

    iterator make_child(iterator& _parent, _Tp data) {
        auto it = make_child(_parent);
        *it = data;
        return it;
    }

    void add_parent(iterator& child_it, iterator& parent_it) {
        NodeData* child{child_it.node_ptr};
        NodeData* parent{parent_it.node_ptr};

        if (find_circular_dependency(*child, *parent)) {
            throw std::logic_error("at add_parent: Circular dependency found when adding a parent to a child.");
        }

        child->parents.push_back(parent);
        parent->childs.push_back(child);
    }

    void erase_leaf(iterator leaf) {
        if (!leaf.node_ptr->childs.empty()) {
            throw std::logic_error("at erase_leaf: Tried to erase a node with childs");
        }

        for (auto& p : leaf.node_ptr->parents) {
            auto it = std::find(p->childs.begin(), p->childs.end(), leaf.node_ptr);
            p->childs.erase(it);
        }
    }

    ~RootedDAG() {
        auto prev = begin();
        auto sig = prev;
        ++sig;
        while (prev != end()) {
            delete prev.node_ptr;
            prev = sig;
            ++sig;
        }
    }

    RootedDAG()
    :root{new NodeData()}
    {   }

    RootedDAG(const RootedDAG& r) = delete;     // hard-copy not implemented

    RootedDAG(RootedDAG&& r) {
        std::swap(*this, r);
    }

    RootedDAG(_Tp root_data)
    :root{new NodeData()}
    {
        root->data = root_data;
    }

    inline iterator begin(void) {
        return {*root};
    }

    inline iterator end(void) {
        return {};
    }
};

#endif /* MOSHI3D_ROOTED_DAG_H_ */