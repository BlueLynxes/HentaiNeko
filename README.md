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

 **Update 1:**
 - Development undergoing! First piece of the backend done! (many more missing tho)

 **Update 2:**
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

 **Update 3:**
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

 **Update 4:**
 - Added collection scanner, kicks in when an entry point is selected via the GUI.
   There is one flaw however, the collection scanner essentially iterates recursively looking for every file, then
   it extracts the file extension, converts is to uppercase and matches it against a list of supported extensions.
   This works, but scanning a collection with thousands of files can take time, if that happens... the software
   literally hangs while it\'s doing it and the OS may even report it as not responding while it\'s doing it\'s thing.
   Depending on where the pictures are store (aka storage speed) and even computational speed, aside from, of course
   amount of pictures, this can take a while (a few seconds for 1900 pictures stored on a NAS in LAN, done by a VM).
   I would really need to do this in another thread and to show a spinner loading thing while it\'s working.

 Next steps:
 - IMPLEMENT THAT DAMN IMAGE PREVIEWER!

 **Update 5:**
 - Woohoo added the working image preview! And let me tell you, way faster than the Python prototype.
   You can pretty easily test it, just follow the note under the *build requirements* to add a 
   fallback image to preview.
   **Note:** when I say that there is a *working image previewer* I mean that the widget is there, it works
   and the image does scale correctly, however, the buttons that will change the previewed images have
   not yet been implemented like in the prototype... so hang on tight, that\'s still to be done.

 Next steps:
 - Destructor to deallocate memory:
   Yup, until now I **did not** do that, mind you, because most stuff i scoped to the lifetime of the class
   anyway, however, from now on some stuff will be working with pointer and stuff allocated to the heap.
   Now, the `ImagePreviewer` widget has been temporarily and brutally bashed right into the init function for
   the data insertion window, which is, well, temporary and just to test the widget.
   There should be a pointer as a class member, which gets initialized by said function and deallocated by the
   class destroyer. This also means that the pointer should either always be allocated (as in, all init function
   **must** be called), or there should be some checking of wether a pointer is `nullptr` or not.
   Eh, I\'ll think about it next time.

 - Implement the next and back buttons for the image previewer:
   Essentially, this should be the last step for clickign on the *"Select Entry Point"* button and then actually
   seeing the images in your collection on the image previewer, for now, tested supported formats are `jpg` and `png`
   with `gif` being kinda supported (only the first frame will show), no videos... still work to be done.

 - Implementing a loading bar or spinner while the scanner is running through the collection:
   I would have liked to do this today, but it meant working up a lot of stuff for multithreading and adding stuff
   here and there, so for the moment I decided to not do that, thought, it is necessary to do it in the future.
   **Important note:** this means that if you select a pretty large collection with many individual files the program
   may hang while it\'s listing everything and parsing the extension, as a result a horrible message will popup saying
   that the application is not responding, which will disappear as soon as the scanner has done it\'s job.
   This happens because the scanner is blocking the thread, and I belive GTK has to report every now and then that
   it\'s not stuck, which cannot happen while the thread is stuck by the scanner.