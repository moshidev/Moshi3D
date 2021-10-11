#include "ejes.h"
#include "_aux.h"

// -----------------------------------------------------------------------------

Ejes::Ejes()
{
    axis_size = 1000;
    createArrayData();
}
// -----------------------------------------------------------------------------

void Ejes::changeAxisSize(float newSize)
{
    axis_size = newSize;
    createArrayData();
}
// -----------------------------------------------------------------------------

void Ejes::createArrayData()
{
    // clang-format off
	color_array[0] = 1; color_array[1] = 0; color_array[2] = 0;
	color_array[3] = 1; color_array[4] = 0; color_array[5] = 0;
	color_array[6] = 0; color_array[7] = 1; color_array[8] = 0;
	color_array[9] = 0; color_array[10] = 1; color_array[11] = 0;
	color_array[12] = 0; color_array[13] = 0; color_array[14] = 1;
	color_array[15] = 0; color_array[16] = 0; color_array[17] = 1;

	vertex_array[0] = -axis_size; vertex_array[1] = 0; vertex_array[2] = 0;
	vertex_array[3] = axis_size; vertex_array[4] = 0; vertex_array[5] = 0;
	vertex_array[6] = 0; vertex_array[7] = -axis_size; vertex_array[8] = 0;
	vertex_array[9] = 0; vertex_array[10] = axis_size; vertex_array[11] = 0;
	vertex_array[12] = 0; vertex_array[13] = 0; vertex_array[14] = -axis_size;
	vertex_array[15] = 0; vertex_array[16] = 0; vertex_array[17] = axis_size;
    // clang-format on
}

void Ejes::draw()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex_array);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, color_array);
    glDrawArrays(GL_LINES, 0, 6);
}