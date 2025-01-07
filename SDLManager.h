#ifndef SDLMANAGER_H
#define SDLMANAGER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_opengl.h> 
// #include <GLES2/gl2.h>
// #include <EGL/egl.h>
#include <glad/glad.h>
#include <iostream>
using namespace std;

enum class SCREENSIZE{
    is640x480,
    is1280x720,
    fullscreen
};

class SDLManager{
    public:
         SDLManager();
         ~SDLManager();
         SDL_Event pollEvent();
         void resize(int width, int height);
         void drawCard(card thisCard, int n);
         void update();
         void getOpenGLInfo();
         void VertexSpecification();
         void createGraphicsPipeline();
         GLuint createShader(const string &vertexShader, const string &fragmentShader);
         GLuint compileShader(GLuint type, const string &source);
         void pDraw();
         void draw();
    private:
        SDL_Renderer* renderer;
        SDL_Window *window;
        SDL_Texture *background;
        SDL_GLContext context;
        vector<SDL_Texture *> cardTextures;
        int win_width;
        int win_height;
        SCREENSIZE curr_screen_size;
        SCREENSIZE last_non_fullscreen_size;
        GLuint vertexArrayObject = 0;
        GLuint vertexBufferObject = 0;
        //program object for shaders
        GLuint graphicsPipelineShader = 0;

        const string vertexShaderSource = "#version 410 core\n"
                                          "in vec4 position;\n"
                                          "void main()\n"
                                          "{\n"
                                          " gl_Position = vec4(position.x, position.y, position.z, position.w);\n"
                                          "}\n";
        const string fragmentShaderSource = "#version 410 core\n"
                                          "out vec4 color;\n"
                                          "void main()\n"
                                          "{\n"
                                          " color = vec4(1.0f, 0.5f, 0.0f, 1.0f);\n"
                                          "}\n"; 



};

#endif

// typedef enum SDL_WindowFlags
// {
//     SDL_WINDOW_FULLSCREEN = 0x00000001,         /**< fullscreen window */
//     SDL_WINDOW_OPENGL = 0x00000002,             /**< window usable with OpenGL context */
//     SDL_WINDOW_SHOWN = 0x00000004,              /**< window is visible */
//     SDL_WINDOW_HIDDEN = 0x00000008,             /**< window is not visible */
//     SDL_WINDOW_BORDERLESS = 0x00000010,         /**< no window decoration */
//     SDL_WINDOW_RESIZABLE = 0x00000020,          /**< window can be resized */
//     SDL_WINDOW_MINIMIZED = 0x00000040,          /**< window is minimized */
//     SDL_WINDOW_MAXIMIZED = 0x00000080,          /**< window is maximized */
//     SDL_WINDOW_MOUSE_GRABBED = 0x00000100,      /**< window has grabbed mouse input */
//     SDL_WINDOW_INPUT_FOCUS = 0x00000200,        /**< window has input focus */
//     SDL_WINDOW_MOUSE_FOCUS = 0x00000400,        /**< window has mouse focus */
//     SDL_WINDOW_FULLSCREEN_DESKTOP = ( SDL_WINDOW_FULLSCREEN | 0x00001000 ),
//     SDL_WINDOW_FOREIGN = 0x00000800,            /**< window not created by SDL */
//     SDL_WINDOW_ALLOW_HIGHDPI = 0x00002000,      /**< window should be created in high-DPI mode if supported.
//                                                      On macOS NSHighResolutionCapable must be set true in the
//                                                      application's Info.plist for this to have any effect. */
//     SDL_WINDOW_MOUSE_CAPTURE    = 0x00004000,   /**< window has mouse captured (unrelated to MOUSE_GRABBED) */
//     SDL_WINDOW_ALWAYS_ON_TOP    = 0x00008000,   /**< window should always be above others */
//     SDL_WINDOW_SKIP_TASKBAR     = 0x00010000,   /**< window should not be added to the taskbar */
//     SDL_WINDOW_UTILITY          = 0x00020000,   /**< window should be treated as a utility window */
//     SDL_WINDOW_TOOLTIP          = 0x00040000,   /**< window should be treated as a tooltip */
//     SDL_WINDOW_POPUP_MENU       = 0x00080000,   /**< window should be treated as a popup menu */
//     SDL_WINDOW_KEYBOARD_GRABBED = 0x00100000,   /**< window has grabbed keyboard input */
//     SDL_WINDOW_VULKAN           = 0x10000000,   /**< window usable for Vulkan surface */
//     SDL_WINDOW_METAL            = 0x20000000,   /**< window usable for Metal view */

//     SDL_WINDOW_INPUT_GRABBED = SDL_WINDOW_MOUSE_GRABBED /**< equivalent to SDL_WINDOW_MOUSE_GRABBED for compatibility */
// } SDL_WindowFlags;