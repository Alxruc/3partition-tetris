# 3partition-tetris

Work in progress

A tetris clone based on the 3-PARTITION reduction layed out in: Breukelaar, R., Demaine, E. D., Hohenberger, S., Hoogeboom, H. J., Kosters, W. A., & Liben-Nowell, D. (2004). Tetris is hard, even to approximate. International Journal of Computational Geometry & Applications, 14(01n02), 41-68.

This program creates a tetris level based on an instance of the 3-PARTITION problem and allows the player to play that level

Note: Even the simplest of levels like the demoLevel0, which has a total of 6 1's, meaning only 2 groups have to be formed, take some time to complete since the board grows rather quickly.

## How to play (Linux/WSL (Ubuntu))
1. Install SDL2 and SDL2 Image Packages:

```
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
```

2. Execute Makefile in root directory of this repository
```
make
```

3. Run the program
```
./bin/3partitiontetris
```


## How the level files are structured
Since each level is structured with the help of a 3-PARTITION instance, two things are required:

- In the first line you write your integers. The amount of integers should be divisible by 3

- In the second line you add your T. In the 3-PARTITION Problem you check if we can split our integers into groups of 3, so that all equal T.

Demo levels are in the partitionLevels folder