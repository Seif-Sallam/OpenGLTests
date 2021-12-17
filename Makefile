
CC = g++
CCFLAGS = $(INC)
PROGRAM_NAME = opengl
LIBS = -lGL -lglfw3 -lGLU -pthread -ldl -lrt -lXi -limgui
GLFW_LIBS_DIR = ./Thirdparty/glfw/
IMGUI_LIBS_DIR = ./Thirdparty/imgui/imgui/lib/
GLAD_DIR = ./Thirdparty/glad/
GLAD_INC = ./Thirdparty/glad/
GLFW_INC = ./Thirdparty/glfw/include/
SRC_DIR = ./src/
SRCS = $(wildcard $(SRC_DIR)*.cpp)
SRCS += $(GLAD_DIR)glad.c
IMGUI_DIR = ./Thirdparty/imgui/imgui/
IMGUI_INC = ./Thirdparty/imgui/
INC = -I$(GLAD_INC) 
INC += -I$(GLFW_INC)
INC += -I$(IMGUI_INC)
OBJ_DIR = ./Objs/
IMGUI_OBJS = ./Thirdparty/imgui/imgui/objs/ 
IMGUI_OBJ = $(subst $(IMGUI_DIR), $(OBJ_DIR), $(patsubst %.cpp, %.o, $(wildcard $(IMGUI_DIR)*.cpp)))
LIBS_FLAGS = -L$(GLFW_LIBS_DIR) -L$(IMGUI_LIBS_DIR)
GLFW_DIR = ./Thirdparty/glfw/include/
all: CreateImGui
	$(CC) $(CCFLAGS) $(SRCS) -o $(PROGRAM_NAME) $(LIBS_FLAGS) $(LIBS)


include ./Thirdparty/imgui/imgui/Makefile 

CreateImGui:
	$(MAKE) CreateLib