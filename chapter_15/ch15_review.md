# Chapter 15 - Review

### The definition of a 'function of one argument / variable'

A function that takes exactly one external argument to calculate and produce a single output. The author does not discuss function purity, but technically it may not depend on any external state beyond the function argument (No global values, etc).

### The types of data best represented as continuous lines vs. discrete points
A continuous line should be considered if the data contains a variable that is a direct function of another variable, such as a series of <Year, Steel production> value pairs.

The change in value between the plotted points reflects some kind of trend or relationship - more examples:
- Daily temperature readings
- Supply and demand curves
- Heart rate vs. exercise intensity

Conversely, data such as the \<Gross domestic product per person\> mapped against the \<Population of country\> is more appropriately plotted as unconnected points.

In such cases, the values between points are not that meaningful. Instead, each reading may be seen as a distinct event or measurement - more examples:
- Individual student test scores
- Items sold per product category
- Medal count by country

### The function or mathematic formula that defines a slope
The slope measures the change in **Y** for each plotted **X**.

The example used in the book is:` double slope(double x) { return x / 2; }`.

Which can be equally seen as: `double slope(double x) { return x * 0.5; }`

Where the slope between points is **0.5**. This is a linear function, the slope is constant.

Furthermore, the point where such a function crosses the Y axis can be controlled by an additional term called the "y-intercept".
```
double slope(double x) { return <Slope value> * x + <Y-Intercept value>; }
```

### The properties of a 'parabola'
A symmetrical U-shaped curve that represents a quadratic function.

The example used in the book is:
```
double quadratic(double x) { return x * x; };
```

The author does not really expand upon the subject matter, at least not in chapter 15.

The more complete form of a common quadratic function is:
```
double parabola(double c) { return <Quadratic coefficient value> * x * x + <Linear coefficient> * x + <Y-Intercept coefficient>; }
```

The quadratic coefficient determines the width of the parabola, and whether it turns upward or downward.

The linear coefficient determines the placement of the axis of symmetry.

Much like for linear functions, the y-intercept controls where the parabola crosses the Y axis.

### The methodology for defining and drawing Y and X axes

At least for the initial example covered in the book, this process does not seem to be accurately described.

The following constants are used to initialize the graph(s):
```c++
constexpr int xmax = 600;      constexpr int ymax = 400;      // Bounds
constexpr int x_orig = xmax/2; constexpr int y_orig = ymax/2; // Graph origin
constexpr int r_min = -10;     constexpr int r_max = 11;      // # of units
constexpr int x_scale = 30;    constexpr int y_scale = 30;    // Unit size
// Initialize graph
Function s {one, r_min, r_max, {x_orig, y_orig}, n_points, x_scale, y_scale};
```

Note that the origin is in the middle of the screen, the scale factor which is essentially the unit size is 30.

Now, the X axis is initialized as follows:
```c++
constexpr int xlength = xmax – 40; // make axis a bit smaller than the window
constexpr int ylength = ymax – 40;
Axis x {Axis::x,Point{20, y_orig}, xlength, xlength/x_scale, "one notch == 1"};
```

This doesn't properly align the notches with the units, or the intervals, used to plot the function.

Axis objects always start and end with a notch, there's no offsetting or terminating the axis by say half a unit.

The X axis is initialized at `x=20`, but the closest unit point to that coordinate would be at:
```
int closest_unit_x = static_cast<int(x_orig - xscale * std::round((x_orig - 20) / xscale));
//                 = 30
```

So the X axis is off by 10 pixels.

The other issue is the distance between notches, this is determined by the width of the axis and the number of notches:
```
int axis_width = xlength;                   // xmax - 40 = 600 - 40 = 560
int num_notches = axis_width / xscale;      // 560 / 30 = 18
int notch_space = axis_width / num_notches; // 560 / 18 = 31
```

This means that the distance between notches is one pixel too wide.

There are times when a custom scale may be desired, but since the Axis objects are labelled "one notch == 1" this seems unlikely here.

Assuming the end goal is to create axes that align with the units of the plotted functions, this is the general workflow:
1. Create two instances of **Axis**, one by passing argument axis=Axis::x, the other axis=Axis::y.
2. Place them so that they intersect where the X and Y values of the plotted Function are at zero.
3. Ensure that the notches align with the 'units' (scaling factors) of the function being plotted.
4. Ensure that the space between notches are the same as the x and y 'units' (scaling factors)
5. Ensure that the axis dimensions so fit within the bounds of the window
6. Label the axes in a way that one can easily identify the distance between notches.
7. Color the axes in a way that separates them from the graphed data.

