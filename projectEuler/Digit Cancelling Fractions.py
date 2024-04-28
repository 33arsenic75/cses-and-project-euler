from math import gcd
st = set()
def process(a,b,c): # a and b, c is common

    num = 10*a+c
    den = 10*b+c
    if num*b == a*den and num<den:
        st.add((num,den))
    
    num = 10*c+a
    den = 10*c+b
    if num*b == a*den and num<den:
        st.add((num,den))

    num = 10*a+c
    den = 10*c+b
    if num*b == a*den and num<den:
        st.add((num,den))

    num = 10*c+a
    den = 10*b+c
    if num*b == a*den and num<den:
        st.add((num,den))




for i in range(1,10):
    for j in range(1,10):
        for k in range(1,10):
            process(i,j,k)

num = 1
den = 1
for i in st:
    print(i)
    num *= i[0]
    den *= i[1]

g = gcd(num,den)
print(num//g,den//g)
