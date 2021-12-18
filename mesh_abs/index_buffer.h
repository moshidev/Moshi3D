/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_INDEX_BUFFER_H_
#define MOSHI3D_INDEX_BUFFER_H_

#include "index_buffer_object.h"
#include "tuplasg.h"
#include <vector>

class IndexBuffer {
    IndexBufferObject ibo;
public:
    std::vector<Tupla3u> data;

    IndexBuffer() = default;
    IndexBuffer(const std::vector<Tupla3u>& v, bool gen_buffer=false);

    void set_ib_data(void);
    void set_ib_data(const std::vector<Tupla3u>& v);

    inline bool usable(void) const { return ibo.usable(); }
    inline void bind(void) const { ibo.bind(); }
    inline void unbind(void) const { ibo.unbind(); }
    inline unsigned get_num_indices(void) const { return ibo.get_num_indices(); }
};

#endif /* MOSHI3D_INDEX_BUFFER_DATA_H_ */