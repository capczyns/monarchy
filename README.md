# monarchy
CIS 375 Butterfly Tracking System

Build Instructions:

Visual Studio:
  Go to file->new->project from existing code
  Select Visual C++ and press next
  Click browse and navigate to the project directory
  Set a project name, press next
  from Project Type select Console application project
  Click finish
  The project should now be ready to build

Code::Blocks
  --It appears to be a known issue with the version of mingw packaged with Code::Blocks 13.12
  --I would recommend building with Visual Studio if you have to work on Windows.
  -- http://mingw-w64.org/doku.php contains a version of mingw that should work if you want to fix your Code::Blocks
  Create an empty project
  Go to Project->Add Files Recursively
  Navigate to the project directory
  Once files have loaded, go to Project->Build Options
  Check the box next to "Have g++ follow the C++11 ISO C++ language standard [-std=c++11]"
  The project should now be ready to build
