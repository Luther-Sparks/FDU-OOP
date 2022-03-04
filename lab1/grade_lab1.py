from subprocess import Popen, PIPE
from sys import stderr
import argparse
import os

class Test(object):
    def __init__(self, command, input_data, expected_output, encode_type='utf-8'):
        self._command = command
        self._input_data = input_data
        self._expected_output = expected_output
        self._encode_type = encode_type
    
    def __run(self):
        process = Popen(self._command, stdin=PIPE, stdout=PIPE, stderr=PIPE, shell=True)
        for line in self._input_data:
            process.stdin.write((line+'\r\n').encode(self._encode_type))
            process.stdin.flush()
        process.wait()
        output = [item.decode(self._encode_type).strip() for item in process.stdout.readlines()]
        stderr = [item.decode(self._encode_type).strip() for item in process.stderr.readlines()]
        return output, stderr

    def run_test(self):
        output, stderr = self.__run()
        if stderr:
            for line in stderr:
                print('[ERROR] {}'.format(line))
            return False
        if len(output) != len(self._expected_output):
            print('\033[31m[ERROR]\033[0m Output: {}'.format(output))
            print('\033[31m[ERROR]\033[0m Expected: {}'.format(self._expected_output))
            return False
        for actual, expected in zip(output, self._expected_output):
            if actual != expected:
                print('\033[31m[ERROR]\033[0m Output: {}'.format(output))
                print('\033[31m[ERROR]\033[0m Expected: {}'.format(self._expected_output))
                return False
        return True
        
        

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--encode_type', '-e', help='选择你的编码格式，默认为utf-8', default='utf-8')
    args = parser.parse_args()
    encode_type = args.encode_type
    vec = ['php', 'is', 'the', 'best', 'language', 'in', 'the', 'world']
    score = 0
    if os.name == 'nt':
        test_file = '.\\build\\findKthStr.exe'
    elif os.name == 'posix':
        test_file = './build/findKthStr'
    else:
        assert False, 'Unsupported OS'
    
    if Test(test_file, ['8', '-1'] + vec, [], encode_type).run_test() and  \
         Test(test_file, ['8', '0'] + vec, [], encode_type).run_test() and \
             Test(test_file, ['8', '7'] + vec, [], encode_type).run_test():
        print('\033[32m[OK] invalid_k_test passed\033[0m')
        score += 5
    else:
        print('\033[31m[Fail] invalid_k_test failed\033[0m')
        
    if Test(test_file, ['8', '3'] + vec, ['best'], encode_type).run_test() and  \
         Test(test_file, ['8', '5'] + vec, ['language'], encode_type).run_test():
        print('\033[32m[OK] single_output_test passed\033[0m')
        score += 5
    else:
        print('\033[31m[Fail] single_output_test passed\033[0m')
        
    if Test(test_file, ['8', '2'] + vec, ['php', 'the', 'the'], encode_type).run_test() and  \
         Test(test_file, ['8', '1'] + vec, ['is', 'in'], encode_type).run_test():
        print('\033[32m[OK] multi_output_test passed\033[0m')
        score += 10
    else:
        print('\033[31m[Fail] multi_output_test passed\033[0m')
        
    print('total score: {}'.format(score))
        
        

             