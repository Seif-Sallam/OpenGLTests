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
IMGUI_DIR = ./Thirdparty/imgui/imgui/
IMGUI_INC = ./Thirdparty/imgui/
INC = -I$(GLAD_INC) 
INC += -I$(GLFW_INC)
INC += -I$(IMGUI_INC)
OBJ_DIR = ./Objs/
IMGUI_OBJS = ./Thirdparty/imgui/imgui/objs/ 
IMGUI_OBJ = $(subst $(IMGUI_DIR), $(OBJ_DIR), $(patsubst %.cpp, %.o, $(wildcard $(IMGUI_DIR)*.cpp)))
OBJS= $(subst $(SRC_DIR), $(OBJ_DIR), $(patsubst %.cpp, %.o, $(SRCS)))
LIBS_FLAGS = -L$(GLFW_LIBS_DIR) -L$(IMGUI_LIBS_DIR)
GLFW_DIR = ./Thirdparty/glfw/include/
all: CreateImGui $(OBJS) $(OBJ_DIR)glad.o
	$(CC) $(CCFLAGS) $(OBJS) $(OBJ_DIR)glad.o -o $(PROGRAM_NAME) $(LIBS_FLAGS) $(LIBS)


$(OBJS): $(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	$(CC) $(CCFLAGS) -c $< -o $@ $(LIBS_FLAGS) $(LIBS)

$(OBJ_DIR)glad.o: 
	$(CC) $(CCFLAGS) -c $(GLAD_DIR)glad.c -o $(OBJ_DIR)glad.o $(LIBS_FLAGS) $(LIBS)

include ./Thirdparty/imgui/imgui/Makefile 

CreateImGui:
	$(MAKE) CreateLib