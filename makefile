# ##############################################################################
#
# Informática Gráfica (Grado Informática)
# Makefile (sirve para Linux y macOS)
#
# ##############################################################################

.SUFFIXES:
.PHONY: x

exe             := pracs_exe
obj				:= obj
units_cc        := $(wildcard *.cpp) $(wildcard renderers/*.cpp) $(wildcard primitives/*.cpp) $(wildcard gl_abs/*.cpp) $(wildcard mesh_abs/*.cpp) $(wildcard file_io/*.cpp) $(wildcard escena/*.cpp)
units_o         := $(addprefix $(obj)/, $(addsuffix .o, $(basename $(units_cc))))
headers         := $(wildcard *.h*) $(wildcard include/*.h*)
uname           := $(shell uname -s)
en_macos        := $(findstring Darwin,$(uname))
en_linux        := $(findstring Linux,$(uname))
compiler        := $(if $(en_linux), g++, clang++ )
sistoper        := $(if $(en_macos), macOS, Linux )

cc_flags_common := -std=c++17 -Wall -g -I/usr/include -I. -I./include -I./primitives -I./gl_abs -I./mesh_abs -I./renderers -I./escena
cc_flags_linux  := -DLINUX
cc_flags_macos  := -DMACOS
cc_flags        := $(cc_flags_common) $(if $(en_linux), $(cc_flags_linux), $(cc_flags_macos))

ld_libs_common := -ljpeg
ld_libs_linux  := -lGLEW -lGLU -lglut -lGL
ld_libs_macos  := -framework OpenGL -framework GLUT
ld_libs        := $(ld_libs_common) $(if $(en_linux), $(ld_libs_linux), $(ld_libs_macos))


x: $(exe)
	@echo Enlazando para: $(sistoper)
	./$(exe)

$(exe): $(units_o) makefile
	$(compiler) -o $(exe) $(addprefix $(obj)/, $(notdir $(units_o))) $(ld_libs)

$(obj)/%.o : %.cc
	$(compiler) -c -o $(obj)/$(notdir $@) $(cc_flags) $<

$(obj)/%.o : %.cpp
	$(compiler) -c -o $(obj)/$(notdir $@) $(cc_flags) $<

$(units_cc) : $(headers)
	touch $(units_cc)

configure:
	@mkdir -p obj

clean:
	rm -f $(obj)/*.o *_exe
