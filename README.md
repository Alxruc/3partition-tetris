# 3partition-tetris

A tetris clone based on the 3-PARTITION reduction layed out in: Breukelaar, R., Demaine, E. D., Hohenberger, S., Hoogeboom, H. J., Kosters, W. A., & Liben-Nowell, D. (2004). Tetris is hard, even to approximate. International Journal of Computational Geometry & Applications, 14(01n02), 41-68.

This is to be used as a visual help for the reduction proof. Mainly for the Tetris objective of maximizing the number of cleared rows.

## How the level files are structured
Since each level is structured with the help of a 3-PARTITION instance, two things are required:

- In the first line you write your integers. The amount of integers should be divisible by 3

- In the second line you add your T. In the 3-PARTITION Problem you check if we can split our integers into groups of 3, so that all equal T.

Demo levels are in the partition-levels folder