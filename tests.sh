./nm nm > test/1
nm nm > test/2
diff test/1 test/2

./nm nm nm > test/3
nm nm nm > test/4
diff test/3 test/4

./nm nm -A > test/5
nm nm -A > test/6
diff test/6 test/5

./nm nm nm -A > test/7
nm nm nm -A > test/8
diff test/7 test/8

./nm nm -p > test/9
nm nm -p > test/10
diff test/10 test/9

./nm nm nm -p > test/11
nm nm nm -p > test/12
diff test/11 test/12

./nm nm -r > test/13
nm nm -r > test/14
diff test/13 test/14

./nm nm nm -r > test/15
nm nm nm -r > test/16
diff test/16 test/15

./nm nm -j > test/17
nm nm -j > test/18
diff test/17 test/18

./nm nm nm -j > test/19
nm nm nm -j > test/20
diff test/19 test/20

./nm nm -rAj > test/21
nm nm -rAj > test/22
diff test/21 test/22

./nm nm nm -rAj > test/23
nm nm nm -rAj > test/24
diff test/23 test/24