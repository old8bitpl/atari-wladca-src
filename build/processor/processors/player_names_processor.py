#!/usr/bin/python3

from processor.core import BuildOutput, load_text_file


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
            c_converted = self.convert_character(c)
            converted_player_name.append(c_converted)

        return converted_player_name

    @staticmethod
    def convert_character(c):
        # 0x00 - 0x1f -> 0x40 - 0x5f
        # 0x20 - 0x3f -> 0x00 - 0x1f
        # 0x40 - 0x5f -> 0x20 - 0x3f
        # 0x60 - 0x7f -> 0x60 - 0x7f
        c = c & 0x7f
        if c < 32:
            return c + 0x40
        if c < 64:
            return c - 0x20
        if c < 96:
            return c - 0x20
        return c
