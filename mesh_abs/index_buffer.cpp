#include "index_buffer.h"

IndexBuffer::IndexBuffer(const std::vector<Tupla3u>& v, bool gen_buffer)
: data{v}
{
    if (gen_buffer) {
        set_ib_data();
    }
}

void IndexBuffer::set_ib_data(void) {
    ibo.set_indices(data.size()*3, data.data());
}

void IndexBuffer::set_ib_data(const std::vector<Tupla3u>& v) {
    data.clear();
    data.insert(data.begin(), v.begin(), v.end());
    set_ib_data();
}