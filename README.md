## Problems for AlgoLab course at ETH Zurich. Fall 2019 

You might find this of no use, but, for students at ETH, it might be interesting!

Week 7
1. Maximize it - Basic LP (max & min)
2. Diet - Basic LP - Transform a real-world problem in a LP formulation 

Week 9
1. Satellites - MinCut
2. Algocoon - MinCost MaxFlow
3. Canteen - MinCost MaxFlow with Nonnegative weights \
  Trick: Add large additive weight & compensate later.\
  Obs: For n aprox 1000, use successive_shortest_path_nonnegative_weights, NOT cycle_canceling.
4. Marathon - Keep the shortest paths from start to finish - Dijkstra using lengths of the edges. Apply flow on that graph - using the width as capacity. \n
  Obs: When adding edges (e.g. (x,y)) into a graph for flow, make checks so that the edge is added into the correct way (direction matters - add x connected to the source if the distance from the source is smaller than y's, else add y connected near the source and x to the finish node).

Potw \
Week 9 - Suez - LP \

Extra exercises \
DP problems \
1. Coin change
2. Longest increasing subsequence
3. Subset Sum
