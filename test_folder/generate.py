# 这是一个生成最大规模测试数据的 Python 脚本 (generate.py)
# 运行后会生成一个 huge_data.txt，里面有 400,000 个节点
import random

N1 = 200000
N2 = 200000

with open("huge_data.txt", "w") as f:
    # 生成 T1
    f.write(f"{N1}\n")
    for i in range(N1):
        # 生成 -10^9 到 10^9 的随机数，除了第一个节点，其他父节点随机挂
        val = random.randint(-1000000000, 1000000000)
        parent = -1 if i == 0 else random.randint(0, i - 1)
        f.write(f"{val} {parent}\n")
    
    # 生成 T2
    f.write(f"{N2}\n")
    for i in range(N2):
        val = random.randint(-1000000000, 1000000000)
        parent = -1 if i == 0 else random.randint(0, i - 1)
        f.write(f"{val} {parent}\n")
    
    # 生成目标和 N
    f.write("100\n")