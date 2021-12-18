/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "objply.h"
#include "file_io/ply_reader.h"

ObjPLY::ObjPLY(const std::string& nombre_archivo)
{
   ply::read(nombre_archivo, vertices.data, indices.data);
   init_color(vertices.data.size());
   init_normal_vectors();
}