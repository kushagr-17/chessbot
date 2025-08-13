# Chess Engine using 0x88 notation
This is a C++ chess engine under development, using **0x88 board representation**.

# About 0x88 notation
The 0x88 board representation encodes the chessboard into a 1D array of 128 elements, where:

- Valid squares range from 0x00 to 0x77 (file and rank encoded in hex)

- Off-board squares have the 0x88 bit set

- This allows ultra-fast boundary checking

 Only the half of the board-array are valid squares representing the position. The second half is almost garbage as usually not addressed. The little-endian layout of an 0x88 array, valid indices red:
|   | A      | B      | C      | D      | E      | F      | G      | H      |    |    |    |    |    |    |    |    |
| - | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | -- | -- | -- | -- | -- | -- | -- | -- |
| 8 | <span style="color:red;">**70**</span> | <span style="color:red;">**71**</span> | <span style="color:red;">**72**</span> | <span style="color:red;">**73**</span> | <span style="color:red;">**74**</span> | <span style="color:red;">**75**</span> | <span style="color:red;">**76**</span> | <span style="color:red;">**77**</span> | 78 | 79 | 7A | 7B | 7C | 7D | 7E | 7F |
| 7 | <span style="color:red;">**60**</span> | <span style="color:red;">**61**</span> | <span style="color:red;">**62**</span> | <span style="color:red;">**63**</span> | <span style="color:red;">**64**</span> | <span style="color:red;">**65**</span> | <span style="color:red;">**66**</span> | <span style="color:red;">**67**</span> | 68 | 69 | 6A | 6B | 6C | 6D | 6E | 6F |
| 6 | <span style="color:red;">**50**</span> | <span style="color:red;">**51**</span> | <span style="color:red;">**52**</span> | <span style="color:red;">**53**</span> | <span style="color:red;">**54**</span> | <span style="color:red;">**55**</span> | <span style="color:red;">**56**</span> | <span style="color:red;">**57**</span> | 58 | 59 | 5A | 5B | 5C | 5D | 5E | 5F |
| 5 | <span style="color:red;">**40**</span> | <span style="color:red;">**41**</span> | <span style="color:red;">**42**</span> | <span style="color:red;">**43**</span> | <span style="color:red;">**44**</span> | <span style="color:red;">**45**</span> | <span style="color:red;">**46**</span> | <span style="color:red;">**47**</span> | 48 | 49 | 4A | 4B | 4C | 4D | 4E | 4F |
| 4 | <span style="color:red;">**30**</span> | <span style="color:red;">**31**</span> | <span style="color:red;">**32**</span> | <span style="color:red;">**33**</span> | <span style="color:red;">**34**</span> | <span style="color:red;">**35**</span> | <span style="color:red;">**36**</span> | <span style="color:red;">**37**</span> | 38 | 39 | 3A | 3B | 3C | 3D | 3E | 3F |
| 3 | <span style="color:red;">**20**</span> | <span style="color:red;">**21**</span> | <span style="color:red;">**22**</span> | <span style="color:red;">**23**</span> | <span style="color:red;">**24**</span> | <span style="color:red;">**25**</span> | <span style="color:red;">**26**</span> | <span style="color:red;">**27**</span> | 28 | 29 | 2A | 2B | 2C | 2D | 2E | 2F |
| 2 | <span style="color:red;">**10**</span> | <span style="color:red;">**11**</span> | <span style="color:red;">**12**</span> | <span style="color:red;">**13**</span> | <span style="color:red;">**14**</span> | <span style="color:red;">**15**</span> | <span style="color:red;">**16**</span> | <span style="color:red;">**17**</span> | 18 | 19 | 1A | 1B | 1C | 1D | 1E | 1F |
| 1 | <span style="color:red;">**00**</span> | <span style="color:red;">**01**</span> | <span style="color:red;">**02**</span> | <span style="color:red;">**03**</span> | <span style="color:red;">**04**</span> | <span style="color:red;">**05**</span> | <span style="color:red;">**06**</span> | <span style="color:red;">**07**</span> | 08 | 09 | 0A | 0B | 0C | 0D | 0E | 0F |
|   | A      | B      | C      | D      | E      | F      | G      | H      |    |    |    |    |    |    |    |    |
				