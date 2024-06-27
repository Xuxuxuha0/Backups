"""
二进制:0b/0B开头
八进制:0o/0O开头
十六进制:0x/0X

四舍五入函数:
    round(1.555,2)==1.56
    round(1.555)==2

运算:
除:   10/3==3.33333333333
整除: 10//3==3
幂运算: 10**0.5 即根号10 


绝对值函数:abs(-10)==10
幂函数:pow(10,2)==100
最大值函数:max(1,9,5)==9
最小值函数:min(1,9,5)==1

类型转换函数：
整数函数:int(123.55)==123    int("123")==123
浮点函数:float(12)==12.0     float("1.23")==1.23
复数函数:complex(4)==4+0j
str(1.23) 返回"1.23"    str([1,2]) 返回"[1,2]"    强制转换为字符串类型
hex(425) 返回"0x1a9"    oct(425) 返回"0o651"
chr(u) 返回对应的字符
ord(x) 返回对应的Unicode编码

set(x)将x转换为集合类型   
list(x)转换为列表   
tuple(x)转换为元组   
dict(x)转换为字典
str(x)转换为字符串   
int(x)和float(x)只能是字符串或数字转换为整数/浮点数
最好用eval(x)


索引:      "opajia"[0]  表示第一个字符
切片:      "opajia"[0:-1]  表示除-1(最后一个)之外所有字符
高级切片1: "0123456789"[:3] 表示"012"             "0123456789"[3:] 表示"3456789"
高级切片2: "0123456789"[1:8:2] 表示"1357"         "0123456789"[::-1] 表示"9876543210"

转义符保留字符的本意:   \" 即 "
转义符表示特殊含义:     \b 回退    \n 换行    \r 移动到本行首




字符串格式化:

    槽{}与format()
        "{}:计算机{}的cpu占用率为{}%".format("10.10","007",10)
    format()的格式化控制
        "{0:=^20}".format("python")
            =表示填充符    ^表示居中对齐    20表示宽度
            输出   '=======python======='

        "{:10}".format("bit")
            输出   'bit       '

        "{0:,.2f}".format(12345.6789)
            ,表示千位分隔符 位于宽度之后
            输出   '12,345.68'

        输出类型
            "{0:b},{0:c},{0:d},{0:o},{0:x},{0:X}".format(425)
            输出   '110101001,Σ,425,651,1a9,1A9'
            "{0:e},{0:E},{0:f},{0:%}".format(3.14)
            输出   '3.140000e+00,3.140000E+00,3.140000,314.000000%'


条件组合的保留字
    and  or  not


异常处理
try:
    <1>
except:
    <2>
else:
    <3>
finally:
    <4>


遍历循环:
    for i in range(1,6,2):     
        print(i,end=",")          1,3,5,
    for c in "python123":
        print(c,end=",")          p,y,t,h,o,n,1,2,3,
    for item in[123,"py",456]
        print(item,end=",")       123,py,456,

循环扩展:
    for...else...
    while...else...
    只要循环没有被break强制退出 循环结束后就要执行else


def fact(n,m=1):
    s=1
    for i in range (1,n+1):
        s*=i
    return s//m
调用fact(10,5) 则m=5参与运算
也可以fact(m=5,n=10)

def fact(n,*b):          *b表示未知个数的参数
    s=1
    for i in range (1,n+1):
        s*=i
    for item in b:
        s*=item
    return s
调用fact(10,3,5,8) 则逐个相乘

多个返回值:
    return a,b,c       则返回(a,b,c)
    也可以a,b,c=fact(10,5)  则依次对应返回值

在函数中使用
    global s
    则调用的是全局变量s,且在函数中会被修改值

函数没有创建组合数据类型,但使用了它,则该组合数据类型就是全局变量,会被更改值

lambda函数:
    函数名=lambda <参数>:<表达式>
    f=lambda x,y:x+y
    f(10,25)==35



字符串操作:
    "ABCde".lower()            "abcde"
    "ABCde".upper()            "ABCDE"

    "a,b,c".split(",")         ['a','b','c']    根据符号分割为列表
    ",".join("1234")           "1,2,3,4"

    "a aabc a".count("a")        4              返回出现次数
    "abc".replace("c","cde")   "abcde"          替换为新字符串
    "abcd".center(10,"=")      '===abcd==='     居中并填补
    "= abc= ".strip(" =a")     "bc"             去掉字符

    连接两个字符串: x+y
    复制n次字符串:  n*x  /   x*n
    x是s的子串 返回True: x in s
    len("一二三456")  返回6


集合:
    a={"abc",123,("abc",123)}
    b=set("333abc")  其中集合的元素则为'3' 'a' 'b' 'c'   集合不允许存在相同元素
操作符:
    s|t:新集合,包含所有元素
    s-t:新集合,包含在s但不在t中的元素
    s&t:新集合,同时在st中的
    s^t:新集合,st中不相同的
    s<=t等:返回True/False   反应包含关系
四个增强操作符:
    s|=t:更新s,包含所有元素
    s-=t    s&=t    s^=t  同上
集合处理函数:
    s.add(x)  增加x到s中
    s.discard(x)  移除x;如果x不在s中,不报错
    s.remove(x)  移除x;如果x不在s中,报错
    s.clear()   清空s
    s.pop(x)   返回元素x(没有参数x则默认最后一个元素),同时删除它;如果s为空会报错
    s.copy()  返回s的一个副本
    len(s)  元素个数
    x in s / x not in s   返回True/False


序列:(字符串、元组、列表)
    操作符:
        x in s / x not in s
        s+t  连接
        s*n  复制n次
        s[i]  s[i:j]  s[i:j:k]
    操作函数:
        len(s)
        min(s)  max(s)
        s.index(x)   s.index(x,i,j) 返回从i--j第一次出现x的位置
        s.count(x)  s中出现x的总次数


元组:
    a="b","c","d"
    i=("e",123,a)   其中a也是元组类型
                    i[-1][1]即'c'
    tuple(a)  强制转换为元组类型
    元组类型无法修改 所有操作都是生成了新的元组类型


列表:
    a=['b','c','123']
    a=b  则会让a b都指向同一个列表
    操作:
        a[i]=x  替换为x
        a[i:j:k]=b  用b列表替换切片后对应的元素子列表
        del a[i]  删除第i个元素
        del a[i:j:k]  删除相应的元素
        a+=b   更新a 把b中的元素增加到a中
        a*=n   更新a 使其重复n次
    函数；
        a.append(x)   在最后增加x
        a.clear()     清空a
        a.copy()      生成新列表
        a.insert(i,x) 在i位置增加x
        a.pop(i)      去除i位置元素
        a.remove(x)   第一次出现的x删除
        a.reverse()   元素反转


字典类型:
    d={"1":"a","2":"b","3":"c"}   123为键,abc为对应的值
        d["1"]=='a'
    d={}     生成空的字典类型
        d["a"]=1   给字典新增键值对
    type(x)  检测x是什么类型
    函数:
        del d[k]    删除k键对应的值
        k in d      判断k键是否在d中
        d.keys()    返回d中所有键,类似列表类型,但不能当作列表
        d.values()  返回d中所有值,类似列表类型,但不能当作列表
        d.items()   返回d中所有键值对
        
        d.get(k,<default>)  键k存在,返回k的值;否则返回default
        d.pop(k,<default>)  键k存在,取出k的值并删除该键值对;否则返回default
        d.popitem()         随机取出并删除一个键值对,以元组形式返回
        d.clear()           清空
        len(d)              元素个数


jieba库(已安装)   用于中文分词
    函数:jieba.lcut(s)   分词函数


文件:
    文件名:
        D:\a\b.txt   ->    "D:/a/b.txt" 或 D:\\a\\b.txt
        若源文件同目录   则也可以使用  "./a/b.txt"或"b.txt"
    打开方式:
        'r'   读文件
        'w'   覆盖式写文件
        'x'   创建一个文件来写
        'a'   追加
        'b'   二进制打开
        't'   文本文件打开
            '+'  增加读写功能
    函数:
        f=open("文件名","方式")    打开
        f.close()                 关闭

        s=f.read()       读取整个f文件 ;给出参数则读x个字符
        s=f.readline()   读一行 ;给出参数则读该行前x个字符
        s=f.readlines()  读所有行,每一行为一个元素构成列表  ;给出参数则读x行

        f.write("123")   将字符串写入文件
        f.writelines(ls) 将ls列表中的元素直接拼接后写入文件

        f.seek()         参数为0,1,2 指针依次定位到开头,当前,结尾


一维数据:
    有序:列表
    无序:集合
    存储方式:  空格分隔  逗号分隔  特殊符号分隔
    写入文件: 
        ls=['1','2','3']
        f.write('$'.join(ls))      1$2$3$
    读取为列表:
        ls=f.split(",")            ['1','2','3']
二维数据:
    二维列表
    csv格式


wordcloud库(已安装)
    函数:
        w.generate(txt)       向w中加载文本txt
        w.to_file(filename)   将词云输出为图像文件  .png或.jpg格式

        wordcloud.WordCloud(width=a)  宽度设为a
        wordcloud.WordCloud(height=b)  高度设为b

        wordcloud.WordCloud(min_font_size=b)      最小字号
        wordcloud.WordCloud(max_font_size=b)      最大字号
        wordcloud.WordCloud(font_step=b)          字号的递进间隔
        wordcloud.WordCloud(font_path="指定文体文件的路径")

        wordcloud.WordCloud(max_words=b)          最大显示的词汇数量
        wordcloud.WordCloud(stop_words={。。。})   不显示的词汇

        wordcloud.WordCloud(backgroud_color='white')  背景变为白色

    指定词云的形状的一般步骤:
        from scipy.misc import imread / from imageio import imread
        mk=imread("形状图像文件")
        w=wordcloud.WordCloud(mask=mk)


第三方库的安装方法:
    python社区:  https://pypi.org/
    pip方法:
            在cmd中输入 pip install 库名     安装库
                        pip install -U 库名  更新库
                        pip uninstall 库名   卸载库
                        pip search 关键词    搜索所在的库
                        pip list             列出已安装的库
    需要编译的库:
            https://www.lfd.uci.edu/~gohlke/pythonlibs/


os库:
    os.path 子库:
                函数:
                    os.path.abspath("file.txt")  返回文件的绝对路径
                    os.path.norpath(path)        用\\归一化表示路径
                    os.path.relpath(path)        返回相对路径

                    os.path.dirname(path)        返回目录
                    os.path.basename(path)       返回文件名
                    os.path.join(path,*paths)    组合二者并返回路径

                    os.path.exists(path)         判断是否存在
                    os.path.isfile(path)         判断文件是否存在
                    os.path.isdir(path)          判断目录是否存在

                    os.system(path)              调用该程序


数据分析库:numpy  pandas   scipy
数据可视化库:matplotlib   seaborn   mayavi
文本处理库:pypdf2   nltk   python-docx
机器学习库:scikit-learn   tensorflow   mxnet

爬虫库:requests   scrapy   pyspider
信息解析:beautiful soup     re    python-goose
网站开发:django   pyramid   flask
网络应用开发:werobot   aip   myqr

人机交互界面:pyqt5   wxpython   pygobject
人机交互游戏:pygame   panda3d   cocos2d
人机虚拟交互:vr zero    pyovr   vizard
图形艺术:quads   ascii_art   turtle

python进阶与应用 进一步看嵩天视频





































"""
