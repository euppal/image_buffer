# image_buffer

image_buffer is a very simple library for producing images which I have found very useful to myself - and hopefully to others. As an example, my custom grapher tool uses it to graph.

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
