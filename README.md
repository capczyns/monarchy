# monarchy
CIS 375 Butterfly Tracking System

Build Instructions:

Visual Studio 2015:
  Go to file->new->project from existing code
  Select Visual C++ and press next
  Click browse and navigate to the project directory
  Set a project name, press next
  from Project Type select Console application project
  Click next
  Under "Preprocessor definitions (/D): add _CRT_SECURE_NO_WARNINGS
  Click finish
  The project should now be ready to build

Code::Blocks
  Create an empty project
  Go to Project->Add Files Recursively
  Navigate to the project directory
  Once files have loaded, go to Project->Build Options
  Check the box next to "Have g++ follow the C++11 ISO C++ language standard [-std=c++11]"
  The project should now be ready to build

Build Requirements:
  c++11 support
