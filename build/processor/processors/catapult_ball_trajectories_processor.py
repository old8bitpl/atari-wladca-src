#!/usr/bin/python3

from processor.core import BuildOutput, SrcFileProcessor, load_text_file


class CatapultBallTrajectoriesProcessor(SrcFileProcessor):

    def __init__(self, filename, offset):
        super().__init__(filename, offset)

    def process(self, output: BuildOutput):
        lines = load_text_file(self.filename)

        n = 0
        for line in lines:
            data_tab_str = line.split(",")
            for i in range(len(data_tab_str)):
                sadr = self.offset + 128 * n + i
                d = int(data_tab_str[i])
                output.put_byte(sadr, d)
            n += 1
