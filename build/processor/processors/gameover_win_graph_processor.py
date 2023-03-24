#!/usr/bin/python3

from processor.core import BuildOutput, SrcFileProcessor


class GameOverWinGraphProcessor(SrcFileProcessor):

    def __init__(self, filename, offset):
        super().__init__(filename, offset)

    def process(self, output: BuildOutput):
        input_data = super().process(output)

        # Game over win pic extract (load 191 lines, then skip last one)
        fr = 0
        to = fr + 191 * 40
        data = input_data[fr: to]
        output.put(self.offset, data)
