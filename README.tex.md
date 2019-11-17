# Collatz-Mapper
Code to create a visual representation of convergence in the generalized [Collatz Conjecture](https://en.wikipedia.org/wiki/Collatz_conjecture "Collatz Conjecture").

> Update: new version with more numpy goodness is available in the notebook "CollatzMapperPresentation". Soon it will be put in its own `.py` file.

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
  * Perform the _Collatz_ rules for 200 steps
  * Use the current $n$ value as $n_{min}+n_{init}$, where $n_{init}$ is an initialization value.
  * Perform the _Collatz_ rules again and while $n \nequal n_{min}$:
    * If at some step $n = n_{min}$, a loop has been found $\Rightarrow$ Convergence
    * If 100 steps are exceded $\Rightarrow$ No convergence
    * If $n$ is greater than a threshold value $\Rightarrow$ No convergence
    * If $n < n_{min}$, then $n_{min} \leftarrow n$ and continue


For example, for $d=2$ and for $a$ and $b$ values ranging from -2 to 2, the map would be something like this:

|   \    | **a0**   | **a1** |  ... |
| -----  | :-----: |:-------:|:----:|
| **b0** | (-2,-2) | (-2,-1) |  ... |
| **b1** | (-1,-2) | (-1,-1) |  ... |
|   ...  |   ...   |   ...   |  ... |

Each for each pair in the map a code is recorded which indicates the type of convergence:
* 0 if no convergence for any $n$
* 1 if convergence for some $n$ but not others
* 2 if convergence for all $n$ but at different values
* 3 if convergence for all $n$ at same value

The results are something like this:
![collatz Map 32x32](https://user-images.githubusercontent.com/13749006/63194636-8269fc00-c03e-11e9-9b33-f4b9088224b0.png "Pretty pretty picture #1")


## Usage
You can use the Jupyter Notebook to look at the functions included in `collatz.py`. Also, through the terminal one can use the Python script or compile the C file to generate maps. In the case of the Python script one passes the maximum positive value for a and b (from the example below, the values go from -512 to 512), the divisor, and the maximum $n$ to check for convergence:
```
python collatz.py 512 512 3 20
```

For the C file one has to edit the limits of the map in a text editor. As expected, the compiled C code runs about four times faster the Python script. I don't think it's the most optimized code possible and I didn't even use a `FILE` object to save the map just passed the output to a `.colmap` file, which is simply a text file.
```
gcc collatz.c -lm
./a.out > collatz_map.colmap
```
This is a lot better for generating big maps like this one, which took about 3 minutes:
![Collatz Map 1024x1024](https://user-images.githubusercontent.com/13749006/63195899-dd512280-c041-11e9-81fb-e37dd01c9ab6.png "Pretty pretty picture #2")
