// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "_aux.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D {
  public:
    void draw_immediate();

    void draw_buffered();

    /** función que redibuja el objeto
     * está función llama a 'draw_immediate' (modo inmediato)
     * o bien a 'draw_buffered' (modo diferido, VBOs)
     */
    void draw();

    static GLuint create_VBO(GLuint target, GLsizeiptr size, const void* data, GLuint usage=GL_STATIC_DRAW);

  protected:
    void calcular_normales(); // calcula tabla de normales de vértices (práctica 3)

    std::vector<Tupla3f> vertices;
    std::vector<Tupla3u> indices;
  private:
    GLuint vertices_VBO_id {0};
    GLuint indices_VBO_id {0};

  public:
    virtual ~Malla3D() = 0;
    // completar: tabla de colores, tabla de normales de vértices
};

#endif