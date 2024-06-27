f = open("output.txt", "w+")
ls = ["1", "2", "3"]
f.writelines(ls)
f.seek(0)  # 着重强调写完文件后,指针指向文件尾
for line in f:  # 若调用for...in  需要将指针放在文件头或其他位置
    print(line)
f.close()
