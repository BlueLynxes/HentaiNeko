# Changelog

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

 **Update 8.1:**
 - Eye properties have been removed since theys hould really just be some facialExpressions
 - Created a new updated template for the user define / template defined tags... Ideally, there should be a standard one and separate
   user defined ones, so to allow users to export their preferences separately from the community ones, then allowing HentaiNeko to merge them.
   This way a user could have both the community provided options + it's own custom tags and values.

   At the of the day, in the final config tags object, there would be no difference, it would just be a case of initializing the object with
   multiple files, checking whether a specific item already exists, and if so what about the subtags and what not.
 - Created a version label, which gets initialized from CMake, the version is `0.8.1`, the way it works is actually pretty simple, and
   it follows the `major.minor.patch` scheme.
   - `major` = `0`, since as of right now the application is in development and has not reached a major release yet (aka v 1.0)
   - `minor` = `8`, which is the current *"update"* recorded on this log, which is effectively going to become **changelog**.
   - `patch` = `1`, since after the 8th update I have given some extra stuff and defined it as a patch
   
   If for whatever reason the version macro is missing (which technically cannot happen since cmake inits it), a different message
   will be shown.

 **Update 0.8.2:**
 - Started working on the input side of things. I managed to get a custom checkbox appearing with the string selected on the entry,
   however, a better approach would be making a custom widget in code and having that managing it's own stuff, instead off having to
   implement what I did in the previous commit over and over again...
   Essentially... there is progress, but nowhere near usable.

 **Update 0.8.2.1:**
 - Essentially I started doing what I said I would have done in `v0.8.2`, meaning I made a custom widget that implements the scrollable
   list with the checkboxes + the entry and the button.
   It is still work in progress...

 Next Steps:
 - Keeping on working on that very same custom widget. My idea would be turning the class that exists right now into a template base
   class, then having other class inheriting the base class. The template would serve as way to customize what kind of input the class would have, for example, in some cases the widget will only show simple checkboxes buttons in the list, in other cases it will need
   to display custom horizontal boxes with two entries + some buttons.
   
   I'm still thinking about the design, I may also decide to ditch the whole template thing and just inherit and overload stuff...
   thought, I guess in thise case this would be the less optimal decision.

   Anyway, pretty satisfied with the progress since this was a main thing that needed to be done and will be used a lot.

 - After completing the custom widget, the class to read and store custom tags preferences should be implemented, since that will be
   what will show the initials items in the widget list. And of course, it will also be where the widget saves new tags.

 **Update 0.8.2.2:**
 - The `DynamicCheckbox` can now actually store any kind of widget of which type is provided via template... there are a few **BUT**
   however. First of all, for now a HUGE assumption is made on the constructor of said widget passed via template, and the assumption is that said widget will constructor taking an `std::string` or equivalent. For example, a `Gtk::Label` or a `Gtk::CheckButton`, now
   considering the usecase which is limited to `Gtk::CheckButton` and custom widgets... This is a requirement that can be respected.

   Now, wether this is the right thing to do or not is a different story... probably not, maybe not, maybe I should try to do some
   templating magic to get the function and argument to try and always use the correct constructor, whatever.
   As a requirement to be used by `DynamicCheckbox`, the widget shall have a constructor taking an `std::string` or equivalent.

 Next Steps:
 - Rename `DynamicCheckbox` to `DynamicList` since now the list is not limited to `Gtk::CheckButton`es.
 - Complete the integrations, which boils down to:
   - Storing data alonside the widget.
     Internally the class has a `std::vector` which only contains the widget, this should be enough to retrieve the data, since
     the widget is the mean to retrieve the data after all, for example, the state of the checkbox is something that is gained through
     the `Gtk::ChecButton` anyway.

     How this is done is yet to be considered. Realistically, there could be a template specialization, where the function is deleted
     if the type of the widget is not recognized (meaning a custom one or a known Gtk one). This way the correct method to retrieve
     data could be called if known, but the list could still act as a list if not.

   - Retrieving all the collected data:
     Meaning return a `std::vector<Data>`, which will be created simply by iterating every widget in the vector of widgets and
     while retrieving the data using the way stated above.

   - Individual listbox element callback functions:
     
     This will be the trickier problem. Tags can be of course added, but also removed from the list, therefore a remove button should
     be available in the list of available items (thought, of course, this would be custom to each widget).

     The best solution probably is leaving this up to the custom widget itself, but then how to avoid sefault when deleting the widget
     that Gtk will try to draw?
     Still a few considerations to do.

  **Update 0.8.2.3:**
  - Refined the `DynamicCheckbox` custom widget (_which needs to be renamed btw_).
    I realized that there is no point into doing the whole pair thing (thought I got it to work and as suspected the problem was just
    `Gtk::Checkbutton` being non copyable... for obvious reasons! So literally `std::move` fixed it right away), the reason being
    that anyway all the data is stored withing the Widget itself so what would be the point of copying all of that into another vector?

    Also, there are a couple of considerations to do:
    - First of all, it is pretty annoying to extract data from the widget itselfs when inside the `DynamicCheckbox`, the reason being
      that every Widget can have a different method to extract the required data, for example: `get_active()` for `Checkbutton` and
      `get_text()` for `Entry`... We would need to do a lot of magic and add a log of _intricacies_ (written fancy like that), in order
      to call the correct function and extract the data. Probably possible with templates somehow tho.
    - It is unnecessary, and frankly, a waste.
      Whatever thing is creating the `DynamicCheckbox` knows exactly how to retrieve the data using what method. So how about we just
      return a lovely reference to the internal vector containing all the widgets, and then let the caller deal with it?

      Well, that's exactly what's going on now. Meaning we can effectively add whatever type of widget we want, as long as it can be
      added as a `Gtk::Widget`, it's good to go.
  - The Json preview window now shows the selected scene types from the list! Yay!
    *(this was actually done to test the thing above, but pretend I did it to add the thing right away)*

 Next Steps:
  - Rename `DynamicChekbox` to `DynamicList` or something like that.
  - Create the parser for the default tags thing and use it to add the default checkboxes where needed.
  - Add a system to delete the widget inside the listbox, using a button within the lsitbox itself.
    
    And I kind of have an idea to accomplish this.
    Essentially, instead of having the user create the button, how about the Widget the user adds is not directly added within the
    list, but rather it is added inside an horizontal box which will contain both the custom widget and a button on the right to
    delete the widget (which is also going to delete the label from the custom defined tags file).

  **Update 0.8.2.4**
   - Added an encapsulation system to wrap the custom widget in a horizontal box with a delete button (which for now does nothing)
   - Updated the `getWidgets` method of the `DynamicCheckbox` to iterate inside the vector containing the widgets (aka the horizontal
     boxes) and extract the user defined widget.
     
     Little note tho, now said vector contains pointers.
     This is still slower since we are effectively creating a new vector, but the memory waste is minimum since it's a vector of
     pointers (I fought with my life for it to be references, but failed) and it gets *supposedly* moved to the caller function.

     Of course since now we're dealing with pointers, the syntax changes a bit... but nothing major (just use `->` instead of `.` or
     dereference the pointers with `*`).

 Next Steps:
  - Add callback to remove row.
    
    I do have an idea on how to do this already. Apparently using `sigc::bind` it is possible to give an argument to a callback
    which means that we can effectively have a single callback function, which will then be called by every button.

    The only extra step is using `std::bind` and giving the correct index to remove the correct row. But this is also pretty easy!
    All we need to do is give it the iterator of the last item of the `listboxItems` vector, so that when we want to delete it, we
    already have the correct iterator.

    However there some questions to wether that's possible or not, does the function calling the callback actually support something
    like that, or only literals? And what about when I delete an element, wouldn't the vector point to the wrong element then, and
    make the application crash if pointing to something out of bounds?

    Maybe I had more of a hunch than an idea, so yeah... so more thinking to do here. However, a step forward.