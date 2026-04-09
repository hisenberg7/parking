#include <stdio.h>
#include <string.h>
#define SIZE 10
struct car {
    char carNumber[20];
    int moved;
};
typedef struct {
    int top;
    struct car c[SIZE];
} stack;
int empty_garage(stack *s) {
    return (s->top == -1);
}
int full_garage(stack *s) {
    return (s->top == SIZE - 1);
}
void in(stack *s, struct car c) {
    if (full_garage(s))
        printf("\n******Garage is full******\n");
    else {
        s->top++;
        s->c[s->top] = c;
    }
}
struct car out(stack *s) {
    return s->c[s->top--];
}
void garage_status(stack *s) {
    if (empty_garage(s)) {
        printf("\n****** GARAGE EMPTY ******\n");
    } else {
        printf("\n===== CAR LIST =====\n");
        for (int i = 0; i <= s->top; i++) {
            printf("Position %d : %s (Moved %d times)\n",
                   i, s->c[i].carNumber, s->c[i].moved);
        }
        printf("Total Cars: %d\n", s->top + 1);
    }
}
void arrive(stack *s) {
    struct car temp;

    if (full_garage(s)) {
        printf("\nSorry, the garage is full at this moment. Try again\n");
        return;
    }
    printf("Enter Car Number: ");
    scanf("%s", temp.carNumber);
    temp.moved = 0;
    s->top++;
    s->c[s->top] = temp;
    printf("%s has arrived at parking space number %d\n",
           temp.carNumber, s->top);
}
void depart(stack *s, stack *s1) {
    char num[20];
    struct car temp;
    int found = 0;
    if (empty_garage(s)) {
        printf("\n******Garage is empty******\n");
        return;
    }
    printf("Enter Car Number to depart: ");
    scanf("%s", num);
    while (!empty_garage(s)) {
        temp = out(s);
        if (strcmp(num, temp.carNumber) == 0) {
            found = 1;
            printf("The car %s has departed. It was moved %d times during departure\n",
                   temp.carNumber, temp.moved);
            break;
        }
        temp.moved++;
        in(s1, temp);
    }
    if (!found) {
        printf("Sorry, that car is not on this garage\n");
    }
    while (!empty_garage(s1)) {
        in(s, out(s1));
    }
}
int main() {
    stack s, s1;
    s.top = -1;
    s1.top = -1;
    char ch;
    while (1) {
        printf("\n===== Parking Garage =====\n");
        printf("A - Arrival\n");
        printf("D - Departure\n");
        printf("S - Show Cars\n");
        printf("E - Exit\n");
        printf("Enter choice: ");
        scanf(" %c", &ch);
        switch (ch) {
            case 'A':
                arrive(&s);
                break;
            case 'D':
                depart(&s, &s1);
                break;
            case 'S':
                garage_status(&s);
                break;
            case 'E':
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}