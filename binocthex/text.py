text = "Alex E"
print(*[format(ord(letter),'08b') for letter in text])

phrase = [
    0b1000001,
    0b01101100,
    0b01110111,
    0b01100001,
    0b01111001,
    0b01110011,
    0b00100000,
    0b01100100,

    0b01101111,
    0b00100000,
    0b01011001,
    0b01001111,
    0b01010101,
    0b01010010,
    0b00100000,
    0b01100010,
    0b01100101,
    0b01110011,
    0b01110100,
    0b00100001
]

print(*[chr(letter) for letter in phrase], sep="")



