#!/usr/bin/python3

from processor.core import BuildOutput, SrcFileProcessor


class AllianceGraphProcessor(SrcFileProcessor):

    def __init__(self, filename, offset):
        super().__init__(filename, offset)

    def process(self, output: BuildOutput):
        input_data = super().process(output)

        # picture data
        chargen = input_data[0: 1024]
        picture = input_data[1024: 2048-5]
        colours = input_data[2048: 2048+5]

        # new picture and new chargen
        game_npict_mapping = {0: 3, 1: 0, 2: 2, 3: 1}
        new_chargen = [0x00] * 1024
        new_picture = [0x1f] * (1024 - 5)

        for npict in range(4):
            game_npict = game_npict_mapping[npict]
            dst_char_no = 32 * game_npict
            for y in range(6):
                for x in range(5):
                    src_pic_i = 4 + (9 * game_npict) + (40 * y) + x
                    src_char = picture[src_pic_i] & 0x7f
                    for char_i in range(8):
                        src_char_i = (8 * src_char) + char_i
                        dst_char_i = (8 * dst_char_no) + char_i
                        new_chargen[dst_char_i] = chargen[src_char_i]
                    dst_new_pic_i = 360 + 7 + (40 * y) + (7 * npict) + x
                    new_picture[dst_new_pic_i] = dst_char_no
                    dst_char_no += 1

        new_colours = [c for c in colours]

        data = new_chargen + new_picture + new_colours
        output.put(self.offset, data)

        return input_data
