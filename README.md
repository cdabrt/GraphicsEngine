# GraphicsEngine  
A work in progress: After many years of experience in OO and functional programming languages I decided to jump into a low-level imperative paradigm using C and also take a leap into the world of graphical computing by starting work on a graphics engine. Low-level programming is not new to me, however, I want to brush up on skills and learn new ones. To make this learning experience more exciting and challenging, I decided to combine it with such a complex project. This way, I combine testing my already existing skills in architecting complex architectures and systems with skills that I will gain in a new programming and computing paradigm.

For now, this is an educational project which also exists to showcase my work on my portfolio if it bears fruit.

## License
This repository and its code are made publicly available solely for my own educational, portfolio and personal purposes. 
Feel free to fork this repository for personal study and exploration. 
However, any copying, modification, distribution, or commercial use of this code is prohibited without explicit written permission from me.

## Build
Run the following commands below. Make sure to install a C compiler and add it to your PATH if you are on Windows.

-**Conan commands**
* conan profile detect --force  
 This automatically creates a conan profile based on system scans.
* conan install . --output-folder=build --build=missing  
 Installs dependencies set in the conanfile.txt. --build=missing is here in case no pre-compiled binary exists of a dependency. 

-**CMake commands**
* cd build  
 Cd into build folder.
* cmake .. -DCMAKE_TOOLCHAIN_FILE=build/Release/generators/conan_toolchain.cmake -DCMAKE_PREFIX_PATH=build/Release/generators -DCMAKE_BUILD_TYPE=Release  
 Set conan toolchain and build type.
* cmake --build .  
 Build project using cmake.
***
**Using CLion:**  
Right click on the makefile and click load CMake Project. It will show an error at first, no issue. Proceed with the steps below.  
In CLion under Settings -> Build, Execution, Deployment -> CMake
Add the command:  

-DCMAKE_TOOLCHAIN_FILE=\${PROJECT_DIR}/build/build/Release/generators/conan_toolchain.cmake -DCMAKE_PREFIX_PATH=\${PROJECT_DIR}/build/build/Release/generators -DCMAKE_BUILD_TYPE=Release  

Replace \${PROJECT_DIR} with your absolute path to the project.  
With this, you can now add your own run configuration. Select CMake Application, choose the run target (name of the project in the CMake file) and you should be able to run the program.  
***
**Note:**
Always run the Conan commands before running the CMake configuration. 
Also, always run the CMAKE commands after making edits or creating new files (or use the built in CLion functions for reloading the CMake project).