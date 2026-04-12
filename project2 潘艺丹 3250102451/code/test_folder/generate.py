#generating maximum-scale test data
import random

N1=200000
N2=200000 #number of loop iterations
with open("huge_data.txt","w") as f: #creat t1
    f.write(f"{N1}\n")

    for i in range(N1):
        val=random.randint(-1000000000,1000000000)
        parent=-1 if i==0 else random.randint(0,i-1)
        f.write(f"{val} {parent}\n") #generate random integers ranging from -10⁹ to 10⁹,except for the first node, all other nodes are randomly assigned to parent nodes
    f.write(f"{N2}\n") #creat t2
    
    for i in range(N2):
        val=random.randint(-1000000000,1000000000)
        parent=-1 if i==0 else random.randint(0,i-1)
        f.write(f"{val} {parent}\n")
    f.write("100\n") #creat the target and n