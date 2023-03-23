#!/usr/bin/python3


class BuildOutput:
    def __init__(self, size=65536):
        self.buf = bytearray([0] * size)

    def put(self, offset, src):
        self.buf[offset: offset + len(src)] = src

    def export(self):
        with open("export.dat", "wb") as file:
            file.write(self.buf)


class SrcFileProcessor:

    def __init__(self, filename, offset):
        self.filename = filename
        self.offset = offset

    def process(self, output):
        return load_binary_file(self.filename)


class GmSrcFileProcessor(SrcFileProcessor):

    def __init__(self, filename, offset):
        super().__init__(filename, offset)

    def process(self, output):
        input_data = super().process(output)

        # picture data
        chargen = input_data[0: 1024]
        picture = input_data[1024: 2048-5]
        colours = input_data[2048: 2048+5]
        data = chargen + picture + colours
        output.put(self.offset, data)

        return input_data


def load_binary_file(filename: str, file_length=65536):
    with open(filename, mode="rb") as file:
        return file.read(file_length)
