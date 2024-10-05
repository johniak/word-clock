import argparse
import time
from clock_display_hal import ClockDisplayHAL
from word_clock import WordClock


# Color definitions


def main(pin, brightness, gif_path):
    clock_display_hal = ClockDisplayHAL(pin, brightness)
    word_clock = WordClock(clock_display_hal, gif_path)

    try:
        while True:
            word_clock.display_time()
            time.sleep(10)
    except KeyboardInterrupt:
        clock_display_hal.clear_pixels()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Run the Word Clock.")
    parser.add_argument("--pin", type=str, required=True, help="The PIN number for the clock display.")
    parser.add_argument("--brightness",
                        type=float,
                        required=False, help="The brightness of the clock display.",
                        default=0.05)
    parser.add_argument("--gif", type=str, required=False, help="The path to the GIF image.")
    args = parser.parse_args()
    main(args.pin, args.brightness, args.gif)
