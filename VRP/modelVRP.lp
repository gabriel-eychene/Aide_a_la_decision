\ENCODING=ISO-8859-1
\Problem name: IloCplex

Minimize
 obj1: 0 x(0,0) + 13.8924439894498 x(0,1) + 21.0237960416286 x(0,2)
       + 32.5576411921994 x(0,3) + 17.2046505340853 x(0,4)
       + 13.8924439894498 x(1,0) + 0 x(1,1) + 12.369316876853 x(1,2)
       + 19.2093727122985 x(1,3) + 31.0644491340181 x(1,4)
       + 21.0237960416286 x(2,0) + 12.369316876853 x(2,1) + 0 x(2,2)
       + 15.2970585407784 x(2,3) + 37.0135110466435 x(2,4)
       + 32.5576411921994 x(3,0) + 19.2093727122985 x(3,1)
       + 15.2970585407784 x(3,2) + 0 x(3,3) + 49.6789693934969 x(3,4)
       + 17.2046505340853 x(4,0) + 31.0644491340181 x(4,1)
       + 37.0135110466435 x(4,2) + 49.6789693934969 x(4,3) + 0 x(4,4)
Subject To
 c1(1):    x(0,1) + x(2,1) + x(3,1) + x(4,1)  = 1
 c1(2):    x(0,2) + x(1,2) + x(3,2) + x(4,2)  = 1
 c1(3):    x(0,3) + x(1,3) + x(2,3) + x(4,3)  = 1
 c1(4):    x(0,4) + x(1,4) + x(2,4) + x(3,4)  = 1
 c2(1):    x(1,0) + x(1,2) + x(1,3) + x(1,4)  = 1
 c2(2):    x(2,0) + x(2,1) + x(2,3) + x(2,4)  = 1
 c2(3):    x(3,0) + x(3,1) + x(3,2) + x(3,4)  = 1
 c2(4):    x(4,0) + x(4,1) + x(4,2) + x(4,3)  = 1
 c3(1)(0): 50 x(1,0) + a(0) - a(1) <= 43
 c3(1)(1): 50 x(1,2) - a(1) + a(2) <= 43
 c3(1)(2): 50 x(1,3) - a(1) + a(3) <= 43
 c3(1)(3): 50 x(1,4) - a(1) + a(4) <= 43
 c3(2)(0): 50 x(2,0) + a(0) - a(2) <= 20
 c3(2)(1): 50 x(2,1) + a(1) - a(2) <= 20
 c3(2)(2): 50 x(2,3) - a(2) + a(3) <= 20
 c3(2)(3): 50 x(2,4) - a(2) + a(4) <= 20
 c3(3)(0): 50 x(3,0) + a(0) - a(3) <= 34
 c3(3)(1): 50 x(3,1) + a(1) - a(3) <= 34
 c3(3)(2): 50 x(3,2) + a(2) - a(3) <= 34
 c3(3)(3): 50 x(3,4) - a(3) + a(4) <= 34
 c3(4)(0): 50 x(4,0) + a(0) - a(4) <= 41
 c3(4)(1): 50 x(4,1) + a(1) - a(4) <= 41
 c3(4)(2): 50 x(4,2) + a(2) - a(4) <= 41
 c3(4)(3): 50 x(4,3) + a(3) - a(4) <= 41
 c4(1):    a(1) - Rgc4(1)  = 7
 c4(2):    a(2) - Rgc4(2)  = 30
 c4(3):    a(3) - Rgc4(3)  = 16
 c4(4):    a(4) - Rgc4(4)  = 9
Bounds
 0 <= x(0,0) <= 1
 0 <= x(0,1) <= 1
 0 <= x(0,2) <= 1
 0 <= x(0,3) <= 1
 0 <= x(0,4) <= 1
 0 <= x(1,0) <= 1
 0 <= x(1,1) <= 1
 0 <= x(1,2) <= 1
 0 <= x(1,3) <= 1
 0 <= x(1,4) <= 1
 0 <= x(2,0) <= 1
 0 <= x(2,1) <= 1
 0 <= x(2,2) <= 1
 0 <= x(2,3) <= 1
 0 <= x(2,4) <= 1
 0 <= x(3,0) <= 1
 0 <= x(3,1) <= 1
 0 <= x(3,2) <= 1
 0 <= x(3,3) <= 1
 0 <= x(3,4) <= 1
 0 <= x(4,0) <= 1
 0 <= x(4,1) <= 1
 0 <= x(4,2) <= 1
 0 <= x(4,3) <= 1
 0 <= x(4,4) <= 1
 0 <= a(0) <= 50
 0 <= a(1) <= 50
 0 <= a(2) <= 50
 0 <= a(3) <= 50
 0 <= a(4) <= 50
 0 <= Rgc4(1) <= 43
 0 <= Rgc4(2) <= 20
 0 <= Rgc4(3) <= 34
 0 <= Rgc4(4) <= 41
Binaries
 x(0,0)  x(0,1)  x(0,2)  x(0,3)  x(0,4)  x(1,0)  x(1,1)  x(1,2)  x(1,3) 
 x(1,4)  x(2,0)  x(2,1)  x(2,2)  x(2,3)  x(2,4)  x(3,0)  x(3,1)  x(3,2) 
 x(3,3)  x(3,4)  x(4,0)  x(4,1)  x(4,2)  x(4,3)  x(4,4) 
Generals
 a(0)  a(1)  a(2)  a(3)  a(4) 
End
