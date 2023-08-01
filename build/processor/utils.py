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


def get_current_repo():
    return git.Repo(search_parent_directories=True)


def get_current_git_sha(repo):
    return repo.head.object.hexsha


def get_current_git_branch_name(repo):
    return repo.active_branch.name


def get_current_tag_name(repo):
    return next((tag for tag in repo.tags if tag.commit == repo.head.commit), None)


def get_version_line(defined_version : str):
    repo = get_current_repo()
    current_tag_name = get_current_tag_name(repo)

    if defined_version:
        version = defined_version
    elif current_tag_name:
        version = "{}".format(current_tag_name)
    else:
        current_branch_name = get_current_git_branch_name(repo)
        current_sha = get_current_git_sha(repo)
        version = "{}/{}".format(current_branch_name, current_sha)

    version_adjusted = version[0:40]
    version_formatted = " " * (40 - len(version_adjusted)) + version_adjusted
    return convert_ascii_txt_to_screen_arr(version_formatted)
