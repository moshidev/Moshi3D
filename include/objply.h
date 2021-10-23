/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_OBJPLY_H_
#define MOSHI3D_OBJPLY_H_

#include "_aux.h"
#include "ply_reader.h"
#include "mesh.h"

class ObjPLY: public Mesh3D {
public:
    ObjPLY(const std::string& filename);
};

#endif /* MOSHI3D_OBJPLY_H_ */