from math import sqrt
import math
N = 1000
a = (1 + sqrt(5))/2
b = (1 - sqrt(5))/2
i = 1
logc = math.log10(5)/2 + N - 1
loga = math.log10(a)
ans = logc/loga
print(ans)
