# Sliding puzzle game

1. This program solves [Sliding puzzle](https://en.wikipedia.org/wiki/Sliding_puzzle) for the board of size `5x5`, i.e. **puzzle 24 game**.

```
--------------------------
|  1 |  2 |  3 |  4 | 5  |
|  6 |  7 |  8 |  9 | 10 |
| 11 | 12 | 13 | 14 | 15 |    The final configuration for puzzle 24 game.
| 16 | 17 | 18 | 19 | 20 |
| 21 | 22 | 23 | 24 | F  |
--------------------------
F denotes free slot
```


2. There is the wiki article about [15 puzzle](https://en.wikipedia.org/wiki/15_puzzle) game with board of size `4x4`.

3. The [A* algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm) has been implemeted for solving the puzzle 24 game.

4. The input to the game is the initial configuration on the board. The solutions is the sequence of moves leading from the initial configuration to the final configuration. The final configuration for puzzle 24 game is presented above.

5. In order to apply the A* algorithm must define the graph and the distance between graph's node.

6. In my approach the node of the graph is defined as a two-dimmensional squared array `5x5`. Each element of this array holds unique integer `x` in the range `0 <= x < 25`.
