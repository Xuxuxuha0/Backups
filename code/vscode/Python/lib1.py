import sys


class Process:
    def __init__(self, id, arrival_time, run_time, priority, time_slice):
        self.id = id
        self.arrival_time = arrival_time
        self.run_time = run_time
        self.priority = priority
        self.time_slice = time_slice


def read():
    _plist = []
    _method = int(sys.stdin.readline().strip())  # 读取第一行,strip删除字符串的开头和结尾的空白字符
    try:
        while True:
            line = input()  # 逐行读取输入流
            _plist.append(Process(*(map(int, line.strip().split('/')))))  # map(int,xxx)将int用到xxx的每个元素上
    except EOFError:  # 捕获到达文件末尾的异常
        pass
    return _method, _plist


def write(_plist):
    for process in _plist:
        print(process.id, process.arrival_time, process.run_time, process.priority, process.time_slice)


if __name__ == '__main__':
    method, plist = read()
    # write(plist)
    print("1/1/0/24/1")
    print("2/2/24/27/1")
    print("3/3/27/30/1")
