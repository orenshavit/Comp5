

void main() {
    int x = 1;
    byte y = 1b;
    while (x < 10 and y < 5b) {
        x = x + x;
        y = y + 1b;
    }
    printi(x);
    int z = y;
    printi(z);
}