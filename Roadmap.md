# Roadmap

As usual, the state of the project is messy. It started out in python for testign with GTK, which went well.
However Python is definitely not suitable for this kind of work, lack of structure kills the application.

I managed to create an environment using Visual Studio 2022, VMWare and CMake to write the code on VS and build the application directly on the virtual machine.
The priority for now I to create a decent structure for GTK. Unforutnately GTKmm is not as well maintained as I hoped it would be, so we'll have to go with
GTK3 from C directly.

First step is reaching the point that we reached in Python from C++ using the C APIs.

Specifically the following

 - [x] Succesfully Display UI
 - [x] Display extra Windows (about window in this case)
 - [x] Parsing Json File Correctly
 - [x] Serializing Json File Correctly
 - [x] Create Main Object Representing the GUI
 - [x] Getting a working image previewer
 - [x] Getting a working JSON preview dialogue
 - [x] Getting a working directory picker dialogue

From there on, adding all the new features.
Honestly, feature wise the input application is relatively simple, most of the work came from creating the UI.

## Important Projects Improvement

This kind of stuff should be done early in the lifecycle of the project to not be a problem earlier.

**Splitting the main glade file**

Right now all of the UI is stored withing `ui/HentaiNeko.glade`, this is a mistake.
Each window should have it's own glade file, just like each complex widget should.

This is also a done to shrink UI files sizes, save a lot of reused code, and editing one
XML gile Widget will update the Widget everywhere within the application.

_Note: Althought Glade can specify IDs for Widgets, in the case of reusable complex Widgets specifically We should avoid using Glade IDs, there will be many instances of the same Widget, so we should copy the Widget assing it an ID in code, and then reference it by that._

_If this is possible, that is._