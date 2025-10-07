# Chess Engine using 0x88 notation
This is a C++ chess engine under development, using **0x88 board representation**.
This project is being built step by step, starting from board setup and move generation towards a fully working UCI-compatible chess engine.

# About 0x88 notation
The 0x88 board representation encodes the chessboard into a 1D array of 128 elements, where:

- Valid squares range from 0x00 to 0x77 (file and rank encoded in hex)

- Off-board squares have the 0x88 bit set

- This allows ultra-fast boundary checking

 Only the half of the board-array are valid squares representing the position. The second half is almost garbage as usually not addressed. The little-endian layout of an 0x88 array, valid indices bold (under marked columns):

|   | A      | B      | C      | D      | E      | F      | G      | H      |    |    |    |    |    |    |    |    |
| - | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | -- | -- | -- | -- | -- | -- | -- | -- |
| 8 | **70** | **71** | **72** | **73** | **74** | **75** | **76** | **77** | 78 | 79 | 7A | 7B | 7C | 7D | 7E | 7F |
| 7 | **60** | **61** | **62** | **63** | **64** | **65** | **66** | **67** | 68 | 69 | 6A | 6B | 6C | 6D | 6E | 6F |
| 6 | **50** | **51** | **52** | **53** | **54** | **55** | **56** | **57** | 58 | 59 | 5A | 5B | 5C | 5D | 5E | 5F |
| 5 | **40** | **41** | **42** | **43** | **44** | **45** | **46** | **47** | 48 | 49 | 4A | 4B | 4C | 4D | 4E | 4F |
| 4 | **30** | **31** | **32** | **33** | **34** | **35** | **36** | **37** | 38 | 39 | 3A | 3B | 3C | 3D | 3E | 3F |
| 3 | **20** | **21** | **22** | **23** | **24** | **25** | **26** | **27** | 28 | 29 | 2A | 2B | 2C | 2D | 2E | 2F |
| 2 | **10** | **11** | **12** | **13** | **14** | **15** | **16** | **17** | 18 | 19 | 1A | 1B | 1C | 1D | 1E | 1F |
| 1 | **00** | **01** | **02** | **03** | **04** | **05** | **06** | **07** | 08 | 09 | 0A | 0B | 0C | 0D | 0E | 0F |
|   | A      | B      | C      | D      | E      | F      | G      | H      |    |    |    |    |    |    |    |    |
				
## Features Implemented
### Board Representation
- **0x88 board representation**
- Support for:
  - Piece placement from **FEN**.
  - Side-to-move tracking.
  - Castling rights (`KQkq`).
  - En passant square.
  - Halfmove/fullmove counters.

### Move Representation
- `Move` struct with:
  - from, to squares
  - moving piece
  - captured piece (if any)
  - promoted piece (if any)
  - flags (capture, promotion, en passant, castle)

### Move Generation
- **Pseudo-legal move generation**:
  - Pawn pushes, captures, promotions, en passant
  - Knight, Bishop, Rook, Queen, King moves
  - Castling moves
- **Legal move filtering** using:
  - `isSquareAttacked()`
  - `makeMove()` and `undoMove()`

### Perft Testing
- Implemented `perft(depth)` and `perftDivide(depth)` for validating move generation.
- Verified against known perft numbers up to **depth 6**:
```
Perft(1) = 20 [Time: 3.86e-05 sec, 518134 NPS] 
Perft(2) = 400 [Time: 0.0002554 sec, 1566170 NPS] 
Perft(3) = 8902 [Time: 0.0035115 sec, 2535098 NPS] 
Perft(4) = 197281 [Time: 0.0543623 sec, 3629003 NPS] 
Perft(5) = 4865609 [Time: 1.32475 sec, 3672840 NPS] 
Perft(6) = 119060324 [Time: 37.3176 sec, 3190458 NPS]
```
- Perft outputs include timing and NPS (nodes per second).

## Next Steps
- Implement a **basic evaluation function** (material count + piece-square bonuses).
- Add a **minimax search with alpha-beta pruning**.
- Return best moves for given positions at fixed depth.
- Extend CLI into full **UCI protocol**

## Build & Run

```bash
g++ -std=c++17 main.cpp board.cpp utils.cpp movegen.cpp perft.cpp -o chessbot
./chessbot
```

## References
- [Chess Programming Wiki](https://www.chessprogramming.org/Main_Page)
- [r/chessprogramming](https://www.reddit.com/r/chessprogramming)
- [Stockfish's official Github](https://github.com/official-stockfish/Stockfish)
- [Major Carry Job](https://chatgpt.com)
- [Evaluation Function](https://hxim.github.io/Stockfish-Evaluation-Guide)