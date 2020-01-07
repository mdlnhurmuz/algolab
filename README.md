## Problems for AlgoLab course at ETH Zurich. Fall 2019 

You might find this of no use, but, for students at ETH, it might be interesting!

### Week 1
1. **Even Pairs** - Number of pairs 0 <= i <= j < n such that sum xij is even. \
  Steps: Keep partial sums. Compute the number of even sums and odd sums. \
  Result: Comb(E, 2) + Comb(O, 2) + E.
2. **Build the Sum**
3. **Dominoes** - 2 pointers technique 
4. **Even Matrices** - Compute partial sums on matrix + Even pairs combination

### Week 2

Tutorial DP + Sliding window <br>
Sliding window idea: 
- Keep two pointers that keep track of the current interval (window) 
- If the value of the window is too large: increase the left pointer 
- If the value of the window is too small: increase the right pointer 
Some problems in which you need to find some optimal interval can be solved in linear time using a similar sliding window approach. 

1. **Search Snippets**
2. **Beach Bars**
3. **Burning Coins**
4. **The Great Game** 

### Week 3

Tutorial CGAL (1)
1. CGAL::Exact_predicates_inexact_constructions_kernel "Epic"
2. CGAL::Exact_predicates_exact_constructions_kernel "Epec"
3. CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt "Epecsqrt" (e.g. CGAL::sqrt)

Fast to slow: Epic -> Epec -> Epecsqrt <br>
Guideline #1: Avoid (square) roots! <br>
For x, y >= 0: sqrt(x) < sqrt(y) <=> x < y.  <br>
Guideline #2: Avoid divisions! <br>
For b,d > 0: a/b < c/d <=> ad < bc. <br>

Obs: Use two kernels in one problem: inexact kernel for predicates only (e.g. CGAL::left_turn) and the exact kernel for the non-trivial constructions (e.g. circle.has_on_boundary(point)). 

Steps to run with CGAL <br>
- Run cgal_create_cmake_script 
- Add 
 include( ${CGAL_USE_FILE} ) \
 include( CGAL_CreateSingleSourceCGALProgram ) \
 create_single_source_cgal_program( "first_hit.cpp" ) \
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
- cmake . <br>
- make && ./hello-exact

1. **Hit** <br>
  For checking the existence of possible intersections, use CGAL::orientation and CGAL::do_intersect. If we have a ray with a start point S and a direction D and a line segment with two points X and Y, we compute orientation for (S, D, X) and (S, D, Y) and if these two values are negative, it means that X and Y are on different parts of the ray, so it might be a chance of intersection and we can call do_intersect. 
2. **First hit** <br>
- We do not need roots, but we construct intersection points. Therefore, using EPEC makes sense. <br>
- Input number are up to 51 bits => LONG <br>
- Implementation idea: <br>
  - Use clipping (from ray to segment) <br>
  - Clip the ray at each segment hit (cuts down on the number of intersection points to be constructed) <br>
  - Use random shuffle on the segments for a uniformly random permutation of an n element set <br>
3. **Antenna** - Min circle & Find roots (EPECSQRT)
4. **Almost Antenna** - Min circle & Try erasing one point to find minimum radius (EPECSQRT)

### Week 4

Tutorial BGL (1)
BGL outlook:
- *breadth_first_search*
- strongly connected components in directed graphs (*strong_components*)
- connected components in undirected graphs (*connected_components*)
- *is_bipartite*
- minimum spanning tree (*kruskal_minimum_spanning_tree*, *prim_minimum_spanning_tree*)

1. **First steps with BGL** - Kruskal & Dijkstra 
2. **Ant Challenge** - 60 points: Run Prim for every species to establish its network & Dijkstra from source to destination on the smallest weight given all the possible ones from the established networks 
3. **Buddy Selection** <br>
- Set intersection (sort and 2 pointers to keep track of common elements)
- If the number of common elements > 1, then we have an edge
- We have a maximum matching problem <=> bipartite graph - flow formulation through vertex capacities
- The graph has n * 2 + 2 nodes. Put an edge of capacity 1 from source, to the first n nodes and same for target and last n nodes. Add an edge of capacity 1, between the 2 rounds of nodes, if they share more than f characteristics. 
4. **Shortest Paths** - Dijkstra 

### Week 6
 
 Tutorial BGL (2)
 Maximum flows:
 - *push_relabel_max_flow* - almost always
 - *edmonds_karp_max_flow* - almost never
 Common techniques:
 - multiple sources/sinks - edges with infinite capacity from the source and to the target
 - vertex capacities - split in-vertexes and out-vertexes and put an edge of capacity 1 from in-vertexes to out-vertexes
 - undirected graphs - undirected edge (v, w) with capacity 4 will become directed edge (v, w) with capacity 4 and directed edge (w, v) with capacity 4
 - edge with constraints 
 <br>
 Lemma (Flow Decomposition): In a directed graph with unit capacities, the maximum number of edge disjoint s-t-paths is equal to the maximum flow ,from s to t. 
<br>
Circulation problem - solving with max-flow
<br>

1. **Coin tossing** - Max flow
2. **Shopping trip** - Max flow - Every store linked with the target. 
3. **Tetris** - Vertex capacities of 1 and edge capacities of 1 <br>
Obs:
- "Left end does not necessarily come first"
- Attention there might be nodes from 0 to w, from v_source to v_target directly.
4. **London** - Max flow with constraints on edges

### Week 7
1. **Maximize it** - Basic LP (max & min)
2. **Diet** - Basic LP - Transform a real-world problem in a LP formulation 

### Week 9
1. **Satellites** - MinCut
2. **Algocoon** - MinCost MaxFlow
3. **Canteen** - MinCost MaxFlow with Nonnegative weights \
  Trick: Add large additive weight & compensate later.\
  Obs: For n aprox 1000, use successive_shortest_path_nonnegative_weights, NOT cycle_canceling.
4. **Marathon** - Keep the shortest paths from start to finish - Dijkstra using lengths of the edges. Apply flow on that graph - using the width as capacity. \
  Obs: When adding edges (e.g. (x,y)) into a graph for flow, make checks so that the edge is added into the correct way (direction matters - add x connected to the source if the distance from the source is smaller than y's, else add y connected near the source and x to the finish node).

### Week 13
1. **Bob's Burden** - Shortest Paths (Dijkstra) \
  Obs: Convert from a lower triangular matrix (see from (i, j) to one-dimensional mapping). \
  From weights in the nodes to weights on edges (directed graph). All nodes are connected to the balls around them (could be up to 6 neighbours). All the neighbours of a node, when they want to get in the node, they will pay the price of that node (its weight), so we put edges from the children to the node with the cost of the node. \
  Note: If 0 is a neighbour of 1, also 1 is a neighbour of 0. So, in a setting with three balls (one up and two down), we will have 6 edges.   \
  Apply Dijkstra from all the three specials balls and sum up the values. The minimum value among those sums is the result. 

### Potw 
Week 9 - **Suez** - LP

### Extra exercises 
DP problems
1. **Coin change**
2. **Longest increasing subsequence**
3. **Subset Sum**
4. **Knapsack** TODO
5. **Longest common subsequence** TODO
6. **Edit distance** TODO
