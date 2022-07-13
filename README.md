# Minesweeper-solver
A simple c++ program to solve minsweeper with moderate probability

<h4>Note: The code only works for mines percentage upto 20% of total cells, after which the probability of winning reduces drastically</h4>

<h3>Instructions:</h3>
Enter the length of the side of the mine matrix<br/>
Enter the input matrix for every step<br/>
The code will output the probability of each cell, the coordinates of the cell to choose, the minimum probability and the average probability.<br/>
Replace the chosen cell(s) with the number that is displayed after selecting it in the minesweeper game.<br/>

Min probability of >0.65 means there is a very low chance of winning the game.<br/>

Instructions for input matrix cell<br/>
-1 for square not opened<br/>
n: number of mines around a cell<br/>
Example input (6x6):<br/>
 -1 -1 -1 -1 3 -1<br/>
 2 3 3 2 -1 -1<br/>
 0 0 1 -1 4 -1<br/>
 0 0 2 -1 -1 -1<br/>
 1 1 2 -1 4 -1<br/>
 -1 -1 1 1 -1 -1<br/>
