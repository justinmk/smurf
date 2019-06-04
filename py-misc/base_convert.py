def base16_encode(n):
    alphabet = '0123456789abcdef'
    if n == 0:
        return '0'
    remainder = n
    s = ''
    while remainder > 0:
        s = alphabet[remainder % 16] + s
        remainder = remainder // 16
    return s

def base16_decode(s):
    pass

print(base16_encode(42731))
print(base16_encode(0))
