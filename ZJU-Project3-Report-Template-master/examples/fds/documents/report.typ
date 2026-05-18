#import "../../../template.typ": *
#import "@preview/lovelace:0.3.0": *

#show: project.with(
  theme: "project",
  course: "Fundamentals of Data Structures",
  title: "Projects 3: Dijkstra Sequence
",
  date: "2026/05/05",
  author: "Pan Yidan",
  semester: "2025-2026 Spring & Summer",
)

= *Chapter 1*: Introduction

== Problem Signifience

*Dijkstra's algorithm* is a fundamental greedy algorithm widely used to find the shortest paths from a single source vertex to all other vertices in a weighted graph. A core characteristic of this algorithm is its step-by-step nature: at each iteration, it expands the shortest path tree by selecting the unvisited vertex with the minimum distance from the source.

However, in many practical graph topologies, multiple unvisited vertices might share the exact same minimum distance at a given step. Consequently, the algorithm can legitimately choose any of these tied vertices, leading to multiple valid selection sequences (Dijkstra sequences) for the same graph. The primary *motivation* of this project is to deepen our comprehension of this greedy mechanism. By reverse-verifying these sequences, we *aim* to ensure a thorough understanding not just of the final shortest path calculation, but of the exact step-by-step procedural logic and the dynamic state changes during the algorithm's execution.

== Problem Description

In this project, we are given a connected undirected graph with positive edge weights, along with several query sequences consisting of permutations of all vertices. For each given sequence, the first vertex is assumed to be the source node.

The *objective* is to design and implement a program that dynamically simulates the vertex selection process of *Dijkstra's algorithm*. For each sequence, the program must verify whether it represents a valid execution order. Specifically, we must validate that at every step, the chosen vertex in the sequence genuinely possesses the minimum tentative distance among all currently unvisited vertices. If the sequence strictly follows the greedy choice property, the program should output "Yes"; otherwise, if a sub-optimal vertex is chosen prematurely, it should output "No".

= *Chapter 2*: Algorithm Specification

== Data Structure
To efficiently implement the simulation of *Dijkstra's algorithm*, the following data structures are utilized in this project:

- *Adjacency Matrix (G[MAX][MAX])*: A 2D integer array used to represent the undirected weighted graph. Given that we need to frequently query the edge weight between any two specific vertices during the relaxation process, an adjacency matrix provides $O(1)$ constant time complexity for edge lookups. The absence of an edge is represented by a sufficiently large constant INF.

- *Distance Array (dist[MAX])*: A 1D integer array that stores the current shortest distance from the source vertex to every other vertex.

- *Visited Array (flag[MAX])*: A 1D boolean/integer array used to keep track of whether a vertex has been securely included in the shortest path tree (1 for visited, 0 for unvisited).

- *Query Array (inquiry[MAX])*: A 1D array to store the current given permutation sequence of vertices that needs to be verified.

== Sketch of The Main Program 
The main program coordinates the input processing, graph construction, and the execution of queries. The execution flow is outlined below:

+ *Read Graph Parameters:* Read the total number of vertices $N_v$ and edges $N_e$.

+ *Matrix Initialization:* Initialize all elements in the adjacency matrix G to INF.

+ *Graph Construction:* Loop $N_e$ times to read each edge $(u, v)$ and its weight. To ensure robustness against potential parallel edges, the program conditionally updates the matrix only if the newly read weight is strictly smaller than the existing weight G[u][v].

+ *Query Processing:* Read the number of queries $K$. Loop $K$ times:
  - Read the given permutation sequence of $N_v$ vertices into the inquiry array.
  - Call the core verification function Judge_Dijkstra(inquiry, N_v) to determine the validity of the sequence.

== Key Algorithm
*Pseudocode of Judge_Dijkstra:*
#pseudocode-list[
  + Let source vertex $v$ = `inquiry[1]`
  + Initialize `dist[1..n]` = $G[v][1..n]$, and `flag[1..n]` = `0`
  + `dist[v]` = 0
  + `flag[v]` = `1`
  + `current_idx` = 2
  + *for* `step` = 1 *to* $n - 1$ *do*
    + `mindist` = INF
    + *for* $j$ = 1 *to* $n$ *do*
      + *if* `flag[j]` == `0` and `dist[j]` < `mindist` *then*
        + `mindist` = `dist[j]`
      + *end if*
    + *end for*
    + Let target_vertex $k$ = `inquiry[current_idx]`
    + *if* `dist[k]` $!=$ `mindist` *then*
      + Print "No"
      + *Return*
    + *end if*
    + `flag[k]` = `1`
    + `current_idx` = `current_idx` + 1
    + *for* $j$ = 1 *to* $n$ *do*
      + *if* `flag[j]` == `0` and edge($k, j$) exists *then*
        + *if* `dist[k]` + weight($k, j$) < `dist[j]` *then*
          + `dist[j]` = `dist[k]` + weight($k, j$)
        + *end if*
      + *end if*
    + *end for*
  + *end for*
  + Print "Yes"
]

