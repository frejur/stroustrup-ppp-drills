# Chapter 16 - Review questions

### Reasons for wanting a GUI
- To create an intuitive interface: it mimics real-life, allowing users to visually manipulate different 'objects' on the screen.
- It is often expected of a modern application, both in terms of visuals and usability.

### Situations where a non-graphical interface is preferred
- Technical / professional work where tasks are performed based on a limited set of commands.
- Programs where a GUI would add unnecessary complexity, e.g.:
	+ Applications that can be chained together with other tools or run in scripts (Often terminal based).
	+ Systems with limited processing or display capabilities.
	+ Systems that are accessed remotely to perform administrative tasks.

### The definition of a software layer
A level of abstraction within a system that provides specific functionality, such as:
- A graphics library
- Device drivers
- The operating system
- A program that interacts with any of the above.

### Reasons for layering software
To organize functionality and abstract complexities, allowing developers to build higher-level features on top of existing systems.

However, it's also a natural result of how systems evolve over time, where new layers are added incrementally as technology advances and projects grow, often without it being a fully conscious design choice from the start.

### The fundamental problem when communicating with an operating system using C++.
The operating system doesn't "speak" C++, so an abstraction layer is needed to translate certain constructs into something the OS can handle.

This is done not only out of necessity but also to ensure cleaner, more maintainable code.

(Ideally, even within the C++ code, low-level or C-like implementation parts should be kept separate and hidden behind a more modern interface)

### The defintion of a callback
A callback is a function registered for an object that the system (OS + GUI framework) will "call back" when the object is triggered by an event, like a button click.

### The definition of a Widget
A visual object that may be interacted with, the book describes them as "forms of interaction".

### The 'other' name for a widget
Also known as a **control**.

### The meaning and pronounciation of FLTK.
Fast Light Toolkit, pronounced 'full tick'.

### Some other common GUI toolkits
QT, GTK, Dear ImGUI, Electron.

### Systems that use the term widget vs. control
The book considers **control** to be "more descriptive, but less evocative".

However, it does not name any particular systems that prefer this term over **widget**.

### Some examples of widgets?
Window, Button, Menu, In_box, Out_box

### Situations where you would want to use an In_box Widget
When you want to capture text input.

### The type of the value stored in an In_box Widget
A string (Which can be interpreted as numerical input if needed).

### Situations where would you use a button
When you want to trigger an action as a certain rectangular area of the window is clicked, e.g.:
- Next
- Submit
- Quit

### Situations where you would use a menu Widget
When you want several buttons that are grouped together.

This facilitates aligment, placement and enables the developper to perform actions such as hide() on the entire collection of buttons.

### The definition of 'control inversion'
The transfer of control over the order of execution from the **program** to another entity, in this case the **GUI** and its widgets.

In conventional programs the order of operations is directly expressed in code.

In a GUI program, user actions, like clicking a button, trigger callbacks, determining the flow of execution.

### The basic strategy for debugging a GUI program
- Use well-tested components
- Develop incrementally
- Carefully check linker settings
- Compare against working code, line by line if needed
- Explain the code to a peer (Or do some rubberducking)

### The reasons debugging a GUI program is harder than debugging a program with text based input and output

Mainly because of the control inversion: The execution flow is driven by unpredictable user interactions.

This complicates the "tracing" of program execution, and it can get exceedingly tricky to identify which callback was triggered and by what action.

The multitude of possible operation combinations often makes systematic testing impractical.

Additionally, output statements may fail when the GUI doesn't display correctly, and exceptions may simply be ignored by the GUI framework.
