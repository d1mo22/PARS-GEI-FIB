#include <unistd.h>

int main() {
    char c;

    read(0, &c, sizeof(char));
    write(1, &c, sizeof(char));
}
