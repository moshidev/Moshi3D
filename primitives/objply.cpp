/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "objply.h"
#include "ply_reader.h"

ObjPLY::ObjPLY(const std::string& nombre_archivo)
{
   ply::read(nombre_archivo, vertices, indices);
   init_color(vertices.size());
}


