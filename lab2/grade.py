import subprocess
import sys
import os
import shutil
import logging
from typing import Tuple, List
import json
import datetime
import platform
import argparse


# exit if python2
if sys.version_info[0] < 3 and sys.version_info[1] < 7:
    print("This program requires Python 3.7. Please contact TA for help.")
    sys.exit(1)

standard_json = r"""{
    "name": "TA",
    "id": "TA",
    "time": "2022-03-23 16:54:50",
    "tests": [
        {
            "test": "command_test1",
            "stdin": "l\nq\n",
            "stdout": "> 1: This is a test file.\n2: We love OOP!\n3: 1 + 1 = 2\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "command_test2",
            "stdin": "list\nq\n",
            "stdout": "> 1: This is a test file.\n2: We love OOP!\n3: 1 + 1 = 2\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "command_test3",
            "stdin": "i 2 test3\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> 1: This is a test file.\n2: test3\n3: We love OOP!\n4: 1 + 1 = 2\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "command_test4",
            "stdin": "insert 2 test4\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> 1: This is a test file.\n2: test4\n3: We love OOP!\n4: 1 + 1 = 2\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "command_test5",
            "stdin": "i 2 test5\ni 3 test5\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> 1: This is a test file.\n2: test5\n3: test5\n4: We love OOP!\n5: 1 + 1 = 2\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "command_test6",
            "stdin": "e 2 test6\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> 1: This is a test file.\n2: test6\n3: 1 + 1 = 2\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "command_test7",
            "stdin": "edit 2 test6\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> 1: This is a test file.\n2: test6\n3: 1 + 1 = 2\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "command_test8",
            "stdin": "e 2 test8\ne 3 test8\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> 1: This is a test file.\n2: test8\n3: test8\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "command_test9",
            "stdin": "d 2\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> 1: This is a test file.\n2: 1 + 1 = 2\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "command_test10",
            "stdin": "delete 3\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> 1: This is a test file.\n2: We love OOP!\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "command_test11",
            "stdin": "d 1\nd 2\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> 1: We love OOP!\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "command_test12",
            "stdin": "i 1 test12\ne 2 test12\ni 3 test12\nd 3\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> 1: test12\n2: test12\n3: We love OOP!\n4: 1 + 1 = 2\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "command_test13",
            "stdin": "i 2 test13\ne 3 test13\nd 1\nw\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> 1: test13\n2: test13\n3: 1 + 1 = 2\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "test13\ntest13\n1 + 1 = 2\n",
            "other": "other"
        },
        {
            "test": "command_test14",
            "stdin": "i 2 test14\ne 3 test14\nd 1\nwrite\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> 1: test14\n2: test14\n3: 1 + 1 = 2\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "test14\ntest14\n1 + 1 = 2\n",
            "other": "other"
        },
        {
            "test": "command_test15",
            "stdin": "i 2 test15\ne 3 test15\nd 1\nw\nr\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> 1: test15\n2: test15\n3: 1 + 1 = 2\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "test15\ntest15\n1 + 1 = 2\n",
            "other": "other"
        },
        {
            "test": "command_test16",
            "stdin": "i 2 test16\ne 3 test16\nd 1\nw test/other.txt\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> 1: test16\n2: test16\n3: 1 + 1 = 2\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "test16\ntest16\n1 + 1 = 2\n"
        },
        {
            "test": "command_test17",
            "stdin": "i 2 test17\ne 3 test17\nd 1\nw test/other.txt\nr\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> 1: This is a test file.\n2: We love OOP!\n3: 1 + 1 = 2\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "test17\ntest17\n1 + 1 = 2\n"
        },
        {
            "test": "command_test18",
            "stdin": "i 2 test18\ne 3 test18\nd 1\nw test/other.txt\nr test/other.txt\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> 1: test18\n2: test18\n3: 1 + 1 = 2\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "test18\ntest18\n1 + 1 = 2\n"
        },
        {
            "test": "command_test19",
            "stdin": "i 2 test19\ne 3 test19\nd 1\nr\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> 1: This is a test file.\n2: We love OOP!\n3: 1 + 1 = 2\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "command_test20",
            "stdin": "i 2 test20\ne 3 test20\nd 1\nr test/other.txt\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> 1: other\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "command_test21",
            "stdin": "i 2 test21\ne 3 test21\nd 1\nw\nr test/other.txt\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> 1: other\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "test21\ntest21\n1 + 1 = 2\n",
            "other": "other"
        },
        {
            "test": "command_test22",
            "stdin": "i 2 test22\ne 3 test22\nd 1\nw\nr\nr test/other.txt\nl\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> \u001b[32mOK\n\u001b[0m> 1: other\n\u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "test22\ntest22\n1 + 1 = 2\n",
            "other": "other"
        },
        {
            "test": "error_test1",
            "stdin": "d 14\nq\n",
            "stdout": "> > ",
            "stderr": "\u001b[31mRuntime error\n\u001b[0m",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "error_test2",
            "stdin": "i 0 test2\nq\n",
            "stdout": "> > ",
            "stderr": "\u001b[31mRuntime error\n\u001b[0m",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "error_test3",
            "stdin": "i 14 test3\nq\n",
            "stdout": "> > ",
            "stderr": "\u001b[31mRuntime error\n\u001b[0m",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "error_test4",
            "stdin": "i 4 test4\nq\n",
            "stdout": "> \u001b[32mOK\n\u001b[0m> ",
            "stderr": "",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "error_test5",
            "stdin": "e 0 test5\nq\n",
            "stdout": "> > ",
            "stderr": "\u001b[31mRuntime error\n\u001b[0m",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "error_test6",
            "stdin": "e 14 test6\nq\n",
            "stdout": "> > ",
            "stderr": "\u001b[31mRuntime error\n\u001b[0m",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "error_test7",
            "stdin": "anycommand\nq\n",
            "stdout": "> > ",
            "stderr": "\u001b[31mInvalid command\n\u001b[0m",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "error_test8",
            "stdin": "r 9\nq\n",
            "stdout": "> > ",
            "stderr": "\u001b[31mRuntime error\n\u001b[0m",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "error_test9",
            "stdin": "r notexist.txt\nq\n",
            "stdout": "> > ",
            "stderr": "\u001b[31mRuntime error\n\u001b[0m",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "error_test10",
            "stdin": "e 9\nq\n",
            "stdout": "> > ",
            "stderr": "\u001b[31mInvalid command\n\u001b[0m",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        },
        {
            "test": "error_test11",
            "stdin": "e\nq\n",
            "stdout": "> > ",
            "stderr": "\u001b[31mInvalid command\n\u001b[0m",
            "content": "This is a test file.\nWe love OOP!\n1 + 1 = 2",
            "other": "other"
        }
    ]
}"""


