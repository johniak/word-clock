import board
import neopixel




"""
Clock Display Hardware Abstraction Layer

Display letters and indexes
131 ITLISASTHPMA 120
108 ACFIFTEENDCO 119
107 TWENTYFIVEXW 096
084 THIRTYXTENXW 095
083 MINUTESETOUR 072
060 PASTORUFOURT 071
059 SEVENXTWELVE 048
036 NINEFIVECTWO 047
035 EIGHTFELEVEN 024
012 SIXTHREEONEG 023
011 TENSEZOCLOCK 000
"""
class ClockDisplayHAL:
    WIDTH = 12
    HEIGHT = 11
    NUM_LEDS = WIDTH * HEIGHT

    WORDS_TO_LEDS = {
        "HOUR_1": (20, 22),
        "HOUR_2": (45, 47),
        "HOUR_3": (15, 19),
        "HOUR_4": (67, 70),
        "HOUR_5": (40, 43),
        "HOUR_6": (12, 14),
        "HOUR_7": (55, 59),
        "HOUR_8": (29, 35),
        "HOUR_9": (36, 39),
        "HOUR_10": (9, 11),
        "HOUR_11": (24, 29),
        "HOUR_12": (48, 53),
        "OCLOCK": (0, 5),
        "PAST": (60, 63),
        "TO": (63, 64),
        "MINUTES": (77, 83),
        "THIRTY": (84, 89),
        "TWENTY": (102, 107),
        "TWENTYFIVE": (98, 107),
        "FIVE": (98, 101),
        "TEN": (91, 93),
        "FIFTEEN": (110, 116),
        "IS": (127, 128),
        "IT": (130, 131),
    }

    def __init__(self, board_pin, brightness):
        self.pixels = neopixel.NeoPixel(getattr(board, board_pin), self.NUM_LEDS, brightness=brightness, auto_write=False)

    def display_word(self, word, color):
        start, end = ClockDisplayHAL.WORDS_TO_LEDS[word]
        for i in range(start, end + 1):
            self.pixels[i] = color

    def cartesian_to_word_clock_led_strip_index(self, x, y):
        if y % 2 == 0:
            row_index = ClockDisplayHAL.NUM_LEDS - (y * ClockDisplayHAL.WIDTH)
            index = row_index - (x + 1)
        else:
            row_index = ClockDisplayHAL.NUM_LEDS - ((y + 1) * ClockDisplayHAL.WIDTH)
            index = row_index + x
        if index < 0 or index >= ClockDisplayHAL.NUM_LEDS:
            raise ValueError(f"Invalid x={x}, y={y}. Hardware only supports x=0-11, y=0-10")
        return index

    def set_pixel(self, x, y, color, width=12):
        index = self.cartesian_to_word_clock_led_strip_index(x, y)
        self.pixels[index] = color

    def clear_pixels(self, show=True):
        self.pixels.fill((0, 0, 0))
        if show:
            self.pixels.show()

    def show(self):
        self.pixels.show()