### The definition of default arguments
Initializers provided directly in the function or constructor signature (usually in the declaration) for parameters that can be **omitted by the caller**, allowing those parameters to assume the specified default values.

### The syntax for default arguments
The general form is:
```c++
<Return type> function_name(<Type> parameter_a,
                            <Type> parameter_b = <Default value A>,
                            <Type> parameter_c = <Default value B>);
```

Once a parameter has been given a default value, all trailing parameters must also have default values.

Example:
```c++
void message(const std::string& subject,
             const std::string& verb = "needs",
             int amount = 1,
             const std::string& object = "shot") {
	std::cout << subject << ' ' << verb << ' ' << amount << ' ' << object
	          << (amount != 1 ? "s" : "") << '\n';
}

int main() {
	message("He");                      // Prints "He needs 1 shot"
	message("She", "wants");            // Prints "She wants 1 shot"
	message("They", "get", 2);          // Prints "They get 2 shots"
	message("You", "give", 0, "shit");  // Prints "You give 0 shits"
}
```

### The benefits of using default arguments
It makes function calls less verbose but also eliminates the need for implementing multiple overloaded functions.

### The basics of "composing functions" (adding functions together)
Define a new single argument function that calls any number of functions (using the same input), and returns the sum of their combined output.
```c++
double sloping_cos(double x) {
	return std::cos(x) + slope(x);
}
```

### The methods used for coloring and labeling graphs
The **Axis** objects can be labeled upon initialization through their constructors.

Labels can be created for the actual Graphs by drawing separate **Text** objects and placing them accordingly.

Instances of **Function**, **Axis**, **Text**, and whatever Shape derivative is used to plot data, may be colored using **set_color()**.

### The meaning of a series "approximating" a function
Many functions, such as exponential functions, can be approximated by computing them as a series of terms, and calculating the sum of those terms:
```
e(x) = 1 + x + x^2/2! + x^3/3! + . . .
```
​Each additional term brings the approximation closer to the true value of the function, until computational limits (floating-point precision, overflow, underflow) start to cause errors.

Graphing a function directly using built-in functions (like **std::exp()**) usually avoids these issues.

### The reasons for sketching out a graph before coding it
Sketching the layout of a graph increases our understanding for the data and how to best represent it (Continuous lines, points, bar charts, etc.).

Also, planning and organizing labels, colors, and axes usually leads to better visuals and more clarity.

### The typical workflow for controlling the scale of graph inputw
1. Define the data ranges for x and y axes.
2. Set the graph dimensions in pixels.
3. Calculate scaling factors: `scale = available_pixels / data_range`
4. Use these scaling factors for plotting data and any drawing other graph-related objects (e.g. Axis or Text).

### The best way to avoid trial and error when scaling graph input
Refactor and separate all scaling calculations from other logic. The improved reusability and maintainability will reduce the risk of errors.

Use well-defined constants to feed into the various graph-related functions and objects.

### The reasons for preferring formatted over raw data
Using "just the numbers" seems simpler at first glace, but well-structured input usually leads to a better experience for both the programmer and user in the long run.

Some of the perks:
- Structured data is easier for humans to read and understand. It is often self-documenting and can provide context without the need of additional notes.
- The rules for parsing data are usually clearer, easier to implement and easier to troubleshoot.
- The format can be extended to include more information at a later stage.

### The common approach to planning graph layouts
- Determine data to display and elements to represent it: Axes, labels, different colored points/shapes for each data set.
- Decide element placement within the window, use coordinates and dimensions relative to the window or other objects rather than hard coded pixel values.
- Visualize the layout through a rough drawing or diagram (Used as a blueprint for the implementation, but can also be helpful in spotting issues such as overlaps or poor use of space)

### The essentials of expressing a planned layout in actual code
- Identify and define all the variables needed to implement the correct positioning and dimensions of the different objects.
- Refactor calculations such as scaling into separate helper functions / classes.
- Gradually add elements, making sure they use the same variables and helpers mentioned above.
- (Refactor into a dedicated setup function)

