# Collatz-Mapper
Code to create a visual representation of convergence in the generalized [Collatz Conjecture](https://en.wikipedia.org/wiki/Collatz_conjecture "Collatz Conjecture").

## About
The idea is to make a particular visual representation of the [Collatz Conjecture](https://en.wikipedia.org/wiki/Collatz_conjecture "Collatz Conjecture") where a generalized version of the conjecture is considered: <img src="/tex/353804572cedf345ba803e6221c03610.svg?invert_in_darkmode&sanitize=true" align=middle width=45.70201844999999pt height=22.831056599999986pt/> and divisor <img src="/tex/2103f85b8b1477f430fc407cad462224.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55596444999999pt height=22.831056599999986pt/>.

To do this, I implemented some simple modified definitions:
* A _d-even_ number is a number that is divisible by <img src="/tex/2103f85b8b1477f430fc407cad462224.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55596444999999pt height=22.831056599999986pt/>
* A _d-odd_ number is a number not divisible by <img src="/tex/2103f85b8b1477f430fc407cad462224.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55596444999999pt height=22.831056599999986pt/>

which lead to a slightly modified set of rules:
* if number is _d-odd_: <img src="/tex/d2cffe7ee93c83e89a7e8cd4456a8ad9.svg?invert_in_darkmode&sanitize=true" align=middle width=81.13949579999998pt height=22.831056599999986pt/>
* if number is _d-even_: <img src="/tex/d9b27e55b9c85f31f9bd659c8e3fe9a9.svg?invert_in_darkmode&sanitize=true" align=middle width=62.07952574999999pt height=24.65753399999998pt/>

Since it is impossible to figure out whether or not a given set of numbers <img src="/tex/1e521680a6030382e1f6e4906af72f5c.svg?invert_in_darkmode&sanitize=true" align=middle width=51.69711359999999pt height=24.65753399999998pt/> converge to a value for any <img src="/tex/55a049b8f161ae7cfeb0197d75aff967.svg?invert_in_darkmode&sanitize=true" align=middle width=9.86687624999999pt height=14.15524440000002pt/> and the computing time and power are also limited, some obvious compromises had to be made. The code is trying to find a loop when performing the _Collatz_ rules, like the <img src="/tex/1f6290eb665bdaa67bf1db7db2c632fa.svg?invert_in_darkmode&sanitize=true" align=middle width=39.269394449999986pt height=21.18721440000001pt/> of the <img src="/tex/93f5f9a7e819a127ffcbbaa1c1370093.svg?invert_in_darkmode&sanitize=true" align=middle width=46.39648694999999pt height=21.18721440000001pt/> case. A summary of the algorithm created is presented here:
* The <img src="/tex/2103f85b8b1477f430fc407cad462224.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55596444999999pt height=22.831056599999986pt/> value is fixed
* A pair <img src="/tex/ba933e77b90dc996befbe81f77f43887.svg?invert_in_darkmode&sanitize=true" align=middle width=35.83526759999999pt height=24.65753399999998pt/> is chosen
* For each <img src="/tex/55a049b8f161ae7cfeb0197d75aff967.svg?invert_in_darkmode&sanitize=true" align=middle width=9.86687624999999pt height=14.15524440000002pt/>, from <img src="/tex/3d2be9e2108301e9097fa4bc51046641.svg?invert_in_darkmode&sanitize=true" align=middle width=40.00371704999999pt height=21.18721440000001pt/> up to <img src="/tex/7adb89ee6106df767245caf173b44ebd.svg?invert_in_darkmode&sanitize=true" align=middle width=48.222926399999984pt height=21.18721440000001pt/>:
  * Perform the _Collatz_ rules for 200 steps
  * Use the current <img src="/tex/55a049b8f161ae7cfeb0197d75aff967.svg?invert_in_darkmode&sanitize=true" align=middle width=9.86687624999999pt height=14.15524440000002pt/> value as <img src="/tex/05dc7ff297651ac0e4353b2b8137d704.svg?invert_in_darkmode&sanitize=true" align=middle width=87.48222119999998pt height=19.1781018pt/>, where <img src="/tex/375c472ede34fd86611aaaeafaad3f08.svg?invert_in_darkmode&sanitize=true" align=middle width=32.26048979999999pt height=14.15524440000002pt/> is an initialization value.
  * Perform the _Collatz_ rules again and while <img src="/tex/c5b9dbd3d9a36953925b7148a1b48e6a.svg?invert_in_darkmode&sanitize=true" align=middle width=44.17552589999999pt height=14.15524440000002pt/>:
    * If at some step $n = n_{min}$, a loop has been found $\Rightarrow$ Convergence
    * If 100 steps are exceded $\Rightarrow$ No convergence
    * If $n$ is greater than a threshold value $\Rightarrow$ No convergence
    * If $n < n_{min}$, then $n_{min} \leftarrow n$ and continue


For example, for <img src="/tex/e675da7c7f7c3d89bc6087aab1186a27.svg?invert_in_darkmode&sanitize=true" align=middle width=38.69280359999998pt height=22.831056599999986pt/> and for <img src="/tex/44bc9d542a92714cac84e01cbbb7fd61.svg?invert_in_darkmode&sanitize=true" align=middle width=8.68915409999999pt height=14.15524440000002pt/> and <img src="/tex/4bdc8d9bcfb35e1c9bfb51fc69687dfc.svg?invert_in_darkmode&sanitize=true" align=middle width=7.054796099999991pt height=22.831056599999986pt/> values ranging from -2 to 2, the map would be something like this:

|   \    | **a0**   | **a1** |  ... |
| -----  | :-----: |:-------:|:----:|
| **b0** | (-2,-2) | (-2,-1) |  ... |
| **b1** | (-1,-2) | (-1,-1) |  ... |
|   ...  |   ...   |   ...   |  ... |

Each for each pair in the map a code is recorded which indicates the type of convergence:
* 0 if no convergence for any <img src="/tex/55a049b8f161ae7cfeb0197d75aff967.svg?invert_in_darkmode&sanitize=true" align=middle width=9.86687624999999pt height=14.15524440000002pt/>
* 1 if convergence for some <img src="/tex/55a049b8f161ae7cfeb0197d75aff967.svg?invert_in_darkmode&sanitize=true" align=middle width=9.86687624999999pt height=14.15524440000002pt/> but not others
* 2 if convergence for all <img src="/tex/55a049b8f161ae7cfeb0197d75aff967.svg?invert_in_darkmode&sanitize=true" align=middle width=9.86687624999999pt height=14.15524440000002pt/> but at different values
* 3 if convergence for all <img src="/tex/55a049b8f161ae7cfeb0197d75aff967.svg?invert_in_darkmode&sanitize=true" align=middle width=9.86687624999999pt height=14.15524440000002pt/> at same value

The results are something like this:
[Div=2]
( "Collatz Map for Div=2")
