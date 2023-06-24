#!/usr/bin/python3

from processor.core import BuildOutput, SrcFileProcessor, GmSrcFileProcessor


class TournamentGraphsProcessor:

    def __init__(self, shield_filename1, shield_filename2, shield_filename3,
                 shield_offset, shield_phases_offset, flag_phases_offset):
        self.shield_filename1 = shield_filename1
        self.shield_filename2 = shield_filename2
        self.shield_filename3 = shield_filename3
        self.shield_offset = shield_offset
        self.shield_phases_offset = shield_phases_offset
        self.flag_phases_offset = flag_phases_offset

    def process(self, output: BuildOutput):

        # tournament pic + chargen
        shield_input1_orig = SrcFileProcessor(self.shield_filename1, None).process(None)
        shield_input1 = [d for d in shield_input1_orig]
        # clean zoom window
        for y in range(4):
            for x in range(4):
                shield_input1[1024 + 41 + 40 * y + x] = 0
        GmSrcFileProcessor.fill_data(shield_input1, output, self.shield_offset)

        # shield phases
        TournamentGraphsProcessor.fill_shield_data(shield_input1, output, self.shield_phases_offset + 0x00)

        shield_input2 = TournamentGraphsProcessor.get_data_file(self.shield_filename2)
        TournamentGraphsProcessor.fill_shield_data(shield_input2, output, self.shield_phases_offset + 0x80)

        shield_input3 = TournamentGraphsProcessor.get_data_file(self.shield_filename3)
        TournamentGraphsProcessor.fill_shield_data(shield_input3, output, self.shield_phases_offset + 0x100)

        # flag phases
        for phase in range(12):
            for char in range(2):
                for i in range(8):
                    src_i = 0x805 + 46 * 12 * 8 + 96 * char + 8 * phase + i
                    dst_i = self.flag_phases_offset + 16 * phase + 8 * char + i
                    d = shield_input1[src_i]
                    output.put_byte(dst_i, d)

    @staticmethod
    def get_data_file(filename):
        data_orig = SrcFileProcessor(filename, None).process(None)
        return [d for d in data_orig]

    @staticmethod
    def fill_shield_data(input_data, output, shield_phase_offset):
        data = input_data[80 * 8: 96 * 8]
        output.put(shield_phase_offset, data)
