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
### How to Build and Run

## Build & Run
1. Open `desktop_gui.sln` in Visual Studio
2. Set your build configuration to **Debug / Release** and **x64**
3. Build and run the solution.

### Commands in the Custom Marquee
| Command | Arguments / Input | Description |
| :--- | :--- | :--- |
| **`help`** | *None* | Displays all available commands and their descriptions. |
| **`start_marquee`** | *None* | Starts the marquee animation. |
| **`stop_marquee`** | *None* | Stops the marquee animation. |
| **`set_text`** | `<string>` | Accepts a text input and displays it as a marquee. |
| **`set_speed`** | `<int>` | Sets the marquee animation refresh delay in milliseconds. |
| **`exit`** | *None* | Terminates the console application. |
