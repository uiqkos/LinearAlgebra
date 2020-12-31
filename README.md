# LinearAlgebra
Linear algebra with c++ 
## Examples
#### Print
```cpp
Matrix matrix1 = Matrix(3, 3, vector<int>{1, 2, 3, 0, 4, 5, 1, 0, 6}); 
matrix1.Print();
```
```
1 2 3  
0 4 5  
1 0 6  
```
####Transpose
```cpp    
Matrix matrix1 = Matrix(3, 3, vector<int>{1, 2, 3, 0, 4, 5, 1, 0, 6});
Transpose(matrix1).Print();
```
```
1 0 1
2 4 0
3 5 6
```
#### Multiply
```cpp
Matrix matrix1 = Matrix(3, 3, vector<int>{1, 2, 3, 0, 4, 5, 1, 0, 6});
Matrix matrix2 = Matrix(3, 2, vector<int>{-5, -7, 9, 6, -9, -9});
Multiply(matrix1, matrix2).Print(); // or (matrix1 * matrix2).Print(); 
```
```
-14 -22
-9 -21
-59 -61
```
#### Slices
```cpp
matrix1.MakeSlice(0, 0, 1, 1).Print(); // from (0, 0) to (1, 1)

1 2
0 4
```

```cpp
matrix1.MakeSlice(0, 0, -1, 0).Print(); // first column

1
0
1
```
```cpp
matrix1.MakeSlice(-1, -1, -1, 0).Print(); // last row reversed

6 0 1
```
```cpp
matrix1.MakeSlice(-1, -1, 0, 0).Print(); // reversed matrix

6 0 1
5 4 0
3 2 1
```
#### Casts
#### Reshape
#### Operators
#### Determinant
#### Concatenate
#### Fractions
##TODOs
1. Add norm readme
2. Optimize Multiply
3. Finish Inverse
4. System of linear equations
5. Iterators
6. Add Vector (mb)
