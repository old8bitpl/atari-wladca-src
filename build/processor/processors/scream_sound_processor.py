#!/usr/bin/python3

from processor.core import BuildOutput, SrcFileProcessor


class ScreamSoundProcessor(SrcFileProcessor):

    def __init__(self, filename, offset):
        super().__init__(filename, offset)

    def process(self, output: BuildOutput):
        input_data = super().process(output)

        # Scream sound extract (read every second byte: 1786 bytes in total)
        data = []
        for i in range(1786):
            data.append(input_data[i * 2])

        output.put(self.offset, data)
