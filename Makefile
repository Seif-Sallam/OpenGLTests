CC = g++
CCFLAGS = $(INC) -std=c++17
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
GLM_INC = ./Thirdparty/glm/
KHR_INC = ./Thirdparty/KHR/
STB_IMAGE = ./Thirdparty/stbimage/
INC = -I$(GLAD_INC) 
INC += -I$(GLFW_INC)
INC += -I$(IMGUI_INC)
INC += -I$(GLM_INC)
INC += -I$(KHR_INC)
INC += -I$(STB_IMAGE)
OBJ_DIR = ./Objs/
IMGUI_OBJS = ./Thirdparty/imgui/imgui/objs/ 
IMGUI_OBJ = $(subst $(IMGUI_DIR), $(OBJ_DIR), $(patsubst %.cpp, %.o, $(wildcard $(IMGUI_DIR)*.cpp)))
OBJS= $(subst $(SRC_DIR), $(OBJ_DIR), $(patsubst %.cpp, %.o, $(SRCS)))
ADDITIONAL_OBJS = $(OBJ_DIR)glad.o $(OBJ_DIR)stbimage.o
LIBS_FLAGS = -L$(GLFW_LIBS_DIR) -L$(IMGUI_LIBS_DIR)
GLFW_DIR = ./Thirdparty/glfw/include/

all: CreateImGui $(OBJS) $(ADDITIONAL_OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(ADDITIONAL_OBJS) -o $(PROGRAM_NAME) $(LIBS_FLAGS) $(LIBS)


$(OBJS): $(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	$(CC) $(CCFLAGS) -c $< -o $@ $(LIBS_FLAGS) $(LIBS)


$(ADDITIONAL_OBJS):
	echo ' '

$(OBJ_DIR)glad.o: 
	$(CC) $(CCFLAGS) -c $(GLAD_DIR)glad.c -o $(OBJ_DIR)glad.o $(LIBS_FLAGS) $(LIBS)

$(OBJ_DIR)stbimage.o:
	$(CC) $(CCFLAGS) -c $(STB_IMAGE)stbimage/stb_image.cpp -o $(OBJ_DIR)stbimage.o $(LIBS_FLAGS) $(LIBS)
	
include ./Thirdparty/imgui/imgui/Makefile 

CreateImGui:
	$(MAKE) CreateLib


clean:
	$(RM) $(OBJS)