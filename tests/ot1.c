//int foo() {
//    int x;
//    int y;
//    return 2;
//}

void main() {
    int x = 1;
    switch (x) {
        case 1: {
            int y = 10;
            switch (y) {
                case 10: printi(10); break;
                case 11: printi(11);// break;
                //default: printi(0);
            }
            printi(1111);
            break;
        }
        case 2: printi(2); break;
        case 3: printi(3); //break;
        case 4: printi(4);
        default: printi(0);
    }
    printi(5555);


}