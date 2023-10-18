def read_txt_and_create_dictionary(file):
    num = 0
    text = []
    dictionary = {}
    with open(file, "r") as file:
        for line in file.readlines():  # 全部读入并返回列表，对列表进行迭代
            line = line.strip('\n')  # 移除换行符
            line = line.split()  # 按空格分开
            text.append(line)
            for str in line:
                num += 1
                if str not in dictionary:  # 去重添加，同时计数
                    dictionary[str] = 1
                else:
                    dictionary[str] += 1
    return num, text, dictionary


num, text, dictionary = read_txt_and_create_dictionary("./Data/text.txt")
for dir in dictionary:
    print(dir, "出现次数:", dictionary[dir])

key_list = ['of', 'I', 'world']
for key in key_list:
    if key not in dictionary:
        print("文本中没用此单词：", key)
    else:
        print(key, "出现频率：", dictionary[key]/num)
