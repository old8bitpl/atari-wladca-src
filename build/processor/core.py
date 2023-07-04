#!/usr/bin/python3


class BuildOutput:
    def __init__(self, size=65536):
        self.buf = bytearray([0] * size)

    def put(self, offset, src):
        self.buf[offset: offset + len(src)] = src

    def put_byte(self, offset, byte):
        self.buf[offset] = byte

    def get_byte(self, offset):
        return self.buf[offset]

    def export(self, filename):
        with open(filename, "wb") as file:
            file.write(self.buf)


class BinOutput:
    def __init__(self, build_output: BuildOutput, moverom, movepage6to9):
        self.bin_buf = self._build(build_output.buf, moverom, movepage6to9)

    def export(self, filename):
        with open(filename, "wb") as file:
            file.write(bytearray(self.bin_buf))

    @staticmethod
    def _build(build_output, moverom, movepage6to9):

        # mem to copy under ROM: 0xc000..0xcfff + 0xd800..0xffff
        bin_buf = [0xff, 0xff, 0x00, 0x80, 0xff, 0xb7]
        bin_buf.extend(build_output[0xc000: 0xd000])
        bin_buf.extend(build_output[0xd800:])

        # add moverom (incl. 0x2e2..0x2e3, w/o header 0xff, 0xff)
        bin_buf.extend(moverom)

        # mem: 0x0a00..0xbfff
        bin_buf.extend([0x00, 0x0a, 0xff, 0xbf])
        bin_buf.extend(build_output[0x0a00: 0xc000])

        # mem: 0x0900..0x09ff
        bin_buf.extend([0x00, 0x06, 0xff, 0x06])
        bin_buf.extend(build_output[0x0900: 0x0a00])

        # add movepage6to9 (incl. 0x2e2..0x2e3, w/o header 0xff, 0xff)
        bin_buf.extend(movepage6to9)

        # run
        bin_buf.extend([0xe0, 0x02, 0xe1, 0x02])
        bin_buf.extend(build_output[0x2e0: 0x2e2])

        return bin_buf


class SrcFileProcessor:

    def __init__(self, filename, offset):
        self.filename = filename
        self.offset = offset

    def process(self, output: BuildOutput):
        return load_binary_file(self.filename)


class DataSrcFileProcessor(SrcFileProcessor):

    def __init__(self, filename, offset):
        super().__init__(filename, offset)

    def process(self, output):
        input_data = super().process(output)

        # data
        output.put(self.offset, input_data)


class BinSrcFileProcessor(SrcFileProcessor):

    def __init__(self, filename):
        super().__init__(filename, None)

    def process(self, output: BuildOutput):
        input_data = super().process(output)

        input_data_index = 0
        input_data_len = len(input_data)

        # header check
        header1 = self._read_byte(input_data, input_data_index, input_data_len)
        input_data_index += 1
        header2 = self._read_byte(input_data, input_data_index, input_data_len)
        input_data_index += 1
        if header1 != 0xff or header2 != 0xff:
            raise Exception("Binary file '{}' error: no header (ff, ff)".format(self.filename))

        while True:
            block_from_lsb = self._read_byte(input_data, input_data_index, input_data_len, True)
            input_data_index += 1
            if block_from_lsb is None:
                break

            block_from_msb = self._read_byte(input_data, input_data_index, input_data_len)
            input_data_index += 1

            block_to_lsb = self._read_byte(input_data, input_data_index, input_data_len)
            input_data_index += 1

            block_to_msb = self._read_byte(input_data, input_data_index, input_data_len)
            input_data_index += 1

            block_from = 256 * block_from_msb + block_from_lsb
            block_to = 256 * block_to_msb + block_to_lsb
            if block_from > block_to:
                raise Exception("Binary file '{}' error: block_from > block_to".format(self.filename))

            for i in range(block_from, block_to + 1):
                data_byte = self._read_byte(input_data, input_data_index, input_data_len)
                input_data_index += 1
                output.put_byte(i, data_byte)

    def _read_byte(self, input_data, input_data_index, input_data_len, can_terminate_processing_file=False):
        if input_data_index == input_data_len:
            if can_terminate_processing_file:
                return None
            raise Exception("Binary file '{}' error: insufficient data".format(self.filename))

        return input_data[input_data_index]


class GmSrcFileProcessor(SrcFileProcessor):

    def __init__(self, filename, offset):
        super().__init__(filename, offset)

    @staticmethod
    def fill_data(input_data, output, offset):
        # picture data
        chargen = input_data[0: 1024]
        picture = input_data[1024: 2048-5]
        colours = input_data[2048: 2048+5]
        data = chargen + picture + colours
        output.put(offset, data)

    def process(self, output):
        input_data = super().process(output)

        GmSrcFileProcessor.fill_data(input_data, output, self.offset)

        return input_data


def load_binary_file(filename: str, file_length=65536):
    with open(filename, mode="rb") as file:
        return file.read(file_length)


def load_text_file(filename: str):
    with open(filename, mode="rt") as file:
        return [line.rstrip() for line in file]
