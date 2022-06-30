# HentaiNeko
## *Manage your Waifus! :3*

I wrote a long document to describe the project, but for now I don't have a prototype that's ready. Just most of the UI for a piece of the program.
So there you go, have those.

*Note: icons are broken because I made this in my Ubuntu VM but now it's running on another device. Also, it doesn't respond to dark theme here, there are some things to work on (many)... hey, I started this 3 days ago, and 3 days ago, I didn't know anything about GTK.*

![image](https://user-images.githubusercontent.com/107735757/174418153-6dfa62b8-0ee3-4a07-beef-4f650133fddc.png)
![image](https://user-images.githubusercontent.com/107735757/174418175-c763f391-869f-4972-b702-786480bd662b.png)
![image](https://user-images.githubusercontent.com/107735757/174418207-3fb104ff-a692-44b9-9a07-8fba6501446f.png)

**Some new Screens btw :3**
**With dark theme on Ubuntu, this is the C++ version (Update 8)**
General UI (same as Python prototype)
![Screenshot from 2022-06-30 01-22-22](https://user-images.githubusercontent.com/107735757/176562561-28ea940c-1246-4c46-86f8-be1e97b824bc.png)
Working image previewer :3 **(spent looking a bit to find a SFW picture in there)**
![Screenshot from 2022-06-30 01-24-58](https://user-images.githubusercontent.com/107735757/176562630-d10a4c69-5421-4e86-bd83-ea73a87460a7.png)
Working JSON Previewer (thought, for now empty)
![Screenshot from 2022-06-30 01-25-18](https://user-images.githubusercontent.com/107735757/176562717-dd09a0e6-f87d-430f-801a-b62a2c5d5d29.png)

Little about Window

![Screenshot from 2022-06-30 01-26-09](https://user-images.githubusercontent.com/107735757/176562733-4249bec6-8f63-466b-b579-00145c40812a.png)

By building the project as of right now, you get what you see in the screenshots\* (the one with the dark mode). You will see it with whatever GTK3 theme you have.
Unless you're on my same version of Ubuntu Gnome with the custom icons, the fallback icons will be the samed as the light theme screenshots... I need to fix those.

\* *Waifus not included*



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

 **Update 6:**
 - Added threaded scanning!:
   Now the scanning process is executed on a detatched thread, I figured out how to make the worker thread call
   a function in the main GTK thread to start a spinner and then stop it to show the image previewer.
   In theory said image previewer **should not** be leaking, but let's be honest, I\'m doing big assumption on what
   GTKmm does, and I\'m not paying necessarily too much attention on this *actually very important* stuff.
   So it shouldn\'t, but it may.
   Anyway, the behaviour has now been fixed, scanning a collection will close the dialog right away, to the show a spinner
   instead of the image previewer, finally the first picture of the collection will be shown. The buttons to switch
   to new pictures have yet to be implemented.

 Next steps:
 - Implementing the *"next"* and *"previous"* buttons for the GUI... One that\'s done, we\'re pretty much in the
   "what the Python prototype did" territory, except for opening a couple of extra menus (that did nothing, mind you).
   Soon enough, I should be able to clean up the glade file a bit and start working on the actual data input to then
   compose the json and save it in the picture.
   The good news is that the json parser and serializer already exist, I don't even know yet however what library to user
   to edit metadata.

   *As an extra note to this:* aside from implementing the next and previous buttons, the logic itself to change the current
   preview image should be moved to a single function, instead of being called here and there kinda randomly.
   It being called randomly is of course the result of me testing around stuff along the way... so there is that to do too.
   
 - SQLite:
   Let\'s not get ahead of ourselves here, consider this more of a spoiler... but soon enough I\'ll start working on the SQL schema
   to index all the scanned JSONs. Remember, the JSONs inside the files are there for trading and as a mean to collect the user input
   first hand, of course iterating through every picture and parsing a JSON for every search is insane, everything will be indexed
   in a database, more precisely a SQLite database, essentially which is about the only artifact generated by HentaiNeko that will
   live in the library... in theory.

 - Upscale under res pictures:
   This is an idea but I think it makes sense, if when a picture is scaled it is displayed at a resolution above the actual
   picture resolution, upscale it... More of a "thing I wanna do" than a priority.

 **Update 7:**
 - The image previewer is now fully working! However, a new issue arose from the depths of my code...
   In some cases images in the collection can be pretty heavy (even more than 10 MB), and if those images are stored remotely
   for example on a NAS, HentaiNeko will still load them, however, they will be loaded directly from Gdk using the method to load a file.
   Now, the issue with this is that Gdk will be blocking the main thread until it loads the file, meaning that if it takes a few seconds
   download and load a picture, the application will lock up and be unresponsive until the process is done (exactly the issue we had with
   the scanner).
   The problem here is the fact that it is Gdk that loads the file for now, so instead what we should do is load the buffer on a separate
   thread and show a spinner until that's done, then when it is done init the object and remove the spinner. This way the application will
   not lock up until the picture is loaded.

   Also, the scanner really isn't thread safe, meaning if you start a new scan while the old one is going (you don't wait for the scan to
   be over) there will be mixed results from both scans in the result vector, hence in the final result.
   Or stuff may crash. Essentially, we should watch out for data races.

 Next Steps:
 - IMPLEMENT THREAD SAFETY AND CHECK FOR MEMORY LEAKS:
   However for now I want to build the app, and I want a working pre pre pre alpha, so this will be done at a later time.

 - Implement the data input:
   Anyway there shouldn't be any other complex memory management or threading to do, so for now the missing part is just reading
   user input, compose the JSON and read the JSON, and of course, check if an image has a JSON and if so load everything and whatnot.

 - Implement the composed JSON preview, this will almost be more of a debug tool than an end user thing... but I need it, and anyway I
   don't see anythign wrong with user checking out the JSON or importing a JSON they made with another app or by hand (anyway only valid
   parts of a JSON will be loaded, and we can implement error messages if need be).

 **Update 8:**
 - The `Select Entrypoint` now becomes disabled when a scan starts and until it ends.
 - An issue has been found where clicking the next picture button and then going back prevented you from seeing the first 1 picture again; issue has been fixed.
 - Implemented the JSON Preview:
   It does effectively work, but so far the `ImageProperties` object doesn't get any input, so there isn't anything to add in the json aside from the base structure.
   It would also be cool to add some basic syntax highlight, the gnome project has some stuff [here](https://wiki.gnome.org/Projects/GtkSourceView) but since this is hardly
   a priority of any kind, for the moment I'll skip this. It would also be nice the set the font to a mono something... hey it works, for not that's enough!

 Next Steps:
 - There is not check regarding permission or accessibility to the files, therefore not having access to a file will make the application crash during the scan.
   (I hopened an issue for this since keeping track of it on this file is not ideal)
 - As said in *Update 7*, implement the data input is the next major step.
   This will be a lot of work, considering how the amount of input to set and data to collect.
 - Saving JSON to picture file:
   Once the JSON gets added to the picture file, effectively the data input part is done, the only missing thing would be adding some more formats
   to the image previewer, for now only `JPG`, `PNG` and supposedly the first frame of `GIF` are supported, `webp` isn't, which is a surprisingly common
   format.
 - Start working on auto completion (more on this on a later update, everything is on a document that I haven't pushed on the repo yet).

 **Update 8:**
 - The application can now recover from a failed scan and an error message is shown.
 - Components initialization have been moved to the `Application` constructor.

 Next Steps:
 - Custom input widget:
   As you can see from the screenshot, many parts of the input GUI use the same combination of widgets, except for two field
   being slightly different, those widgets are a Box containing a Scrolled Windows containing a List Box containing a number
   of Rows with checkboxes and label, at the very bottom there is an entry with a button on the side.

   The idea is that list contains all the previosuly user (or template) define tags that can be applied, since tags can be user
   defined aside from the standard ones (standard which still needs to be made), there is an entry at the bottom to create said tags.
   
   The first step is isolating the Widget from the main glade file, since it will be used many times on different occasions, therefore
   it is now effectively time to split up the UI files, before this one becomes too large and hard to manage, thought, I still ma not
   completely convinced about it (since it would be more annoying to deal with it in Glade).

   Then implementing the parses and serializer for the user defined tags, since those will also have to appear on the list of available tags.

   Once all of that is done, the custom widget class will need method to both populate the list and to retrieve which checkboxes have been populated.

   All those info will then be passed to the object composing the json to write onto the picture.

   **But wait, there's more**
   Obviously a picture could already have metadata in it, this would mean two things, first of all the user should have a button to skip the pictures
   that already have metadata in them (In the scan dialog maybe, adding a checkbox could work?), then, if a loaded picture does already have metatdata,
   it should populate the GUI.