#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "graphics/IndexBuffer/IndexBuffer.h"
#include "graphics/VertexBuffer/VertexBuffer.h"
#include "graphics/VertexBufferLayout/VertexBufferLayout.h"
#include "graphics/VertexArray/VertexArray.h"
#include "graphics/Shader/Shader.h"
#include "graphics/Renderer/Renderer.h"
#include "graphics/Texture/Texture.h"
#include "tests/TestClearColor.h"



const unsigned int SCR_WIDTH = 1400;
const unsigned int SCR_HEIGHT = 960;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

    glViewport(0, 0, width, height);
}

glm::vec3 cameraPos = glm::vec3(
    -0.347205f,
    4.42031f,
    4.11971f
);

glm::vec3 cameraFront = glm::vec3(
    0.380422f,
    -0.683273f,
    -0.623231f
);

glm::vec3 cameraUp = glm::vec3(
    0.0f,
    1.0f,
    0.0f
);

float cameraSpeed = 3.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
float sensitivity = 0.1f;

float yaw = -90.0f;
float pitch = 0.0f;

float lastX = 480.0f;
float lastY = 270.0f;

float cubeRotX = 0.0f;
float cubeRotY = 0.0f;

bool mousePressed = false;

double lastMouseX = 0;
double lastMouseY = 0;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        mousePressed = (action == GLFW_PRESS);
    }
}

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (!mousePressed)
    {
        lastMouseX = xpos;
        lastMouseY = ypos;
        return;
    }

    float xoffset = xpos - lastMouseX;
    float yoffset = ypos - lastMouseY;

    lastMouseX = xpos;
    lastMouseY = ypos;

    float sensitivity = 0.3f;

    cubeRotY += xoffset * sensitivity;
    cubeRotX += yoffset * sensitivity;
}


struct Cubelet
{
    glm::vec3 position;
    glm::mat4 rotation;
};

glm::vec3 GetCurrentPos(const Cubelet& c)
{
    glm::vec4 p = c.rotation * glm::vec4(c.position, 1.0f);
    return glm::vec3(p);
}

