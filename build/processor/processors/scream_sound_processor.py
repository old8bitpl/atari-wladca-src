#!/usr/bin/python3

from processor.core import BuildOutput, SrcFileProcessor


class ScreamSoundProcessor(SrcFileProcessor):

    def __init__(self, filename, offset):
        super().__init__(filename, offset)

    def process(self, output: BuildOutput):
        input_data = super().process(output)

        # Scream sound extract (read first 3572 bytes and convert them to 1786 bytes)
        # conversion: take 2 following input bytes (IBA, IBB) and produce result byte (RB):
        # RB3..RB0 = IBA7..IBA4 and RB7..RB4 = IBB7..IBB4
        data = []
        for i in range(1786):
            iba = input_data[i * 2]
            ibb = input_data[(i * 2) + 1]
            iba_h_nibble = iba & 0xf0
            ibb_h_nibble = ibb & 0xf0
            rb = iba_h_nibble >> 4 | ibb_h_nibble
            data.append(rb)

        output.put(self.offset, data)
