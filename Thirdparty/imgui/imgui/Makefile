#This is the one that makes these imgui objects
IMGUI_DIR = Thirdparty/imgui/imgui/
IMGUI_OBJS = $(subst $(IMGUI_DIR), $(IMGUI_DIR)obj/, $(patsubst %.cpp, %.o, $(wildcard $(IMGUI_DIR)*.cpp)))
IMGUI_SRC = $(wildcard $(IMGUI_DIR)*.cpp)
GLFW_DIR = ./Thirdparty/glfw/include/
IMGUI: | CreateLib

$(IMGUI_OBJS): $(IMGUI_DIR)obj/%.o : ./$(IMGUI_DIR)%.cpp
	g++ -c -I$(GLFW_DIR) $< -o $@

CreateLib: $(IMGUI_OBJS)
	ar rvs $(IMGUI_DIR)/lib/libimgui.so $(IMGUI_OBJS)


print:
	for obj in $(IMGUI_SRC); do\
		echo $$obj;\
	done
