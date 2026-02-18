
numRange:int = 64

print(" Dec |   Bin  | Oct | Hex  | "*2)
print(" ------------------------  |"*2)
for i in range(numRange//2):
    num1 = i*2+1
    num2 = num1+1
    print(f"  {format(num1,'02d')} | {format(num1,'06b')} | {format(num1,'03o')} | {format(num1,'02x')}"+
          "   | "+ 
          f"  {format(num2,'02d')} | {format(num2,'06b')} | {format(num2,'03o')} | {format(num2,'02x')}")