*Description:*

The core algorithm dynamically simulates the greedy choice property of Dijkstra's algorithm. Instead of finding the minimum distance vertex to build the path, it verifies if the next vertex provided by the inquiry sequence actually holds the minimum distance among all unvisited vertices.
- *Require:* Graph G, Array inquiry[1..n] containing the vertex sequence
- *Ensure:* Prints "Yes" if the sequence is a valid Dijkstra sequence, else "No"

= *Chapter 3*: Testing Results

== Testing Strategy
To thoroughly evaluate the correctness and robustness of the Judge_Dijkstra algorithm, multiple test cases were designed. These tests cover general graph traversals, special boundary conditions, and extreme graph properties. The testing purposes strictly align with the algorithm's greedy choice property and data handling capabilities.

== Test Cases Table
#align(center)[
  #table(
    columns: (auto, auto, auto, auto, auto, auto, auto),
    // 单元格内容垂直居中对齐
    align: horizon,
    // 定义表头
    table.header(
      [*Test ID*], 
      [*Testing Purposes*], 
      [*Graph Size ($N_v$, $N_e$)*], 
      [*Input Graph Edges (u,v, weight)*], 
      [*Query Sequences*], 
      [*Expected Output*], 
      [*Actual Output*],
    ),

    // 第一行数据：综合测试
    [*Test 1*],
    [*Comprehensive Test:* the example from PTA],
    [$N_v=5$, $N_e=7$],
    [(1,2,2), (1,5,1), (2,4,1), (2,4,1), (2,5,2),(3,5,1),(3,4,1)],
    [Q1: `5 1 3 4 2` \ Q2: `5 3 1 2 4` \ Q3: `2 3 4 5 1` \ Q4: `3 2 1 5 4`], 
    [Q1: Yes \ Q2: Yes \ Q3: Yes \ Q4: No],
    [#image("/assets/image-1.png")Q1: Yes \ Q2: Yes \ Q3: Yes \ Q4: No],

    // 第二行数据：极端情况 (距离相同)
    [*Test 2*],
    [*Extreme Case (Tied Distances):* Multiple vertices share the exact same minimum distance. Dijkstra can pick any of them.],
    [$N_v=3$, $N_e=2$],
    [(1,2,2), (1,3,2)],
    [Q1: `1 2 3` \ Q2: `1 3 2`],
    [Q1: Yes \ Q2: Yes],
    [#image("/assets/image-2.png")Q1: Yes \ Q2: Yes],

    // 第三行数据：极端情况 (重边)
    [*Test 3*],
    [*Extreme Case (Parallel Edges):* Graph contains multiple edges between the same pair of vertices. The program must store the minimum one.],
    [$N_v=3$, $N_e=3$],
    [(1,2,10), (1,2,2), (2,3,1)],
    [Q1: `1 2 3` \ Q2: `1 3 2`],
    [Q1: Yes \ Q2: No],
    [#image("/assets/image-3.png")Q1: Yes \ Q2: No],

    // 第四行数据：最小规模边界测试
    [*Test 4*],
    [*Smallest Size Boundary:* The minimum possible graph size connected by a single edge.],
    [$N_v=2$, $N_e=1$],
    [(1,2,100)],
    [Q1: `1 2` \ Q2: `2 1`],
    [Q1: Yes \ Q2: Yes],
    [#image("/assets/image-4.png")Q1: Yes \ Q2: Yes],

    // Test 5: 最大规模压力测试
    [*Test 5*],
    [*Largest Size Boundary:* Evaluating the \ algorithm's performance under the absolute maximum constraints to ensure no memory overflow or Time Limit Exceeded occurs.],
    [$N_v=1000$, \ $N_e=100000$],
    [_Generated via script_ \ (Fully connected dense graph)],
    [$K=100$ \ random sequences],
    [Correct Yes/No results \ Execution time $< 1.0$s],
    [*Passed successfully.* \ #image("/assets/image-5.png") \ Time: `0.256000 seconds` \ (No SegFault)],
  )
]

== Detailed Analysis of Extreme Cases
- *Test 2 (Tied Distances):* 

  This is a critical extreme case. From vertex 1, both vertex 2 and vertex 3 have a distance of 2. According to Dijkstra's greedy property, picking either 2 or 3 in the next step is completely legal. Our algorithm successfully outputs "Yes" for both permutations, proving it handles distance ties correctly rather than forcing a strict numerical order.

- *Test 3 (Parallel Edges):* 

  Real-world input data may contain noise, such as duplicate paths with different weights. In Test 3, vertices 1 and 2 are connected by weights 10 and 2. The algorithm successfully captures the shortest edge (weight 2) during initialization, outputting "Yes" for 1 2 3 and avoiding the trap of being overwritten by the larger weight.

- *Test 5 (stress test of largest size):*

  To evaluate the algorithm's robustness under the extreme conditions specified by the problem ($N_v = 1000$, $N_e = 100000$, $K = 100$), a local stress testing environment was established. A Python script was developed to automatically generate a fully connected dense graph.  
  \ The script guarantees graph connectivity by initially forming a minimum spanning tree with random weights and subsequently populating the remaining edges randomly to reach the $100,000$ limit. Afterwards, $K=100$ random permutations of the vertices were generated as query sequences.
  \ The standard <time.h> library in C was implemented to measure the execution time strictly for the query processing phase.#image("/assets/image-6.png")
  \ As shown in the output, the program gracefully handled the maximum data scale without any Segmentation Faults or Memory Limit Exceeded errors, proving that our space allocation using the adjacency matrix is perfectly optimal. Furthermore, the total execution time for processing all $100$ queries on this massive graph was merely 0.256000 seconds. This exceptionally low duration strongly proves that the theoretical $O(K times N_v^2)$ time complexity executes well within any standard 1.0-second time limit constraint.

= *Chapter 4*: Analysis and Comments

== Time Complexity
The time complexity of the algorithm is analyzed based on three major phases: Initialization, Graph Construction, and Query Processing. Let $N_v$ be the number of vertices, $N_e$ the number of edges, and $K$ the number of queries.
- *Matrix Initialization:* The program uses a nested loop to initialize the $N_v times N_v$ adjacency matrix with INF. This takes exactly $O(N_v^2)$ time.

- *Graph Construction:* Reading $N_e$ edges from the input and updating the matrix takes $O(N_e)$ time.

- *Query Processing:* For each of the $K$ queries, the Judge_Dijkstra function is executed:
  - The function iterates $N_v - 1$ times to verify each vertex in the sequence.
  - Inside each iteration, it searches for the minimum distance among unvisited vertices, which takes $O(N_v)$.
  - After verification, it performs edge relaxation for all neighbors, which takes another $O(N_v)$.
  - Thus, one query takes $O(N_v) times (O(N_v) + O(N_v)) = O(N_v^2)$ time.
  - For $K$ queries, the total time is $O(K times N_v^2)$.

*Conclusion:* The overall time complexity is $O(N_v^2 + N_e + K times N_v^2)$. Since $N_e <= N_v^2$, the dominant term is $O(K times N_v^2)$.

== Space Complexity
The space complexity is determined by the primary data structures:
+ *Adjacency Matrix:* A 2D array G[1005][1005] of integers. It occupies $1005^2 times 4$ bytes, which is $O(N_v^2)$.
+ *Auxiliary Arrays:* Arrays such as dist[MAX], flag[MAX], and inquiry[MAX] each consume $O(N_v)$ space.
*Conclusion:* The total space complexity is $O(N_v^2)$. This is well within the typical memory limit of 64MB or 128MB for competitive programming.

== Discussion
In this project, we chose the Adjacency Matrix to represent the graph.
- *Adjacency List:* While an Adjacency List is more space-efficient for sparse graphs ($O(N_v + N_e)$), the Adjacency Matrix is superior for our case ($N_v <= 1000$) because it allows $O(1)$ edge weight lookups.
- *Alternative:* If we used an Adjacency List combined with a Priority Queue, the complexity for one Dijkstra pass would be $O(N_e log N_v)$. However, since we are verifying a sequence rather than just finding the shortest path, the $O(N_v^2)$ approach is more straightforward to implement and remains extremely efficient for dense graphs (as seen in our $N_e = 100,000$ test case). The simplicity of the matrix approach also avoids the constant-time overhead associated with heap operations.

= *Declaration*

I hereby declare that this project report, along with the accompanying source code, is 
the product of my own independent work.

I have strictly abided by the academic integrity guidelines of the course. No unautho-
rized  assistance  or  code  generated  entirely  by  others  was  used  to  bypass  the  core problem-solving  requirements. I  fully  understand  that  any  form  of plagiarism, data fabrication in the testing phase, or academic misconduct is strictly prohibited.