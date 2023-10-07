import sys
from pprint import pprint

src_dir = sys.path[0]
data_dir = "./../Data"
file_name = "words.txt"

src_dir + data_dir
with open(src_dir + "/" + data_dir + "/" + file_name, "r") as file:
    data = [i.rstrip() for i in file.readlines()]
    rdata = {i[::-1]: i for i in data}
    ans = []
    for word in data:
        if word in rdata:
            ans.append(word)
            rdata.pop(word[::-1])
    ans = [[i, i[::-1]] for i in ans]
    with open(src_dir + "/" + data_dir + "/" + "ReverseOrderPair(word.txt).txt", "w") as faim:
        faim = faim.writelines([i[0] + " " + i[1] + "\n" for i in ans])
    # pprint(ans) #由于内容过多不在此展示
