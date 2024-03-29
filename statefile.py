Import("env")
import os, glob

header = '''// Auto generated by statefile.py
#pragma once
const char *const STATE_FILE_JSON = R"json(#FILE)json";'''


def test(node):
    json = ""
    with open("src/state.json") as file:
        json = file.read().replace("\n", "")  # .replace(" ", "")
    with open("src/StateFile.h", "w") as file:
        file.write(header.replace("#FILE", json))
    return node


env.AddBuildMiddleware(test, "*/src/main.cpp")
