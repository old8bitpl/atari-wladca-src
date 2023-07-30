#!/usr/bin/python3

import git


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


def convert_ascii_txt_to_screen_arr(txt):
    converted_txt_arr = []
    for c in txt.upper():
        c_converted = convert_character_atascii_to_screen(c)
        converted_txt_arr.append(c_converted)
    return converted_txt_arr


def get_current_git_sha():
    repo = git.Repo(search_parent_directories=True)
    return repo.head.object.hexsha


def get_current_git_branch_name():
    repo = git.Repo(search_parent_directories=True)
    return repo.active_branch.name


def get_version_line():
    branch_name = get_current_git_branch_name()
    sha = get_current_git_sha()

    return convert_ascii_txt_to_screen_arr("{}/{}".format(branch_name, sha))[0:40]
