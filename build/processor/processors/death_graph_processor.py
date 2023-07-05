#!/usr/bin/python3

from processor.core import BuildOutput, SrcFileProcessor


class DeathGraphProcessor(SrcFileProcessor):

    def __init__(self, filename, offset):
        super().__init__(filename, offset)

    def process(self, output: BuildOutput):
        input_data = super().process(output)

        # extract from chargen (first 0x118 bytes)
        for i in range(0x118):
            sadr = i
            dadr = self.offset + i
            d = input_data[sadr]
            output.put_byte(dadr, d)

        # extract from pic
        for line in range(8):
            for i in range(16):
                sadr = 0x4a0 + line * 40 + 11 + i
                dadr = self.offset + 0x118 + line * 16 + i
                d = input_data[sadr]
                output.put_byte(dadr, d)
