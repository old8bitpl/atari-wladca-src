#!/usr/bin/python3

from processor.core import BuildOutput, GmSrcFileProcessor


class BattleGraphProcessor(GmSrcFileProcessor):

    def __init__(self, filename, offset):
        super().__init__(filename, offset)

    def process(self, output: BuildOutput):
        super().process(output)

        # move image 2 lines up = drop first 2 lines, add 2 empty lines at the end
        for line in range(23):
            for i in range(40):
                sadr = self.offset + 1024 + 2 * 40 + 40 * line + i
                dadr = self.offset + 1024 + 40 * line + i
                d = output.get_byte(sadr)
                output.put_byte(dadr, d)

        # clean last 2 lines
        for i in range(80):
            dadr = self.offset + 1024 + 23 * 40 + i
            output.put_byte(dadr, 0x00)
