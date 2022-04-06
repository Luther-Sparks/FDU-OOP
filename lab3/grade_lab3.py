import subprocess
import sys
import os
import logging
import platform
from time import time
import shutil
import argparse
import json

# exit if python2
if sys.version_info[0] < 3 or sys.version_info[1] < 7:
    print("This program requires Python 3.7. Please contact TA for help.")
    sys.exit(1)
    
build_dir = "build"
# Executable based on system
if sys.platform == "win32":
    executable_name = f"n_gram.exe"
else:
    executable_name = f"n_gram"

result = {}

test_words = """best
main
good
small
large
man
woman
king
chinese
america
university
,
oop
trump"""

std_json = {
    "tests": [
        {
            "test": "bigram_test",
            "args": [
                "--train 2 ../wikitext.txt",
                "--test ../test.txt matrix.txt"
            ],
            "stderr": "Error: cannot find word oop\n",
            "output": "largest greatest highest first biggest \nsee boeing your leaving just \nhappy strong bad dangerous better \neasy slow low difficult soft \nsmall easy little difficult low \nmen adult adults giant woman \njoe mind adult adults men \ngulf astronomer armenia ruler independent \nrome greek castle greece times \ncarolina dakota korea arkansas universe \ndictionary records english jones world's \n. and ( is was \n\nduck j tries i n \n"
        },
        {
            "test": "trigram_test",
            "args": [
                "--train 3 ../wikitext.txt",
                "--test ../test.txt matrix.txt"
            ],
            "stderr": "Error: cannot find word oop\n",
            "output": "outstanding golden for nomination confirmed \ngoing see your connection covers \nbad dangerous happy strong better \neasy slow large difficult low \nsmall easy difficult slow low \nlewis port lost fight dogs \njoe mind defence culture foreign \ngulf ruler van <unk> , \nkong korean greek english <unk> \ncarolina dakota universe korea africa \npress dictionary ohio massachusetts records \n<unk> . and ( is \n\nduck nominated graduated j tries \n"
        },
        {
            "test": "5-gram_test",
            "args": [
                "--train 5 ../wikitext.txt",
                "--test ../test.txt matrix.txt"
            ],
            "stderr": "Error: cannot find word oop\n",
            "output": "award nomination awards outstanding academy \nfictional <unk> the this is \npositive mixed critics bad negative \nlarge easy are spiders safe \nsmall are <unk> a the \nlewis board water post introduced \njoe mind defence culture girl \niii iv duke sir prince \npolish and jewish german <unk> \ncarolina dakota africa universe europe \npress college dictionary at he \n. <unk> and ( in \n\nduck nominated don uncle j \n"
        }
    ]

}

tests = [
    ("bigram_test", ['--train 2 ../wikitext.txt', f'--test ../test.txt matrix.txt']),
    ("trigram_test", ['--train 3 ../wikitext.txt', f'--test ../test.txt matrix.txt']),
    ("5-gram_test", ['--train 5 ../wikitext.txt', f'--test ../test.txt matrix.txt'])
]

def write_json():
    with open('result.json', 'w') as f:
        json.dump(result, f, indent=4)
    with open('standard.json', 'w') as f:
        json.dump(std_json, f, indent=4)

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
        logging.info("Build successful.")
    except Exception as e:
        logging.error("something went wrong when building the executable.")
        logging.error(e)
        sys.exit(1)
        
def create_test_file():
    with open('test.txt', 'w') as f:
        f.write(test_words)
    
def run_executable(stdin: str, args: str):
    try:
        # Run the executable
        starttime = time()
        process = subprocess.run(['./'+executable_name]+args.split(' '),
                                 input=stdin,
                                 capture_output=True,
                                 timeout=300,
                                 check=True,
                                 universal_newlines=True)
        # Return stdout and stderr
        usetime = time() - starttime
        return usetime, process.stderr
    except subprocess.TimeoutExpired:
        logging.error("executable timed out.")
        return 0, ""
    except subprocess.CalledProcessError as e:
        logging.error("executable failed.")
        logging.error(e)
        return 0, ""
    except Exception as e:
        logging.error("something went wrong when running the executable.")
        logging.error(e)
        return 0, ""

def handin():
    handin_dir = f"{result['name']}_{result['id']}"
    os.makedirs(handin_dir)
    for file in ["CMakeLists.txt", "grams.cpp", "grams.h", "main.cpp", "util.cpp", "util.h", "result.json"]:
        shutil.copy(file, handin_dir)
    shutil.make_archive(handin_dir, "zip", root_dir=os.getcwd(), base_dir=handin_dir)
    shutil.rmtree(handin_dir)
    logging.info(f"Handin complete. Write to {handin_dir}.zip")
    
def clean_up(clean):
    if clean:
        shutil.rmtree(build_dir)
        os.remove("test.txt")
        os.remove("standard.json")
        os.remove("result.json")
        
def check_if_all_files_exist(files: list):
    for file in files:
        if not os.path.exists(file):
            return False
    return True

def run_test(test_name : str, args):
    train_usetime, stderr = run_executable("", args[0])
    test_usetime, stderr = run_executable("", args[1])
    output = 'output.txt'
    usetime = train_usetime + test_usetime
    print(f"{test_name} took {round(usetime, 3)} seconds.")
    with open(output, 'r') as f:
        content = f.read()
    result['tests'].append({
        "test": test_name,
        "args": args,
        "stderr": stderr,
        "output": content
    })
    logging.debug(f"Test {test_name} complete.")
    
def run_tests():
    for test_name, args in tests:
        run_test(test_name, args)
        
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
        temp1 = str(student_result[i]).strip()
        temp2 = str(standard_result[i]).strip()
        if temp1 != temp2:
            fault_tests.append(student_result[i]["test"])
    if len(fault_tests) == 0:
        logging.info("All tests passed. Extra credit will be evaluated on TA's computer.")
        logging.info("Score: 100/100")
    else:
        for i in fault_tests:
            logging.error(f"Test {i} failed.")
        logging.error(f"Please check the result.json and standard.json.")
        logging.info("Score will be evaluated by TA.")
        
def init_result(handin: bool):
    """
    Initialize the result.
    """
    result["name"] = ""
    result["id"] = ""
    if handin:
        result["name"] = input("Name: ")
        result["id"] = input("ID: ") 
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


def main(args):
    if not check_if_all_files_exist(['CMakeLists.txt', 'grams.cpp', 'grams.h', 'util.cpp', 'util.h', 'wikitext.txt']):
        logging.warning("You missed some files. Please check if you have all the files or in the right folder.")
        sys.exit(1)
    create_test_file()
    build_executable()
    init_result(args.handin)
    run_tests()
    os.chdir('..')
    write_json()
    compare_json()
    if args.handin:
        handin()
    clean_up(args.clean)
    
if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
    parser = argparse.ArgumentParser(description="Runs the lab3 grading script.")
    parser.add_argument('--clean', action='store_true')
    parser.add_argument('--handin', action='store_true')
    args = parser.parse_args()
    main(args)