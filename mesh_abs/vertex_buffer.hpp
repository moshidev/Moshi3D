/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_VERTEX_BUFFER_H_
#define MOSHI3D_VERTEX_BUFFER_H_

#include "vertex_buffer_object.h"
#include <vector>

template<typename _T>
class VertexBuffer {
    VertexBufferObject vbo;
public:
    std::vector<_T> data;

    VertexBuffer() = default;
    VertexBuffer(const std::vector<_T>& v, bool gen_buffer=false)
    : data{v}
    {
        if (gen_buffer) {
            set_vb_data();
        }
    }

    void set_vb_data(void) {
        vbo.set_data(data.size()*sizeof(_T), data.data());
    }

    void set_vb_data(const std::vector<_T>& v) {
        data.clear();
        data.insert(data.begin(), v.begin(), v.end());
        set_vb_data();
    }

    bool usable(void) const {
        return vbo.usable();
    }

    void bind(void) const {
        vbo.bind();
    }

    void unbind(void) const {
        vbo.unbind();
    }
};

#endif /* MOSHI3D_VERTEX_BUFFER_H_ */