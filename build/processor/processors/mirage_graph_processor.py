#!/usr/bin/python3

from processor.core import BuildOutput, SrcFileProcessor


class MirageGraphProcessor(SrcFileProcessor):

    def __init__(self, filename, offset):
        super().__init__(filename, offset)

    def process(self, output: BuildOutput):
        input_data = super().process(output)

        # Mirage pic extract (skip first 8 lines, then load 24 lines)
        fr = 8 * 40
        to = fr + 24 * 40
        data = input_data[fr: to]
        output.put(self.offset, data)
