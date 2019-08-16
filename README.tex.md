# Collatz-Mapper
Code to create a visual representation of convergence in the generalized [Collatz Conjecture](https://en.wikipedia.org/wiki/Collatz_conjecture "Collatz Conjecture").

## About
The idea is to make a particular visual representation of the [Collatz Conjecture](https://en.wikipedia.org/wiki/Collatz_conjecture "Collatz Conjecture") where a generalized version of the conjecture is considered: $a n + b$ and divisor $d$.

To do this, I implemented some simple modified definitions:
* A _d-even_ number is a number that is divisible by $d$
* A _d-odd_ number is a number not divisible by $d$

which lead to a slightly modified set of rules:
* if number is _d-odd_: $n \leftarrow an+b$
* if number is _d-even_: $n \leftarrow n/d$

Since it is impossible to figure out whether or not a given set of numbers $(a, b, d)$ converge to a value for any $n$ and the computing time and power are also limited, some obvious compromises had to be made. The code is trying to find a loop when performing the _Collatz_ rules, like the $1, 4, 2$ of the $3n+1$ case. A summary of the algorithm created is presented here:
* The $d$ value is fixed
* A pair $(a, b)$ is chosen
* For each $n$, from $n=1$ up to $n=20$:
..* Perform the _Collatz_ rules for 200 steps
..* Use the current $n$ value as $n_{min}+n_{init}$, where $n_{init}$ is an initialization value.
..* Perform the _Collatz_ rules again and while $n \nequal n_{min}$:
....* If at some step $n = n_{min}$, a loop has been found $\Rightarrow$ Convergence
....* If 100 steps are exceded $\Rightarrow$ No convergence
....* If $n$ is greater than a threshold value $\Rightarrow$ No convergence
....* If $n < n_{min}$, then $n_{min} \leftarrow n$


Then, I take a list of n values, from 1 to 20, and noting for how many of them there is a convergence for each pair $(a, b)$. If the rules return a value bigger than a certain threshold or if a certain number of steps are exceded, it is taken to mean there is no convergence for that triple $(a, b, n)$
