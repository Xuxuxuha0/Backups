import os
import pickle


class FCB:
    def __init__(self, filename, size, start):
        self.filename = filename
        self.size = size
        self.start = start


class FileSystem:
    def __init__(self, size):
        self.size = size
        self.disk = bytearray(size)
        self.directory = {}
        self.current_dir = self.directory

    def format(self):
        self.disk = bytearray(self.size)
        self.directory = {}
        self.current_dir = self.directory

    def save(self, filepath):
        with open(filepath, 'wb') as f:
            pickle.dump((self.disk, self.directory), f)

    def load(self, filepath):
        with open(filepath, 'rb') as f:
            self.disk, self.directory = pickle.load(f)
        self.current_dir = self.directory


class FileSystem:
    # 初始化、格式化、保存和加载方法
    # ...

    def mkdir(self, dirname):
        if dirname in self.current_dir:
            print("Directory already exists")
        else:
            self.current_dir[dirname] = {}

    def rmdir(self, dirname):
        if dirname not in self.current_dir:
            print("Directory does not exist")
        else:
            del self.current_dir[dirname]

    def ls(self):
        for name in self.current_dir:
            print(name)

    def cd(self, dirname):
        if dirname == "..":
            # Simplified version: does not go up beyond the root
            if self.current_dir != self.directory:
                self.current_dir = self.directory
        elif dirname in self.current_dir and isinstance(self.current_dir[dirname], dict):
            self.current_dir = self.current_dir[dirname]
        else:
            print("No such directory")

    def create(self, filename, size):
        if filename in self.current_dir:
            print("File already exists")
        else:
            start = self.find_space(size)
            if start is not None:
                self.current_dir[filename] = FCB(filename, size, start)
            else:
                print("Not enough space")

    def delete(self, filename):
        if filename not in self.current_dir:
            print("File does not exist")
        else:
            del self.current_dir[filename]

    def find_space(self, size):
        for i in range(self.size - size):
            if all(b == 0 for b in self.disk[i:i + size]):
                return i
        return None


def main():
    fs = None
    while True:
        command = input("Enter command: ").strip().split()
        if not command:
            continue

        if command[0] == "new":
            fs = FileSystem(1024 * 1024)  # 1MB virtual disk
            fs.format()
            print("New file system created")
        elif command[0] == "sfs":
            if len(command) < 2:
                print("Usage: sfs <filepath>")
            else:
                fs = FileSystem(1024 * 1024)
                fs.load(command[1])
                print(f"File system {command[1]} loaded")
        elif command[0] == "exit":
            if fs:
                fs.save("filesystem.dat")
                print("File system saved to filesystem.dat")
            break
        elif fs is None:
            print("No file system is loaded")
        else:
            if command[0] == "mkdir" and len(command) > 1:
                fs.mkdir(command[1])
            elif command[0] == "rmdir" and len(command) > 1:
                fs.rmdir(command[1])
            elif command[0] == "ls":
                fs.ls()
            elif command[0] == "cd" and len(command) > 1:
                fs.cd(command[1])
            elif command[0] == "create" and len(command) > 2:
                fs.create(command[1], int(command[2]))
            elif command[0] == "delete" and len(command) > 1:
                fs.delete(command[1])
            else:
                print("Unknown command or missing arguments")


if __name__ == "__main__":
    main()
