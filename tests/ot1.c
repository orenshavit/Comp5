int fib(byte n) {
    if (n == 0 or n == 1) return 1;
    return fib(n-1b) + fib(n-2b);
}

void main() {
    byte i = 0b;
    while (i < 10) {
        printi(fib(i));
        i = i + 1b;
    }
    print("*");
}