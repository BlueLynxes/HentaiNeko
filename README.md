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