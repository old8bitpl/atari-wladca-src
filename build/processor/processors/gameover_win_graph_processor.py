#!/usr/bin/python3

from processor.core import BuildOutput, SrcFileProcessor


class GameOverWinGraphProcessor(SrcFileProcessor):

    def __init__(self, filename, offset):
        super().__init__(filename, offset)

    def process(self, output: BuildOutput):
        input_data = super().process(output)

        # Game over win pic extract (skip first one, then load 191 lines)
        fr = 40
        to = fr + 192 * 40
        data = input_data[fr: to]
        output.put(self.offset, data)
