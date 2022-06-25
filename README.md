# HentaiNeko
## *Manage your Waifus! :3*

I wrote a long document to describe the project, but for now I don't have a prototype that's ready. Just most of the UI for a piece of the program.
So there you go, have those.

*Note: icons are broken because I made this in my Ubuntu VM but now it's running on another device. Also, it doesn't respond to dark theme here, there are some things to work on (many)... hey, I started this 3 days ago, and 3 days ago, I didn't know anything about GTK.*

![image](https://user-images.githubusercontent.com/107735757/174418153-6dfa62b8-0ee3-4a07-beef-4f650133fddc.png)
![image](https://user-images.githubusercontent.com/107735757/174418175-c763f391-869f-4972-b702-786480bd662b.png)
![image](https://user-images.githubusercontent.com/107735757/174418207-3fb104ff-a692-44b9-9a07-8fba6501446f.png)

### Build requirements
_Considering that this is a demo, and literally not ready for anything aside from looking somewhat pretty (only on Ubuntu gnome tho)_
you can build this using CMake: you will need to have the following dependencies installed:
 - GTKmm (specifically GTKmm3.0 aka GTK3)
 - Jsoncpp

I\'ve only ever built this for Linux, thought, you can use Msys to get this running on Windows, should be pretty simple.
_Note: CMake will output everything on a specific folder, alongside a bunch of folder containing UIs and resources, which you don\'t have._
_I didn\'t upload the `resources` folders because I\'m hella scared of copyright, so just create one and you\'ll be fine!_
_You could also drop a random .jpg or .png called `previewFallback.png`, thought, for now it\'s not necessary._

More info soon hopefully!

** Update 1: **
 - Development undergoing! First piece of the backend done! (many more missing tho)

** Update 2: **
 - Did a bit more work today, minor edits to the templates (for now refer to `templates/properties-template-updated.jsonc`),
   the other one will have to be removed, but for now... well, it\'s there.
 - What\'s in the code? Where is the image preview?
   So, the screenshots are from a Python prototype which did have the working image previewer (albeit, very slow image previewer)
   Since the app will be made in C++, I thought it\'d be a waste to just include the python script for demo purposes, so for now,
   no image preview.
 - What does the app do? For now, just tests and opening the GUI using the class I made, lot of work to be done still.

 Next steps:
 - The main priority would be going back to the state of the Python prototype, which means adding the Image Previewer custom widget.
   Hopefully using the GPU to resize the image to save some performances, but who knows.
 - Also, adding the about window, it\'s pretty simple and asbolute a must do, very important.
 - Splitting the UI file into smaller files.
   This is my fault when I got too happy using glade and ended up making one single giagantic atrocity of a file.
   There isn\'t anything necessarily **wrong** with this, however, for convenience each file will contain a Window, composite widgets
   will also have a file of their own.

** Update 3: **
 - Added about Window and signal to the button to open said window
 - Added dialogue to pick collection entry point when clicking the button
   Yes, the dialogue effectively works, but the collection scanner and image previewer have yet to be implemented.

 Next steps:
 - Implementing the logic to scan the entry point (essentially, iterate all the subdirs and look for pics)
 - Implement the image previewer...
   This sounds simple but isn\'t THAT simple. The original idea would be using a Gtk::Image, unfortunately tho in GTK3
   said images cannot be stretched, they just stay whatever resolution the image is. In GTK4 you have way more control
   but for now we\'re stuck on GTK3 (tho, I really wanna move to GTK4 once the tools around id get more mature).
   So essentially what I have to do is create a pixbuf, load the image in there, and then play with it resizing it using
   my own custom logic whenever the space size changes... It isn\'t necessarily complicated (at least wasn't on Python)
   the worry is the performance hit on window resize, which even though not that much of a big deal, still annoying.
   Thanks GTK3 `;v;`