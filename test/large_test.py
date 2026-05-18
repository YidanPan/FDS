import random

Nv = 1000
Ne = 100000
K = 100

print("Generating extreme test data...")

with open("large_test.txt", "w") as f:
    # 写入顶点数和边数
    f.write(f"{Nv} {Ne}\n")
    
    # 1. 保证图是连通的：生成一个包含所有顶点的基础生成树 (Spanning Tree)
    # 把 1-2, 2-3, 3-4 ... 连起来
    for i in range(2, Nv + 1):
        u = i - 1
        v = i
        weight = random.randint(1, 100)
        f.write(f"{u} {v} {weight}\n")
        
    # 2. 生成剩余的随机边，补齐到 100000 条
    remaining_edges = Ne - (Nv - 1)
    for _ in range(remaining_edges):
        u = random.randint(1, Nv)
        v = random.randint(1, Nv)
        while u == v: # 防止自环
            v = random.randint(1, Nv)
        weight = random.randint(1, 100)
        f.write(f"{u} {v} {weight}\n")
        
    # 3. 写入查询次数 K
    f.write(f"{K}\n")
    
    # 4. 生成 K 个查询序列（每个序列是 1 到 Nv 的随机全排列）
    vertices = list(range(1, Nv + 1))
    for _ in range(K):
        random.shuffle(vertices)
        # 将列表转换为字符串并写入
        f.write(" ".join(map(str, vertices)) + "\n")

print("Generation complete! File saved as large_test.txt")