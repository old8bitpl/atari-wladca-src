#!/usr/bin/python3

def convert_character_atascii_to_screen(c):
    # 0x00 - 0x1f -> 0x40 - 0x5f
    # 0x20 - 0x3f -> 0x00 - 0x1f
    # 0x40 - 0x5f -> 0x20 - 0x3f
    # 0x60 - 0x7f -> 0x60 - 0x7f
    c = ord(c) & 0x7f
    if c < 0x20:
        return c + 0x40
    if c < 0x40:
        return c - 0x20
    if c < 0x60:
        return c - 0x20
    return c
