# Chapter 13 - Review

### The reasons why the book implements its own graphics-library.
- To not overwhelm the reader with all the features of a complete graphics library.
- To introduce fundamental graphics concepts while building the classes.

### The minimum amount of classes needed from the library required for basic graphics output.
The most basic example demonstrated in the book includes three: Simple_window, Point and Line.

### The header files needed to use the graphics library.
In order of importance (Only the top two are required #include's):
1. Window.h
2. Graph.h
3. Point.h (Included in Graph.h)
4. GUI.h
5. Simple_window.h

### The classes that define closed shapes.
- Closed_polyline
    - Polygon
- Rectangle
- Circle
- Ellipse

### The reason 'Line' is not used to create every shape.
A line always consist of exactly two vertices, so even if one were to chain multiple instances of Line together the end result would contain overlapping duplicate points.

### How to initialize a 'Point'.
```
Graphics_lib::Point p{0, 0}; // Plain old data, no default values
```

### How to initialize a 'Line_style'.
```
Graphic_lib::Line_style s{0}; // Initialize by index, 0 = Line_style::solid
```

### How to initialize a 'Color'.
```
Graph_lib::Color c{0}; // Initialize by index, 0 = Color::red
```

### The definition of RGB.
A system for defining color values using three measurements: Red, Green and Blue.

### The difference between two 'Line' objects, and a single 'Lines' object containing two lines.
You cannot control the individual Line objects contained in a Lines object, things such as appearance and draw order are applied to the whole shape.

### The shared mutable properties of 'Shape' objects and all its siblings.
Color, fill color, line style, position.

### The number of sides of a Closed_polyline with five points.
Five if none of its lines cross, but there's no guarantee they won't.

### The visibility of a 'Shape' object not attached to the current window.
None.

### The difference between a 'Rectangle' and a 'Polygon' with four sides.
A Rectangle is always parallell to the X and Y-axes, its opposite sides are always of equal length, and it always consist of four right angles.

A Polygon is not restricted by any of these invariants.

### The difference between a 'Polygon' and a 'Closed_polyline'.
The lines that make up the Polygon may not cross.

### The depth order of 'fill' and outline'.
The outline gets drawn on top of the background color.

### The reason the book doesn't define a 'Triangle' class.
Because without defining any additional invariants, like making it a Right Triangle for example, it's essentially the same thing as a Polygon with three vertices.

### How to visually move a 'Shape'.
Call its 'move()' method and then redraw the Window it is attached to.

### How to label a 'Shape' object.
Create an instance of a Text object and place it accordingly.

### The mutable properties of the text in a 'Text' object.
- Text value.
- Color.
- Font face (and weight).

### The function and merits of using fonts.
There's no obvious mention of this in the book, here is a possible answer:

> A font or typeface is a set of characters designed with a consistent style. Fonts can make text easier to read, add visual appeal, and convey different tones.

The graphics library in the book provides a limited number of predefined fonts to choose from.

### The definition and function of the class 'Vector_ref' as implemented in the book.
A container with an interface similar to a vector, used to hold unnamed objects:
- 'push_back()' to add elements.
- 'size()' to retrieve the number of elements.
- 'operator[]' syntax to access elements.

It can be used to generate a large number of objects of any type, in this case derivatives of 'Shape' objects, in a for loop or similar.

It is also memory safe, see the answer below.

### On the topic of 'Dynamic Allocation' and 'Memory Leaks'.
The objects in a Vector_ref are **dynamically allocated**: Memory space is reserved as needed during runtime, rather than allocating a fixed amount upfront.

This could lead to memory leaks, but luckily the Vector_ref container has been designed to avoid that.

The book does not explore the concept of dynamic allocation in detail until later chapters.

### The difference between a 'Circle' and an 'Ellipse'.
A circle is a special case of an ellipse:
- In a circle all boundary points are placed at the same distance from its center. The center is the sole focus.
- In an ellipse the above may hold true but not always. Instead all points boundary points are placed at the same distance from two fixed points (foci).

### The outcome of drawing an 'Image' with an invalid file path.
An Image object pointing to a file that cannot be opened creates a 'Bad_image' object, which in turn draws a 'crossed-diagonals' box and a text informing the user that the given image could not be opened.

### How to mask an 'Image'.
```
Simple_window win{{10, 10}, 640, 320, "Test"};
Image i{{32, 32}, "test.jpg"};  // 200x200px image
i.set_mask({10, 10}, 180, 180); // Cut away 10px on each side
win.attach(i);
win.wait_for_button();
```