build_dir = "build"
test_dir = "test"
# Executable based on system
if sys.platform == "win32":
    executable_name = f"{build_dir}/editor.exe"
else:
    executable_name = f"{build_dir}/editor"

result = {}

lines = [
    "This is a test file.",
    "We love OOP!",
    "1 + 1 = 2",
]

tests = [
    ("command_test1", ["l"]),
    ("command_test2", ["list"]),
    ("command_test3", ["i 2 test3", "l"]),
    ("command_test4", ["insert 2 test4", "l"]),
    ("command_test5", ["i 2 test5", "i 3 test5", "l"]),
    ("command_test6", ["e 2 test6", "l"]),
    ("command_test7", ["edit 2 test6", "l"]),
    ("command_test8", ["e 2 test8", "e 3 test8", "l"]),
    ("command_test9", ["d 2", "l"]),
    ("command_test10", ["delete 3", "l"]),
    ("command_test11", ["d 1", "d 2", "l"]),
    ("command_test12", ["i 1 test12", "e 2 test12", "i 3 test12", "d 3", "l"]),
    ("command_test13", ["i 2 test13", "e 3 test13", "d 1", "w", "l"]),
    ("command_test14", ["i 2 test14", "e 3 test14", "d 1", "write", "l"]),
    ("command_test15", ["i 2 test15", "e 3 test15", "d 1", "w", "r", "l"]),
    ("command_test16", ["i 2 test16", "e 3 test16",
                        "d 1", f"w {test_dir}/other.txt", "l"]),
    ("command_test17", ["i 2 test17", "e 3 test17",
                        "d 1", f"w {test_dir}/other.txt", "r", "l"]),
    ("command_test18", ["i 2 test18", "e 3 test18", "d 1",
                        f"w {test_dir}/other.txt", f"r {test_dir}/other.txt", "l"]),
    ("command_test19", ["i 2 test19", "e 3 test19", "d 1", "r", "l"]),
    ("command_test20", ["i 2 test20", "e 3 test20",
                        "d 1", f"r {test_dir}/other.txt", "l"]),
    ("command_test21", ["i 2 test21", "e 3 test21",
                        "d 1", "w", f"r {test_dir}/other.txt", "l"]),
    ("command_test22", ["i 2 test22", "e 3 test22",
                        "d 1", "w", "r", f"r {test_dir}/other.txt", "l"]),
    ("error_test1", ["d 14"]),
    ("error_test2", ["i 0 test2"]),
    ("error_test3", ["i 14 test3"]),
    ("error_test4", ["i 4 test4"]),
    ("error_test5", ["e 0 test5"]),
    ("error_test6", ["e 14 test6"]),
    ("error_test7", ["anycommand"]),
    ("error_test8", ["r 9"]),
    ("error_test9", ["r notexist.txt"]),
    ("error_test10", ["e 9"]),
    ("error_test11", ["e"]),
]