int main()
{
    //I Am Laugh Under The Weeping Moon
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cube", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }


    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetCursorPosCallback(window, mouse_move_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);




    glfwSwapInterval(3);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }



    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float vertices[] =
    {
        // ================= BLACK CUBE =================

        // Back
        -0.5f,-0.5f,-0.5f,  0,0,0,
         0.5f,-0.5f,-0.5f,  0,0,0,
         0.5f, 0.5f,-0.5f,  0,0,0,
        -0.5f, 0.5f,-0.5f,  0,0,0,

        // Front
        -0.5f,-0.5f,0.5f,   0,0,0,
         0.5f,-0.5f,0.5f,   0,0,0,
         0.5f,0.5f,0.5f,    0,0,0,
        -0.5f,0.5f,0.5f,    0,0,0,

        // Left
        -0.5f,-0.5f,-0.5f,  0,0,0,
        -0.5f,0.5f,-0.5f,   0,0,0,
        -0.5f,0.5f,0.5f,    0,0,0,
        -0.5f,-0.5f,0.5f,   0,0,0,


        // Right
         0.5f,-0.5f,-0.5f,  0,0,0,
         0.5f,0.5f,-0.5f,   0,0,0,
         0.5f,0.5f,0.5f,    0,0,0,
         0.5f,-0.5f,0.5f,   0,0,0,


         // Top black
         -0.5f,0.5f,-0.5f,   0,0,0,
          0.5f,0.5f,-0.5f,   0,0,0,
          0.5f,0.5f,0.5f,    0,0,0,
         -0.5f,0.5f,0.5f,    0,0,0,


         // Bottom black
         -0.5f,-0.5f,-0.5f,  0,0,0,
          0.5f,-0.5f,-0.5f,  0,0,0,
          0.5f,-0.5f,0.5f,   0,0,0,
         -0.5f,-0.5f,0.5f,   0,0,0,


         // ================= STICKERS =================


         // Front Green
         -0.40f,-0.40f,0.501f,  0,1,0,
          0.40f,-0.40f,0.501f,  0,1,0,
          0.40f,0.40f,0.501f,   0,1,0,
         -0.40f,0.40f,0.501f,   0,1,0,


         // Back Blue
         -0.40f,-0.40f,-0.501f, 0,0,1,
          0.40f,-0.40f,-0.501f, 0,0,1,
          0.40f,0.40f,-0.501f,  0,0,1,
         -0.40f,0.40f,-0.501f,  0,0,1,


         // Right Red
          0.501f,-0.40f,-0.40f, 1,0,0,
          0.501f,0.40f,-0.40f,  1,0,0,
          0.501f,0.40f,0.40f,   1,0,0,
          0.501f,-0.40f,0.40f,  1,0,0,


          // Left Orange
          -0.501f,-0.40f,-0.40f, 1,0.5f,0,
          -0.501f,0.40f,-0.40f,  1,0.5f,0,
          -0.501f,0.40f,0.40f,   1,0.5f,0,
          -0.501f,-0.40f,0.40f,  1,0.5f,0,


          // Top White
          -0.40f,0.501f,-0.40f, 1,1,1,
           0.40f,0.501f,-0.40f, 1,1,1,
           0.40f,0.501f,0.40f,  1,1,1,
          -0.40f,0.501f,0.40f,  1,1,1,


          // Bottom Yellow
          -0.40f,-0.501f,-0.40f, 1,1,0,
           0.40f,-0.501f,-0.40f, 1,1,0,
           0.40f,-0.501f,0.40f,  1,1,0,
          -0.40f,-0.501f,0.40f,  1,1,0
    };

    unsigned int indices[] =
    {
        // Black cube
        0,1,2, 2,3,0,
        4,5,6, 6,7,4,
        8,9,10, 10,11,8,
        12,13,14,14,15,12,
        16,17,18,18,19,16,
        20,21,22,22,23,20,


        // Stickers
        24,25,26,26,27,24, // Green
        28,29,30,30,31,28, // Blue
        32,33,34,34,35,32, // Red
        36,37,38,38,39,36, // Orange
        40,41,42,42,43,40, // White
        44,45,46,46,47,44  // Yellow
    };

    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    VertexBufferLayout layout;

    layout.Push<float>(3);
    layout.Push<float>(3);

    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 72);
    Shader shader("shaders/basic.shader");

    glm::mat4 proj = glm::perspective(
        glm::radians(45.0f),
        (float)SCR_WIDTH / SCR_HEIGHT,
        0.1f,
        100.0f
    );

    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-3, 0, -3));
    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 mvp = proj * view * model;

    shader.Bind();
    shader.SetUniformMath4f("u_MVP", mvp);

    Renderer renderer;

  
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);


    float rotateX = 1.0f;
    float rotateY = 1.0f;
    float rotateZ = 1.0f;
    bool rend = true;

    ImGui::CreateContext();
    ImGui::StyleColorsDark();


    ImGui_ImplGlfwGL3_Init(window, false);
    


    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


    float topRotation = 0.0f;
    float bottomRotation = 0.0f;

    float leftRotation = 0.0f;
    float rightRotation = 0.0f;

    float frontRotation = 0.0f;
    float backRotation = 0.0f;

    bool rotating = false;


    std::vector<Cubelet> cubes;


    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            for (int z = -1; z <= 1; z++)
            {
                Cubelet c;

                c.position = glm::vec3(
                    x * 0.5f,
                    y * 0.5f,
                    z * 0.5f
                );

                c.rotation = glm::mat4(1.0f);

                cubes.push_back(c);
            }
        }
    }

    bool rotation = false;
    float rotate = 10.0f;
    float time = 0.0f;
    std::string roatationType = "";
    while (!glfwWindowShouldClose(window)) {

        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        float speed = cameraSpeed * deltaTime;


        // WASD movement

        //if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        //    cameraPos += speed * cameraFront;

        //if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        //    cameraPos -= speed * cameraFront;

        //if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        //    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;

        //if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        //    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;



        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

        renderer.Clear();
        
        ImGui_ImplGlfwGL3_NewFrame();


        ImGui::Begin("Cube Controls");

        if (ImGui::Button("Top"))
        {
            rotation = true;
            roatationType = "Top";
        }

        if (ImGui::Button("Bottom"))
        {
            rotation = true;
            roatationType = "Bottom";
        }

        if (ImGui::Button("Left"))
        {
            rotation = true;
            roatationType = "Left";
        }

        if (ImGui::Button("Right"))
        {
            rotation = true;
            roatationType = "Right";
        }

        if (ImGui::Button("Front"))
        {
            rotation = true;
            roatationType = "Front";
        }

        if (ImGui::Button("Back"))
        {
            rotation = true;
            roatationType = "Back";
        }

        ImGui::End();

        glm::mat4 cubeRotation = glm::mat4(1.0f);

        cubeRotation = glm::rotate(
            cubeRotation,
            glm::radians(cubeRotX),
            glm::vec3(1, 0, 0)
        );


        cubeRotation = glm::rotate(
            cubeRotation,
            glm::radians(cubeRotY),
            glm::vec3(0, 1, 0)
        );

        if (rotation) {

            if (roatationType == "Top") {
                glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(rotate), glm::vec3(0, 1, 0));

                for (auto& c : cubes)
                {
                    glm::vec3 p = GetCurrentPos(c);
                    if (p.y > 0.4f)
                        c.rotation = r * c.rotation;
                }
            }

            if (roatationType == "Bottom") {
                glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(rotate), glm::vec3(0, 1, 0));

                for (auto& c : cubes)
                {
                    glm::vec3 p = GetCurrentPos(c);
                    if (p.y < -0.4f)
                        c.rotation = r * c.rotation;
                }
            }

            if (roatationType == "Left") {
                glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(rotate), glm::vec3(1, 0, 0));

                for (auto& c : cubes)
                {
                    glm::vec3 p = GetCurrentPos(c);
                    if (p.x < -0.4f)
                        c.rotation = r * c.rotation;
                }
            }

            if (roatationType == "Right") {
                glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(rotate), glm::vec3(1, 0, 0));

                for (auto& c : cubes)
                {
                    glm::vec3 p = GetCurrentPos(c);
                    if (p.x > 0.4f)
                        c.rotation = r * c.rotation;
                }
            }

            if (roatationType == "Front") {
                glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(rotate), glm::vec3(0, 0, 1));

                for (auto& c : cubes)
                {
                    glm::vec3 p = GetCurrentPos(c);
                    if (p.z > 0.4f)
                        c.rotation = r * c.rotation;
                }
            }
            
            if (roatationType == "Back") {
                glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(rotate), glm::vec3(0, 0, 1));

                for (auto& c : cubes)
                {
                    glm::vec3 p = GetCurrentPos(c);
                    if (p.z < -0.4f)
                        c.rotation = r * c.rotation;
                }
            }

            time += rotate;
        }



        for (auto& c : cubes) {

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, c.position);
            model = c.rotation * model;
            model = glm::scale(model, glm::vec3(0.5f));


            model = cubeRotation * model;

            glm::mat4 view = glm::lookAt(cameraPos, glm::vec3(0, 0, 0), cameraUp);
            glm::mat4 mvp = proj * view * model;


            shader.Bind();
            shader.SetUniformMath4f("u_MVP", mvp);


            va.Bind();
            ib.Bind();

            renderer.Draw(va, ib, shader);
        }
       
        if (time >= 90.0f) {
            rotation = false;
            time = 0;
            roatationType = "";
        }


        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}