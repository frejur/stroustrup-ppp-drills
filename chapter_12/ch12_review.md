# Chapter 12 - Review

### Reasons for using graphics.
- Graphics are essential for presenting data, in fields such as scientific computing and data analysis.
- Some programs are graphics-reliant by nature: video games, digital artists' tools, visualization software.
- And generally speaking, most applications these days are expected to come with some form of GUI.

### When not to use graphics.
When there is no need for visual representation or when textual representation is enough.

E.g. command-line applications, data processing tasks or web services.

### The reason graphics is interesting for a programmer.
- Improved userfriendliness of the end product.
- The fact that it provides immediate visual feedback often makes it more enjoyable to work with.
- Graphics code is often more readable than other types of code, it corresponds directly to what is seen on the screen.

### Definition of a window.
- In terms of the programs built throughout Chapter 12: a container of Shape objects and other graphics.
- In terms of the OS: a canvas that provides a graphical representation of the current program.

### The namespace used to keep the graphics library used in the book.
'Graph_lib'.

### The header files needed for creating basic graphics while following along with the examples in the book.
```
#include 'Graph.h'
#include 'Simple_window.h'
```

### The simplest window to use.
Graph_lib::Simple_window

### The most minimal window.
```
Graph_lib::Simple_window{640, 320,  "Label goes here"};
```

### Definition of a window label
The descriptive text that appears in the menu bar at the top (In 99% of window managers) of the window, and in the task manager.

### How to label a window
By specifying it in the initialization of a new window object as outlined in the earlier 'most minimal window' example, or with the 'set_label()' method:
```
window.set_label("Or here");
```

### A short explanation of Window and Screen coordinates.
Coordinates are specified as the offset from the point of origin in pixels, which is the top-left corner.

The coordinates {100, 50} signify an offset of:
- 100 pixels to the right from the point of origin (X-axis)
- 50 pixels downwards from the point of origin (Y-axis).

### What about mathematical coordinates?
In 2D-graphics the direction of the Y-axis is usually inverted compared to mathematical coordinates, so the equivalent of the above would be {100, -50}.

### Examples of simple shapes available in the book's graphics library.
- Graph_lib::Line
- Graph_lib::Rectangle
- Graph_lib::Closed_polyline
- Graph_lib::Text
- Graph_lib::Ellipse

### How to attach a shape to a window.
```
Graph_lib::Simple_window win{640, 320, "Label goes here");
Graph_lib::Rectangle r{{10, 10}, {100, 100}};
win.attach(r); // Attach rectangle
```

### How to draw a hexagon using shapes.
Use a **Closed_polyline** and basic trigonometry to add and arrange its points accordingly.

Please refer to Exercise 11 and the **RegularPolygon** class for implementation details.

### How to draw text.
```
Graph_lib::Text txt{{10, 01}, "Text goes here"}; // First parameter = Position
```

### How to display an image.
```
Graph_lib::Image img{{10, 01}, "path_to_image.jpg"}; // First parameter = Position
```

### Reasons a 'Window' object might fail to appear on screen.
- It is too small, and the window manager is set to draw applications "borderless" (So no toolbar or surrounding frame).
- It is spawned out of bounds (Negative coordinates, or coordinates that exceed that of the current screen resolution).
- The 'draw' method was omitted ('draw()' or 'wait_for_button()').

### Reasons a 'Shape' object might fail to appear in a window.
- It is set to transparent.
- It is set to the same color as the background.
- The points that make up the shape are arranged incorrectly, so the shape could not be drawn.
- It is too small.
- It is drawn out of bounds (Negative coordinates, or coordinates that exceed that of the current window size).
- It was never attached to the window.
- It has not been drawn yet / will apear after the next call to 'wait_for_button()'.
