x^2 = n mod (p). Existence - n^((p-1)/2) == 1 -> there is a soln.,
else == -1, no solution.
Finding sqrt. in some Z mod p :
Cipollas Algorithm.
Find an 'a' (randomly) , s.t. a^2-n doesnt has a sqrt.
Adjoin it to the field. Take (a+sqrt(a^2-n))^((p+1)/2). 
Do all operations mod p, ans will be integer. 
Cipollas Algo works only when mod is prime.
[Remember (a+b)^p = a^p + b^p (mod p) = a + b (mod p)] 

For non-prime :

x^2 = n (mod m).
Soln. -> Compute it modulo prime powers and take CRT.
For prime powers :
We have a solution x0 mod p. We use it to find a solution (mod p^2),
then (p^3) and so on. For p^2 : x^2 = n (mod p^2); We want x to 
reduce to x0 mod p. So x=x0+p*x1. Square it. x0^2+2*x0*x1*p = n mod (p^2). 
Calculate x1.This can be extended to find for greater powers of p.
But the inverse may not exist always which may give a problem.
But then no solution or all solutions. This is called Hensel's Lifting. 
This can also be extended to find f(x) = 0 mod p^2, if we have a 
soln. for f(x) = 0 (mod p). Get something in f'(x).
