#include "window.h"

const char* window_title = "GLFW Starter Project";
Cube * cube;
BezierPatch* patch;
GLint shaderProgram;
GLint gridShaderProgram;
GLint buildingShader;
bool pressedLeft = false;
bool releasedLeft = false;
bool pressedRight = false;
bool releasedRight = false;
double LastX = 0.0;
double LastY = 0.0;
bool start = true;

// On some systems you need to change this to the absolute path
#define VERTEX_SHADER_PATH "/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/shader.vert"
#define FRAGMENT_SHADER_PATH "/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/shader.frag"
#define GRID_VERTEX_SHADER_PATH "/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/gridShader.vert"
#define GRID_FRAGMENT_SHADER_PATH "/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/gridShader.frag"
#define BUILDING_VERTEX_SHADER_PATH "/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/buildingShader.vert"
#define BUILDING_FRAGMENT_SHADER_PATH "/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/buildingShader.frag"
// Default camera parameters
glm::vec3 cam_pos(0.0f, 10.0f, 20.0f);		// e  | Position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

int Window::width;
int Window::height;
std::vector<Building*> buildings;

glm::mat4 Window::P;
glm::mat4 Window::V;

void Window::initialize_objects()
{
	cube = new Cube();
    patch = new BezierPatch();
    
	// Load the shader program. Make sure you have the correct filepath up top
	shaderProgram = LoadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    gridShaderProgram = LoadShaders(GRID_VERTEX_SHADER_PATH, GRID_FRAGMENT_SHADER_PATH);
    buildingShader = LoadShaders(BUILDING_VERTEX_SHADER_PATH, BUILDING_FRAGMENT_SHADER_PATH);
} 

// Treat this as a destructor function. Delete dynamically allocated memory here.
void Window::clean_up()
{
	delete(cube);
    delete(patch);
    for(auto it= buildings.begin(); it!=buildings.end(); ++it)
        delete *it;
	glDeleteProgram(shaderProgram);
    glDeleteProgram(gridShaderProgram);
    glDeleteProgram(buildingShader);
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ // Because Apple hates comforming to standards
	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		fprintf(stderr, "Either GLFW is not installed or your graphics card does not support modern OpenGL.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Get the width and height of the framebuffer to properly resize the window
	glfwGetFramebufferSize(window, &width, &height);
	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
	Window::width = width;
	Window::height = height;
	// Set the viewport size. This is the only matrix that OpenGL maintains for us in modern OpenGL!
	glViewport(0, 0, width, height);

	if (height > 0)
	{
		P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
		V = glm::lookAt(cam_pos, cam_look_at, cam_up);
	}
}

void Window::idle_callback()
{
	// Call the update function the cube
	//cube->update();
}
 
void Window::display_callback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use the shader of programID
	glUseProgram(shaderProgram);
	
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &Window::P[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelview"), 1, GL_FALSE, &Window::V[0][0]);
    
	// Render the cube
	cube->Draw(shaderProgram);
    
    // Use the shader of programID
    glUseProgram(gridShaderProgram);
    
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &Window::P[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelview"), 1, GL_FALSE, &Window::V[0][0]);
    
    patch->Draw(gridShaderProgram);
    
    glUseProgram(buildingShader);
    
    
    if(start){
        srand (time(NULL));
        for(int i = 0; i < patch->curveVertices.size(); i++)
        {
            int length = rand() % 1 + 1;
            int width = rand() % 1 + 1;
            int height = rand() % 10 + 1;
            
            int x = rand() % 20 + 1;
            int y = 0;
            int z = rand() % 20 + 1;
            
            buildings.push_back(new Building(length, height, width, patch->curveVertices[i+1]));
        }
        start = false;
    }//end start
    
    glUniformMatrix4fv(glGetUniformLocation(buildingShader, "projection"), 1, GL_FALSE, &Window::P[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(buildingShader, "modelview"), 1, GL_FALSE, &Window::V[0][0]);
    
    for(auto building = buildings.begin(); building != buildings.end(); ++building)
        (*building)->draw(buildingShader);

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press
	if (action == GLFW_PRESS)
	{
		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
        else if(key == GLFW_KEY_S){
            if(mods == 1){
                cam_pos = cam_pos * 1.3f;
                V = glm::lookAt(cam_pos, cam_look_at, cam_up);
            }//end if
            else{
                cam_pos = cam_pos * .75f;
                V = glm::lookAt(cam_pos, cam_look_at, cam_up);
            }
        }//end else if
	}
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    if (button == GLFW_MOUSE_BUTTON_LEFT){
        if(action == GLFW_PRESS){
            glfwGetCursorPos(window, &xpos, &ypos);
            LastX = xpos;
            LastY = ypos;
            pressedLeft = true;
            releasedLeft = false;
        }//end if
        if(action == GLFW_RELEASE){
            releasedLeft = true;
            pressedLeft =false;
        }//end if
    }//end if
    if (button == GLFW_MOUSE_BUTTON_RIGHT){
        if(action == GLFW_PRESS){
            //Do something
            pressedRight = true;
            releasedRight = false;
        }//end if
        if(action == GLFW_RELEASE){
            releasedRight = true;
            pressedRight =false;
            LastX = xpos;
            LastY = ypos;
        }//end if
    }//end if
}

void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(pressedLeft & !releasedLeft){
        float angle;
        // Perform horizontal (y-axis) rotation
        angle = (float) (LastX - xpos) / 100.0f;
        cam_pos = glm::vec3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(cam_pos, 1.0f));
        cam_up = glm::vec3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(cam_up, 1.0f));
        //Now rotate vertically based on current orientation
        angle = (float) (ypos - LastY) / 100.0f;
        glm::vec3 axis = glm::cross((cam_pos - cam_look_at), cam_up);
        cam_pos = glm::vec3(glm::rotate(glm::mat4(1.0f), angle, axis) * glm::vec4(cam_pos, 1.0f));
        cam_up = glm::vec3(glm::rotate(glm::mat4(1.0f), angle, axis) * glm::vec4(cam_up, 1.0f));
        // Now update the camera
        V = glm::lookAt(cam_pos, cam_look_at, cam_up);
        LastX = xpos;
        LastY = ypos;
        
        // }//end if
    }//end if
    if(pressedRight & !releasedRight){
        //Do something while Right Is pressed
    }//end if
}

