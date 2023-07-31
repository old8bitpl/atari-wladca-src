#!/usr/bin/python3

from processor.core import BuildOutput, load_text_file
from processor.utils import convert_ascii_txt_to_screen_arr


class PlayerNamesProcessor:

    def __init__(self, filename, offset):
        self.filename = filename
        self.offset = offset

    def process(self, output: BuildOutput):
        data = [0x00] * 32
        player_names_orig = load_text_file(self.filename)
        for p in range(4):
            converted_player_name = convert_ascii_txt_to_screen_arr(player_names_orig[p])

            for i in range(min(5, len(converted_player_name))):
                data[8 * p + i] = converted_player_name[i]

        output.put(self.offset, data)

