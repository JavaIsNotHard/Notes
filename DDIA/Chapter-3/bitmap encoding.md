compression technique used in column oriented storage 

each unique value in the column are represented in a bitmap which contains N cells where N is the no of total columns 

the value of each cell in the bitmap is either 0 or 1 depending on whether the value is present in that position or not. 