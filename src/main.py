import time
import board
import neopixel
import random
from datetime import datetime
from gif import display_gif

# Color definitions
COLORS = [
    (255, 0, 0),  # Red
    (0, 255, 0),  # Green
    (0, 0, 255),  # Blue
    (255, 255, 0),  # Yellow
    (255, 0, 255),  # Magenta
    (0, 255, 255),  # Cyan
    (255, 255, 255),  # White
    (165, 42, 42),  # Brown
]

# Neopixel configuration
LED_PIN = board.D12
NUM_LEDS = 132
BRIGHTNESS = 0.04

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
    "FIFTEEN": (110, 116),
    "IS": (127, 128),
    "IT": (130, 131),
}


class WordClock:
    def __init__(self, pixels):
        self.pixels = pixels
        self.last_hour = -1
        self.all_last_highlighted_words = ""

    def clear_pixels(self):
        self.pixels.fill((0, 0, 0))

    def highlight_word(self, word, color=(255, 255, 255)):
        if word in WORDS_TO_LEDS:
            start_index, end_index = WORDS_TO_LEDS[word]
            for index in range(start_index, end_index + 1):
                self.pixels[index] = color

    def get_minutes_word(self, minute):
        if minute < 5:
            return "OCLOCK"
        elif minute < 10:
            return "FIVE"
        elif minute < 20:
            return "FIFTEEN"
        elif minute < 25:
            return "TWENTY"
        elif minute < 30:
            return "TWENTYFIVE"
        elif minute < 35:
            return "THIRTY"
        elif minute < 40:
            return "TWENTYFIVE"
        elif minute < 45:
            return "TWENTY"
        elif minute < 50:
            return "FIFTEEN"
        elif minute < 55:
            return "TEN"
        else:
            return "FIVE"

    def get_random_color(self):
        return random.choice(COLORS)

    def display_time(self):
        now = datetime.now()
        hour = now.hour % 12 or 12  # Ensure hour is 1-12
        minute = now.minute

        if hour != self.last_hour:
            if minute == 0:
                display_gif(self.pixels)
                self.clear_pixels()
                self.last_hour = hour

        self.highlight_word("IT", self.get_random_color())
        self.highlight_word("IS", self.get_random_color())
        all_highlighted_words = "ITIS"

        if minute < 5:
            self.highlight_word("OCLOCK", self.get_random_color())
            all_highlighted_words = "OCLOCK"
        elif minute < 35:
            self.highlight_word("PAST", self.get_random_color())
            all_highlighted_words += "PAST"
            self.highlight_word("MINUTES", self.get_random_color())
            all_highlighted_words += "MINUTES"
        else:
            self.highlight_word("TO", self.get_random_color())
            all_highlighted_words += "TO"
            self.highlight_word("MINUTES", self.get_random_color())
            all_highlighted_words += "MINUTES"
            hour = (hour + 1) % 12 or 12  # Adjust hour for "to" display

        hour_word = f"HOUR_{hour}"
        self.highlight_word(self.get_minutes_word(minute), self.get_random_color())
        all_highlighted_words += self.get_minutes_word(minute)
        self.highlight_word(hour_word, self.get_random_color())
        all_highlighted_words += hour_word

        if self.all_last_highlighted_words != all_highlighted_words:
            self.pixels.show()
            self.all_last_highlighted_words = all_highlighted_words


if __name__ == "__main__":
    pixels = neopixel.NeoPixel(LED_PIN, NUM_LEDS, brightness=BRIGHTNESS, auto_write=False)
    word_clock = WordClock(pixels)
    try:
        while True:
            word_clock.display_time()
            time.sleep(10)
    except KeyboardInterrupt:
        word_clock.clear_pixels()