def create_test_file(file_name: str):
    """
    Create a test file with the given content.
    """
    os.makedirs(test_dir, exist_ok=True)
    content = "\n".join(lines)
    with open(f"{test_dir}/{file_name}", 'w') as f:
        f.write(content)
    with open(f"{test_dir}/other.txt", 'w') as f:
        f.write("other")
    return f"{test_dir}/{file_name}", f"{test_dir}/other.txt"


def check_if_all_files_exist(files: list):
    """
    Check if all files exist.
    """
    for file in files:
        if not os.path.exists(file):
            return False
    return True


def build_executable():
    """
    Build the executable.
    """
    try:
        # Remove build directory if it exists
        if os.path.exists(build_dir):
            shutil.rmtree(build_dir)
        os.mkdir(build_dir)
        # Enter build directory
        os.chdir(build_dir)
        # Generate Makefile based on system
        if sys.platform == "win32":
            subprocess.run(["cmake", "..", "-G", "MinGW Makefiles"],
                           check=True, stdout=subprocess.DEVNULL)
        else:
            subprocess.run(["cmake", ".."], check=True,
                           stdout=subprocess.DEVNULL)
        # Build executable
        subprocess.run(["make"], check=True,  stdout=subprocess.DEVNULL)
        # Return to parent directory
        os.chdir("..")
        logging.info("Build successful.")
    except Exception as e:
        logging.error("something went wrong when building the executable.")
        logging.error(e)
        sys.exit(1)


def clean_up(clean):
    """
    Clean up the build directory.
    """
    shutil.rmtree(test_dir)
    shutil.rmtree(build_dir)
    if clean:
        os.remove("standard.json")
        os.remove("result.json")



def run_executable(stdin: str, args: List[str]) -> Tuple[str, str]:
    """
    Run the executable with the given stdin, return stdout and stderr.
    """
    try:
        # Run the executable
        process = subprocess.run([executable_name]+args,
                                 input=stdin,
                                 capture_output=True,
                                 timeout=5,
                                 check=True,
                                 universal_newlines=True)
        # Return stdout and stderr
        return process.stdout, process.stderr
    except subprocess.TimeoutExpired:
        logging.error("executable timed out.")
        return "", ""
    except subprocess.CalledProcessError as e:
        logging.error("executable failed.")
        logging.error(e)
        return "", ""
    except Exception as e:
        logging.error("something went wrong when running the executable.")
        logging.error(e)
        return "", ""


def run_test(test_name: str, commands: List[str]):
    """
    Run the test with the given name and commands.
    """
    # Create a test file
    file, other = create_test_file(f"{test_name}.txt")
    stdin = '\n'.join(commands) + '\nq\n'
    stdout, stderr = run_executable(stdin, [file])
    # read the file
    with open(file, 'r') as f:
        content = f.read()
    # read other file
    with open(other, 'r') as f:
        other_content = f.read()
    result["tests"].append({
        "test": test_name,
        "stdin": stdin,
        "stdout": stdout,
        "stderr": stderr,
        "content": content,
        "other": other_content,
    })
    logging.debug(f"Test {test_name} complete.")


