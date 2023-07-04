#!/usr/bin/python3

from processor.core import BuildOutput, load_text_file
from processor.utils import convert_character_atascii_to_screen


class CountryNamesProcessor:

    def __init__(self, filename, namkstab_offset, dochtab_offset, shieldtab_offset, flagtab_offset,
                 neartab_offset, tertab_offset):
        self.filename = filename
        self.namkstab_offset = namkstab_offset
        self.dochtab_offset = dochtab_offset
        self.shieldtab_offset = shieldtab_offset
        self.flagtab_offset = flagtab_offset
        self.neartab_offset = neartab_offset
        self.tertab_offset = tertab_offset

    def process(self, output: BuildOutput):
        kn = 0
        countries_src = load_text_file(self.filename)

        output.put(self.neartab_offset, [0xff] * 256)
        output.put(self.tertab_offset, [0xff] * 928)

        for country_line in countries_src:
            if country_line.startswith("#"):
                continue

            (_, country_name_txt, income_txt, shield_location_txt, flag_location_txt, neighbours_txt, terrain_txt)\
                = country_line.split("|")

            income = int(income_txt.strip())
            sadr = self.dochtab_offset + kn
            output.put_byte(sadr, income)

            country_name_with_income = "{} ({})".format(country_name_txt.strip(), income)
            country_name = (self.convert_country_name(country_name_with_income))
            country_name.append(0xff)
            sadr = self.namkstab_offset + 16 * kn
            output.put(sadr, country_name)

            shield_location = self.process_location(shield_location_txt)
            shield_location_lo = shield_location % 256
            shield_location_hi = int(shield_location / 256)
            sadr = self.shieldtab_offset + 2 * kn
            output.put(sadr, (shield_location_lo, shield_location_hi))

            flag_location = self.process_location(flag_location_txt)
            flag_location_lo = flag_location % 256
            flag_location_hi = int(flag_location / 256)
            sadr = self.flagtab_offset + 2 * kn
            output.put(sadr, (flag_location_lo, flag_location_hi))

            neighbours = self.process_numbers(neighbours_txt)
            neighbours.extend([0xff] * (8 - len(neighbours)))
            sadr = self.neartab_offset + 8 * kn
            output.put(sadr, neighbours)

            terrains = self.process_locations(terrain_txt)
            for terrain_offset in terrains:
                sadr = self.tertab_offset + terrain_offset
                output.put_byte(sadr, kn)

            kn = kn + 1

    def process_locations(self, locations_str: str):
        data = []
        for location_str in locations_str.split(";"):
            data.append(self.process_location(location_str))
        return data

    def process_location(self, location_str: str):
        (_, tmp) = location_str.split("(")
        (loc_str, _) = tmp.split(")")
        (x, y) = loc_str.split(",")
        return 40 * int(y) + int(x)

    def process_numbers(self, numbers_str: str):
        data = []
        for number_str in numbers_str.split(";"):
            data.append(int(number_str.strip()))
        return data

    def convert_country_name(self, country_name_str: str):
        converted_country_name = []
        for c in country_name_str:
            c_converted = convert_character_atascii_to_screen(c)
            converted_country_name.append(c_converted)

        return converted_country_name
