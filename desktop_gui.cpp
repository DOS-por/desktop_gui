// IMGUI LIBRARIES: imgui, imgui_impl_glfw, imgui_impl_opengl3
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <fstream>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>

// TIME LIBRARIES
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

static std::string ReadFileToString(const char* path)
{
    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    if (!ifs) return std::string();
    std::ostringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
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

    // UI state for taskbar buttons/windows
    static bool showApp1 = false;
    static bool showApp2 = false;
    static bool showTaskManager = false;
    // App-specific UI state
    static int app1_selected_index = 0; // selected file/folder in File Manager
    static const char* app1_items[] = { "Documents", "Pictures", "Music", "Videos", "Downloads", "Homework", "notes.txt", "todo.md" };
    static int app1_items_count = IM_ARRAYSIZE(app1_items);
    static char app2_address[256] = "https://bee_movie_script.com"; // fake browser address bar
    static int app2_history_index = 0;
    // bee movie script file load
    static std::string gist_content = ReadFileToString("bee_movie_script.txt");

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
            IM_COL32(25, 40, 75, 255),   // Top-left 
            IM_COL32(35, 55, 95, 255),   // Top-right 
            IM_COL32(15, 25, 45, 255),   // Bottom-right
            IM_COL32(20, 32, 60, 255)    // Bottom-left 
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
		
        // REAL TIME CLOCK DISPLAY -------------------------------------------------------

        // Time formatting and Getting
        time_t now = time(nullptr);
		tm localTime_s;
		localtime_s(&localTime_s, &now);    

		char timeBuffer[128]; // HH:MM:SS
		strftime(timeBuffer, sizeof(timeBuffer), "%b %d, %Y | %I:%M:%S %p", &localTime_s);

		// Displaying Real Time Clock on the desktop wallpaper
		ImGui::SetNextWindowPos(ImVec2((float)display_w / 2.0f + 600.0f, 10.0f), ImGuiCond_Always);
		ImGui::Begin("Real Time Clock", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove);
		
		ImGui::SetWindowFontScale(1.5f); // Set font scale for the clock display
		ImGui::SetCursorPosX(1.0f); // Align text to the center of the window  
                
        ImGui::Text("%s", timeBuffer);
		ImGui::End();

        //--------------------------------------------------------------------------------


		//TASK BAR -----------------------------------------------------------------------
		float taskBarHeight = 65.0f;
		float taskBarY = (float)display_h - taskBarHeight;

        //Task Bar container
        draw_list->AddRectFilled(
            ImVec2(0, taskBarY),
            ImVec2((float)display_w, (float)display_h),
            IM_COL32(0, 0, 0, 255) // Darker background for the taskbar
		);

		ImGui::SetNextWindowPos(ImVec2(0, taskBarY), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2((float)display_w, taskBarHeight), ImGuiCond_Always);

		ImGuiWindowFlags taskBarFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(255, 255, 255, 255)); // Darker background for the taskbar
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f); // No rounding for the taskbar

		ImGui::Begin("Task Bar", nullptr, taskBarFlags);

        // Left-side quick-launch buttons (3 buttons)
        float quickButtonSize = 40.0f;
        float left_margin = 20.0f;
        float spacing = 10.0f;

        // Button 1
        ImGui::SetCursorPosX(left_margin);
        ImGui::SetCursorPosY((taskBarHeight - quickButtonSize) * 0.5f);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(70, 130, 180, 255));
        if (ImGui::Button("App 1", ImVec2(quickButtonSize, quickButtonSize))) {
            showApp1 = true;
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();

        // Button 2
        ImGui::SetCursorPosX(left_margin + (quickButtonSize + spacing) * 1);
        ImGui::SetCursorPosY((taskBarHeight - quickButtonSize) * 0.5f);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(100, 180, 120, 255));
        if (ImGui::Button("App 2", ImVec2(quickButtonSize, quickButtonSize))) {
            showApp2 = true;
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();

        // Task Manager button (third)
        ImGui::SetCursorPosX(left_margin + (quickButtonSize + spacing) * 2);
        ImGui::SetCursorPosY((taskBarHeight - quickButtonSize) * 0.5f);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(120, 120, 220, 255));
        if (ImGui::Button("TM", ImVec2(quickButtonSize, quickButtonSize))) {
            showTaskManager = true;
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();

        // Power Button
		float buttonSize = 50.0f;
		float right_margin = 20.0f;
		float powerButtonX = (float)display_w - buttonSize - right_margin;

        ImGui::SetCursorPosX(powerButtonX);
        ImGui::SetCursorPosY((taskBarHeight - buttonSize) * 0.5f);

        // Button Style for Power Button
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 100.0f); // Rounded corners
		ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(200, 0, 0, 255)); // Red button

        if(ImGui::Button("PWR", ImVec2(buttonSize, buttonSize))) {
            // Handle power button click (e.g., exit the application)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		
		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar(2);

        ImGui::End();
        // -------------------------------------------------------------------------------

        // Floating windows opened from taskbar buttons
        if (showApp1) {
            ImGui::SetNextWindowSize(ImVec2(700, 400), ImGuiCond_Appearing);
            ImGui::Begin("File Manager", &showApp1, ImGuiWindowFlags_NoCollapse);

            // two-pane layout - left = folders/files, right = details
            ImGui::BeginChild("##left_pane", ImVec2(220, 0), true);
            ImGui::Text("Folders");
            ImGui::Separator();
            for (int i = 0; i < app1_items_count; ++i) {
                bool selected = (i == app1_selected_index);
                if (ImGui::Selectable(app1_items[i], selected)) {
                    app1_selected_index = i;
                }
            }
            ImGui::EndChild();

            ImGui::SameLine();

            ImGui::BeginChild("##right_pane", ImVec2(0, 0), true);
            ImGui::Text("Details");
            ImGui::Separator();
            if (app1_selected_index >= 0 && app1_selected_index < app1_items_count) {
                const char* name = app1_items[app1_selected_index];
                ImGui::Text("Name: %s", name);
                ImGui::Text("Type: %s", (strstr(name, ".") ? "File" : "Folder"));
                ImGui::Text("Size: %s", (strstr(name, ".") ? "4.5 KB" : "—"));
                ImGui::Dummy(ImVec2(0, 8));
                ImGui::TextWrapped("This is placeholder content for the File Manager. Selecting items shows basic metadata. Implement real filesystem access to populate this list.");
            }
            ImGui::EndChild();

            ImGui::End();
        }

        if (showApp2) {
            ImGui::SetNextWindowSize(ImVec2(900, 600), ImGuiCond_Appearing);
            ImGui::Begin("Fake Browser", &showApp2, ImGuiWindowFlags_NoCollapse);

            // simple toolbar - back / forward (not functional) + address bar
            ImGui::BeginChild("##browser_toolbar", ImVec2(0, 36), false);
            if (ImGui::Button("<-")) { /* back placeholder */ }
            ImGui::SameLine();
            if (ImGui::Button("->")) { /* forward placeholder */ }
            ImGui::SameLine();
            ImGui::SetNextItemWidth(-1);
            ImGui::InputText("##address", app2_address, IM_ARRAYSIZE(app2_address));
            ImGui::SameLine();
            if (ImGui::Button("Go")) {
                // pretend to navigate
                app2_history_index++;
            }
            ImGui::EndChild();

            ImGui::Separator();

            // content area - fake page header and paragraphs
            ImGui::BeginChild("##browser_content", ImVec2(0, -36), true);
            ImGui::Spacing();
            ImGui::TextColored(ImVec4(0.9f,0.9f,0.2f,1.0f), "Example Page Title (Placeholder)");
            ImGui::Spacing();
            ImGui::TextWrapped("This is a fake browser view showing placeholder information. Below is the entire Bee Movie Script. Enjoy.", app2_address);
            ImGui::Dummy(ImVec2(0,8));
            ImGui::TextWrapped("%s", gist_content.empty() ? "Could not load bee_movie.txt" : gist_content.c_str());
            ImGui::EndChild();

            ImGui::End();
        }

        if (showTaskManager) {
            ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_Appearing);
            ImGui::Begin("Task Manager", &showTaskManager, ImGuiWindowFlags_NoCollapse);
            ImGui::Text("Processes");
            ImGui::Separator();

            ImGui::Columns(3, "proc_columns");
            ImGui::SetColumnWidth(0, 320);
            ImGui::Text("Process"); ImGui::NextColumn();
            ImGui::Text("CPU %"); ImGui::NextColumn();
            ImGui::Text("Memory"); ImGui::NextColumn();
            ImGui::Separator();

            const char* procs[][3] = {
                {"explorer.exe", "1.2%", "45 MB"},
                {"chrome.exe", "12.5%", "420 MB"},
                {"code.exe", "5.1%", "300 MB"},
                {"spotify.exe", "3.3%", "120 MB"}
            };
            for (int i = 0; i < 4; ++i) {
                ImGui::TextUnformatted(procs[i][0]); ImGui::NextColumn();
                ImGui::TextUnformatted(procs[i][1]); ImGui::NextColumn();
                ImGui::TextUnformatted(procs[i][2]); ImGui::NextColumn();
            }

            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::End();
        }

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