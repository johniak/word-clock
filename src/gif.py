from PIL import Image
import time
from clock_display_hal import ClockDisplayHAL


def update_led_pixels(gif_pixels, new_size, clock_display_hal):
    for y in range(new_size[1]):
        for x in range(new_size[0]):
            r, g, b = gif_pixels[x, y]
            clock_display_hal.set_pixel(x, y, (r, g, b))


def display_gif(gif_path, clock_display_hal, display_gif_duration=4):
    gif_path = gif_path
    img = Image.open(gif_path)
    new_size = (ClockDisplayHAL.WIDTH, ClockDisplayHAL.HEIGHT)
    start_time = time.time()
    while time.time() < start_time + display_gif_duration:
        try:
            frame = img.resize(new_size).convert('RGB')
            gif_pixels = frame.load()

            update_led_pixels(gif_pixels, new_size, clock_display_hal)
            clock_display_hal.show()
            time.sleep(0.1)
            img.seek(img.tell() + 1)

        except EOFError:
            img.seek(0)
