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

5. In order to apply the A* algorithm, the graph and the distance between graph's nodes must be defined.

6. In my approach the node of the graph is defined as a two-dimmensional squared array `5x5`. Each element of this array holds unique integer `x` in the range `0 <= x < 25`.

7. From the definition of sliding puzzle game, it is known, that one piece of the board is empty. Only the piece that is in the direct neighborhood of the empty slot can be moved into this position. Moving the tile the new configuration of the board is defined. That's way the next node in the the game graph is defined.

9. From the above it follows that the number of edges directed from the given node of the graph can be `2` or `3` or `4`.
    * There are `2` edges if empty slot is in the corner of the board.
    * There are `3` edges if empty slot is alligne to the border.
    * Otherwise there are `4` edges.

10. The second required input to the A* algorithm is the definition of the distance between nodes in the graph. In my approach the distance is defined as the sum of differences between positions of tiles on the board, also called [Taxicab distance](https://en.wikipedia.org/wiki/Taxicab_geometry).
