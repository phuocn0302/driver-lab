# Driver Lab

+ Build

```sh 
# change x and y to desire module
make MOD_NAME=lx_y

# clean
make clean
```

+ Run & Test case

```sh 
#### LAB 1
sudo insmod l1_1.ko arr=1,2,3,4,5,6 n=6 num1=4 num2=44

sudo insmod l1_2.ko arr=1,2,3,4,5,6 n=6

sudo insmod l1_3.ko matrix=1,2,3,4,5,6,7,8,9 row=3 col=3

sudo insmod l1_4.ko arr=10,10,10,90,10,10 n=6

#### LAB 2
sudo insmod l2_1.ko decimal=42 hex=2A binary=101010 octal=52

sudo insmod l2_2.ko str1="  hello  world!    " str2="toi Yeu KMA"

#### LAB 3
sudo insmod l3_1.ko v1=1,2 v2=3,4 vsize=2 matrix1=1,2,3,4 row1=2 col1=2 matrix2=5,6,7,8 row2=2 col2=2

```

