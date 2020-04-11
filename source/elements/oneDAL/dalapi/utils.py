import os
import subprocess
from typing import (
    Any, Union, List, Dict
)
from glob import iglob

class cd:
    def __init__(self, new_path):
        self.new_path = os.path.abspath(new_path)

    def __enter__(self):
        self.saved_path = os.getcwd()
        os.chdir(self.new_path)

    def __exit__(self, etype, value, traceback):
        os.chdir(self.saved_path)


class ProcessHandle(object):
    def __init__(self, command, startup_dir: str = '.'):
        self._command = command
        self._startup_dir = startup_dir

    def run(self):
        with cd(self._startup_dir):
            subprocess.check_call(self._command, shell=True)


class FileModificationTimer(object):
    def __init__(self, base_dir: str, pattern: str):
        self._base_dir = os.path.abspath(base_dir)
        self._pattern = pattern

    def __call__(self):
        mtimes = [os.path.getmtime(x) for x in self._get_files()]
        return max(mtimes) if len(mtimes) > 0 else 0

    def _get_files(self):
        glob_str = f'{self._base_dir}/**/{self._pattern}'
        return iglob(glob_str, recursive=True)

    def __lt__(self, dependency):
        return self() < dependency()

    def __gt__(self, dependency):
        return self() > dependency()
