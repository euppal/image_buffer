# image_buffer

image_buffer is a very simple library for producing images which I have found very useful to myself - and hopefully to others. As an example, my custom grapher tool uses it to graph.

> my custom grapher tool. source may be uploaded here.
![Grapher tool graphing](https://github.com/euppal/image_buffer/blob/images/grapher-tool-example.png)

As of right now, image_buffer supports two file types: `.ppm` and `.pgm`, documentation of which can be found [here](http://netpbm.sourceforge.net/doc/ppm.html) and [here](http://netpbm.sourceforge.net/doc/pgm.html) respectively. Only the 1 byte versions are supported.

The implementation of these two modes involves the `enum image_format` and its cases `image_format_grayscale` and `image_format_rgb`. Alongside this mode (specified during initialization) you must also use the appropriate drawing functions (`write_rgb_pixel`, `write_grayscale_region`, etc).

### Simple Tutorial

In this example you will create a crude and basic truck. Begin by allocating an image buffer.

```c
#define alloc_struct(name, type) struct type* name = (struct type*)malloc(sizeof(struct type))
alloc_struct(image, image_buffer);
```

...and as always, pair this with a call to`free`.

```c
free(image);
```

Now, initialize the image with `init_buffer`. The first parameter is a pointer to the image, the second and third are the width and height of the image, and the fourth is the mode. We will make ours 512 pixels wide and 256 pixels high. We will also use grayscale mode.

```c
init_buffer(image, 512, 256, image_format_grayscale);
```

Now we can begin drawing. Let's draw the main body of the truck. To do this, we will use the functions `pixel_cursor` and `write_grayscale_region`.

```c
pixel_cursor(image, 64, 64);
write_grayscale_region(image, 255, 320, 192);
```

What's happening here? Well, `pixel_cursor` (red arrow) moves the "pixel cursor" around in the image. In this case, we move it to `(64, 64)`. Then we fill a region with white to `(320, 192)` using `write_grayscale_region`.

![Diagram](https://github.com/euppal/image_buffer/blob/images/tutorial-1.png)

With the body out of the way, we can begin to draw the front. The pipeline is very similar to the body: simply move the pixel cursor and write a region.

```c
pixel_cursor(image, 320, 192);
write_grayscale_region(image, 255, 448, 128);
```

![Diagram](https://github.com/euppal/image_buffer/blob/images/tutorial-2.png)

Afterwards, we can draw the circles. To do so we will need to use `write_grayscale_circle`, which draws a circle given a radius out from the pixel cursor.

```c
pixel_cursor(image, 112, 64);
write_grayscale_circle(image, 128, 32);
pixel_cursor(image, 400, 64);
write_grayscale_circle(image, 128, 32);
```

We supplied a different intensity value, `128`, to distinguish the wheels from the body.

Finally, we can save the image to disk and then free the contents of the image (before we `free` it). These three lines are all you need.

```c
save_buffer(image, "Truck.ppm");
system("open Truck.ppm");
free_buffer(image);
```

When you run and build you see this:

![Diagram](https://github.com/euppal/image_buffer/blob/images/tutorial-truck.png)

Congratulations, you have done it! Below is the complete source code.

```c
#include "image_buffer.h"
#define alloc_struct(name, type) struct type* name = (struct type*)malloc(sizeof(struct type))

int main() {
    alloc_struct(image, image_buffer);
    init_buffer(image, 512, 256, image_format_grayscale);

    // body
    pixel_cursor(image, 64, 64);
    write_grayscale_region(image, 255, 320, 192);

    // front
    pixel_cursor(image, 320, 192);
    write_grayscale_region(image, 255, 448, 128);

    // wheels
    pixel_cursor(image, 112, 64);
    write_grayscale_circle(image, 128, 32);
    pixel_cursor(image, 400, 64);
    write_grayscale_circle(image, 128, 32);

    save_buffer(image, "Truck.ppm"); system("open Truck.ppm");
    free_buffer(image);
    free(image);
}
```