def run_tests():
    """
    Run all tests.
    """
    for test_name, commands in tests:
        run_test(test_name, commands)


def write_json():
    """
    Write the result to a json file.
    """
    with open("result.json", 'w') as f:
        json.dump(result, f, indent=4)


def init_result(handin: bool):
    """
    Initialize the result.
    """
    result["name"] = ""
    result["id"] = ""
    if handin:
        result["name"] = input("Name: ")
        result["id"] = input("ID: ") 
    # Get the current time in YYYY-MM-DD HH:MM:SS format
    result["time"] = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    result["tests"] = []
    # Get the current working directory
    result["cwd"] = os.getcwd()
    # Get the system architecture
    result["architecture"] = platform.architecture()
    # Get the system name
    result["system"] = platform.system()
    # Get all files in the current working directory
    result["files"] = os.listdir()
    # Get the g++ version
    result["g++"] = subprocess.run(["g++", "--version"],
                                   capture_output=True,
                                   check=True,
                                   universal_newlines=True).stdout
    # Get the make version
    result["make"] = subprocess.run(["make", "--version"],
                                    capture_output=True,
                                    check=True,
                                    universal_newlines=True).stdout
    # Get the cmake version
    result["cmake"] = subprocess.run(["cmake", "--version"],
                                     capture_output=True,
                                     check=True,
                                     universal_newlines=True).stdout
    # Get python version
    result["python"] = sys.version


def write_standard_json():
    with open("standard.json", 'w') as f:
        f.write(standard_json)


def compare_json():
    with open("result.json", 'r') as f:
        result_json = json.load(f)
    with open("standard.json", 'r') as f:
        standard_json = json.load(f)
    student_result = result_json["tests"]
    standard_result = standard_json["tests"]
    assert len(student_result) == len(standard_result), "The number of tests is not the same. Please contact TA"
    fault_tests = []
    for i in range(len(student_result)):
        if student_result[i] != standard_result[i]:
            fault_tests.append(student_result[i]["test"])
    if len(fault_tests) == 0:
        logging.info("All tests passed.")
    else:
        for i in fault_tests:
            logging.error(f"Test {i} failed.")
        logging.error(f"Please check the result.json and standard.json.")
    return fault_tests

def score(fault_tests):
    command_correct = True
    error_correct = True
    for test in fault_tests:
        if "command" in test:
            command_correct = False
        if "error" in test:
            error_correct = False
    if command_correct and error_correct:
        logging.info("Score: 70/60")
    elif command_correct:
        logging.info("Score: 60/60")
    else:
        logging.info("Score will be evaluated by TA.")
    
def handin():
    handin_dir = f"{result['name']}_{result['id']}"
    os.makedirs(handin_dir)
    for file in ["CMakeLists.txt", "editor.cpp", "editor.h", "main.cpp", "util.cpp", "util.h", "result.json"]:
        shutil.copy(file, handin_dir)
    shutil.make_archive(handin_dir, "zip", root_dir=os.getcwd(), base_dir=handin_dir)
    shutil.rmtree(handin_dir)
    logging.info(f"Handin complete. Write to {handin_dir}.zip")


def main(args):
    if not check_if_all_files_exist(["CMakeLists.txt", "editor.cpp", "editor.h", "main.cpp", "util.cpp", "util.h"]):
        logging.warning(
            "You are missing some files. Please check if you are in the right folder.")
        sys.exit(1)
    build_executable()
    init_result(handin = args.handin)
    write_standard_json()
    run_tests()
    write_json()
    fault_test = compare_json()
    score(fault_test)
    if args.handin:
        handin()
    clean_up(clean = args.clean)
    


if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO,
                        format='%(asctime)s - %(levelname)s - %(message)s')
    parser = argparse.ArgumentParser(
        description="Run the tests")
    parser.add_argument("--clean",action="store_true")
    parser.add_argument("--handin", action="store_true")
    args = parser.parse_args()
    main(args)