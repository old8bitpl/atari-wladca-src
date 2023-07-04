#!/usr/bin/python3

from processor.core import BuildOutput, load_text_file
from processor.utils import convert_character_atascii_to_screen


class PlayerNamesProcessor:

    def __init__(self, filename, offset):
        self.filename = filename
        self.offset = offset

    def process(self, output: BuildOutput):
        data = [0x00] * 32
        player_names_orig = load_text_file(self.filename)
        for p in range(4):
            converted_player_name = self.convert_player_name(player_names_orig[p])

            for i in range(min(5, len(converted_player_name))):
                data[8 * p + i] = converted_player_name[i]

        output.put(self.offset, data)

    def convert_player_name(self, player_name: str):
        converted_player_name = []
        for c in player_name:
            c_converted = convert_character_atascii_to_screen(c)
            converted_player_name.append(c_converted)

        return converted_player_name

