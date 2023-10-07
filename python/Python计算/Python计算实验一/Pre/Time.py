time=input("请输入小时、分钟、秒（用:分隔）:")
hour,minute,second=map(int,time.split(":"))
# while hour>=24 or minute>=60 or second>=60:
#     print("输入有误，请重新输入")
#     time = input("请输入小时、分钟、秒（用:分隔）:")
#     hour, minute, second = map(int, time.split(":"))
second=second+1
if second>=60:
    second%=60
    minute+=1
    if minute>=60:
        minute%=60
        hour+=1
        if hour>=24:
            hour%=24
print(f"下一秒的时间为：{hour:02d}:{minute:02d}:{second:02d}")
