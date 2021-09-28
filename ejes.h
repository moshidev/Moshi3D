#ifndef _EJES_H
#define _EJES_H

class Ejes {

  private:
    float axis_size;
    float vertex_array[18];
    float color_array[18];

  public:
    Ejes();
    void changeAxisSize(float new_size);
    void draw();

  private:
    void createArrayData();
};

#endif /* _EJES_H */