#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Select GL version + let the backend select a GLSL version
    const char* glsl_version = nullptr;
#if defined(IMGUI_IMPL_OPENGL_ES2)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(IMGUI_IMPL_OPENGL_ES3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    // Create window with graphics context
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    GLFWwindow* window = glfwCreateWindow((int)(1280 * main_scale), (int)(800 * main_scale), "Wallpaper Window", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);
    style.FontScaleDpi = main_scale;

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Main loop
#ifdef __EMSCRIPTEN__
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(window))
#endif
    {
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame (kept minimal so backend stays happy)
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Destop Wallpaper GUI drawing code ------------------------------------------------------------------
        //Getting the current window size
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);

        //Wallpaper Drawing intialization
        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

        // Main background color for the desktop wallpaper
        draw_list->AddRectFilledMultiColor(
            ImVec2(0, 0),
            ImVec2((float)display_w, (float)display_h),
            IM_COL32(15, 15, 25, 255),   // Top-left
            IM_COL32(30, 15, 40, 255),   // Top-right
            IM_COL32(10, 10, 15, 255),   // Bottom-right
            IM_COL32(20, 10, 30, 255)    // Bottom-left
        );

        // Draw center logo of the desktop wallpaper
        float centerX = (float)display_w / 2.0f;
        float centerY = (float)display_h / 2.0f;

        draw_list->AddTriangleFilled(
            ImVec2(centerX, centerY - 20.0f),         // Top peak
            ImVec2(centerX - 100.0f, centerY + 100.0f), // Bottom-left
            ImVec2(centerX + 100.0f, centerY + 100.0f), // Bottom-right
            IM_COL32(255, 255, 255, 255)    // White
		);

        ImVec2 outerRightPoly[] = {
            ImVec2(centerX, centerY - 120.0f),        // Outer top peak
            ImVec2(centerX, centerY - 80.0f),         // Inner top peak
            ImVec2(centerX + 160.0f, centerY + 100.0f), // Bottom-right outer
            ImVec2(centerX + 100.0f, centerY + 100.0f)  // Bottom-right inner
        };

        ImVec2 outerLeftPoly[] = {
            ImVec2(centerX - 160.0f, centerY + 100.0f), // Bottom-left outer
            ImVec2(centerX - 100.0f, centerY + 100.0f), // Bottom-left inner
            ImVec2(centerX, centerY - 80.0f),         // Inner top peak
            ImVec2(centerX, centerY - 120.0f)         // Outer top peak
        };
        draw_list->AddConvexPolyFilled(outerLeftPoly, 4, IM_COL32(100, 200, 255, 255)); // Light Blue
        // ---------------------------------------------------------------------------------------------------
		

        // Rendering
        ImGui::Render();
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        
        // Background color (Change these numbers to change background color)
        glClearColor(0.1f, 0.12f, 0.18f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}