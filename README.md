# kr-std-block-cipher

Two standard block ciphers in Korea(LEA, SEED).

## Index
  - [Overview](#overview) 
  - [Demo](#Demo)
## Overview
- It is the implementation code of **SEED** and **LEA**, which are standard block ciphers in Korea.
- The silly code I wrote when I was a freshman.

## Demo

##### LEA

```
[*] LEA 128
P : 10111213 14151617 18191a1b 1c1d1e1f
K : 0f1e2d3c 4b5a6978 8796a5b4 c3d2e1f0
C : 9fc84e35 28c6c618 5532c7a7 04648bfd

[*] LEA 192
P : 20212223 24252627 28292a2b 2c2d2e2f
K : 0f1e2d3c 4b5a6978 8796a5b4 c3d2e1f0 f0e1d2c3 b4a59687
C : 6fb95e32 5aad1b87 8cdcf535 7674c6f2

[*] LEA 256
P : 30313233 34353637 38393a3b 3c3d3e3f
K : 0f1e2d3c 4b5a6978 8796a5b4 c3d2e1f0 f0e1d2c3 b4a59687 78695a4b 3c2d1e0f
C : d651aff6 47b189c1 3a8900ca 27f9e197
```

##### SEED

```
[*] SEED 128
P: 00010203 04050607 08090A0B 0C0D0E0F
C: 5EBAC6E0 054E1668 19AFF1CC 6D346CDB
```





