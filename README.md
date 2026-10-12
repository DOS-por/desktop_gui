# CSOPESY MO4 - Desktop Style OS Mock-up 

## Group Developers
* Campos, Don Oswin
* Lim, Ethan Yuric
* Gutierrez, Hanz
* Co, Stephen

### Project Structure

```text
desktop_gui/                      # Root project directory
├── imgui/                        # Dear ImGui library folder
├── x64/                          # Build output directory
├── .gitattributes                # Git attributes configuration
├── .gitignore                    # Git ignore configuration
├── bee_movie_script.txt          # Text document asset
├── desktop_gui.cpp               # Primary entry point & top-level GUI application
├── desktop_gui.sln               # Visual Studio Solution file
├── desktop_gui.vcxproj           # Visual Studio Project file
├── desktop_gui.vcxproj.filters   # Visual Studio Project Filters file
├── desktop_gui.vcxproj.user      # Per-User Project Options file
├── imgui.ini                     # ImGui configuration settings
└── README.md                     # Project documentation & setup instructions
```


## Prerequisites
* **C++ Compiler:** `g++` with C++11 (or higher) support.
* **Operating System:** Windows (Command Prompt / PowerShell).

## Dependancies
This project requires Dear ImGui, GLFW, and standard Windows OpenGL libraries:

1. **Dear ImGui Files:**
   - Download or clone the repository from the official [Dear ImGui GitHub repository](https://github.com/ocornut/imgui).
   - Ensure the core ImGui files (`imgui.h`, `imgui.cpp`, `imgui_draw.cpp`, `imgui_tables.cpp`, `imgui_widgets.cpp`) as well as the required backends (`imgui_impl_glfw.cpp`, `imgui_impl_glfw.h`, `imgui_impl_opengl3.cpp`, `imgui_impl_opengl3.h`) are included in your project structure (under the `imgui/` folder).
2. **GLFW Pre-compiled Binaries:**
   -Download the 64-bit Windows pre-compiled binaries from the [GLFW downloads page](https://www.glfw.org/download.html).
   - Place the files so that the static library points to your local path:
     `C:\Libraries\glfw\lib-vc2022\glfw3.lib`
3. **Required Linker Libraries:**
   - Ensure your linker dependencies include `glfw3.lib` and the Windows OpenGL library (`opengl32.lib`).

## Instructions

### Build & Run
1. Open `desktop_gui.sln` in Visual Studio
2. Set your build configuration to **Debug / Release** and **x64**
3. Build and run the solution.

### Simple Functions in the Desktop GUI Mockup
| Command | Arguments / Input | Description |
| :--- | :--- | :--- |
| **`desktop_workspace`** | *None* | Renders the background wallpaper along with the live date and real-time clock. |
| **`taskbar`** | *None* | Renders the bottom panel containing application launcher shortcuts and power controls. |
| **`sample_site_app`** | *None* | Opens a window displaying sample web page content. |
| **`file_manager_app`** | *None* | Opens a dummy file explorer window listing sample directories and files. |
| **`task_manager_app`** | *None* | Opens a dummy task manager window displaying simulated process, CPU, and memory metrics. |
| **`power_off`** | *None* | Triggers application shutdown and closes the desktop GUI. |
