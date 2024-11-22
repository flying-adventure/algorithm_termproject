#include <stdio.h>

int main() {
    // Redirect standard input to read from "input.txt"
    freopen("input.txt", "r", stdin);

    int n;
    while (scanf("%d", &n) != EOF) { // Read numbers until the end of the file
        int count = 0; // Minimum number of coins

        while (n > 0) {
            if (n % 5 == 0) {
                // If the amount is divisible by 5
                count += n / 5; // Use as many 5-unit coins as possible
                n = 0;
                break;
            }
            else {
                // Otherwise, subtract 2
                n -= 2;
                count++;
            }
        }

        // Handle cases where the amount cannot be given as change
        if (n < 0) {
            printf("-1\n");
        }
        else {
            printf("%d\n", count);
        }
    }

    return 0;
}
