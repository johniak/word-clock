from PIL import Image
import time

NUM_LEDS = 12 * 11


def cartesian_to_neopixel(x, y, width=12):
    if y % 2 == 0:
        row_index = NUM_LEDS - ((y) * width)
        index = row_index - (x + 1)
    else:
        row_index = NUM_LEDS - ((y + 1) * width)
        index = row_index + x
    return index


def set_pixel(pixels, x, y, color, width=12):
    index = cartesian_to_neopixel(x, y, width)
    pixels[index] = color


def update_led_pixels(led_pixels, gif_pixels, new_size):
    for y in range(new_size[1]):
        for x in range(new_size[0]):
            r, g, b = gif_pixels[x, y]
            set_pixel(led_pixels, x, y, (r, g, b))


def display_gif(led_pixels):
    gif_path = "../heart-art.gif"
    img = Image.open(gif_path)
    new_size = (12, 11)

    display_time_of_gif = 4
    start_time = time.time()

    while time.time() < start_time + display_time_of_gif:
        try:
            frame = img.resize(new_size).convert('RGB')
            gif_pixels = frame.load()

            update_led_pixels(led_pixels, gif_pixels, new_size)
            led_pixels.show()
            time.sleep(0.1)
            img.seek(img.tell() + 1)

        except EOFError:
            img.seek(0)
