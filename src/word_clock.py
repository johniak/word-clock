import random
from datetime import datetime
from gif import display_gif
from clock_display_hal import ClockDisplayHAL


class WordClock:
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

    def __init__(self, clock_display_hal,gif_path):
        self.last_hour = -1
        self.all_last_highlighted_words = ""
        self.clock_display_hal = clock_display_hal
        self.gif_path=gif_path

    def highlight_word(self, word, color=(255, 255, 255)):
        if word in ClockDisplayHAL.WORDS_TO_LEDS:
            self.clock_display_hal.display_word(word, color)

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
        return random.choice(WordClock.COLORS)

    def display_time(self):
        now = datetime.now()
        hour = now.hour % 12 or 12  # Ensure hour is 1-12
        minute = now.minute
        self.clock_display_hal.clear_pixels(show=False)
        if hour != self.last_hour and self.gif_path:
            if minute == 0:
                display_gif(self.gif_path,self.clock_display_hal)
                self.clock_display_hal.clear_pixels(show=False)
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
            self.clock_display_hal.show()
            self.all_last_highlighted_words = all_highlighted_words
