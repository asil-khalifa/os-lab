#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

int compare(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

void fcfs(int req[], int n, int head) {
    int total = 0;
    printf("FCFS Order: %d", head);
    for (int i = 0; i < n; i++) {
        total += abs(req[i] - head);
        head = req[i];
        printf(" -> %d", head);
    }
    printf("\nTotal Seek Time: %d\n", total);
}

void sstf(int req[], int n, int head) {
    int local[MAX];
    int visited[MAX] = {0};
    for (int i = 0; i < n; i++) local[i] = req[i];

    int total = 0;
    printf("SSTF Order: %d", head);

    for (int i = 0; i < n; i++) {
        int min = 1e9, index = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(local[j] - head) < min) {
                min = abs(local[j] - head);
                index = j;
            }
        }
        visited[index] = 1;
        total += abs(local[index] - head);
        head = local[index];
        printf(" -> %d", head);
    }
    printf("\nTotal Seek Time: %d\n", total);
}

void scan(int req[], int n, int head, int size, int dir) {
    int local[MAX];
    for (int i = 0; i < n; i++) local[i] = req[i];
    local[n++] = head;
    local[n++] = (dir == 1 ? size - 1 : 0);

    qsort(local, n, sizeof(int), compare);
    int i;
    for (i = 0; i < n; i++) if (local[i] == head) break;

    printf("SCAN Order: ");

    if (dir == 1) {
        for (int j = i; j < n; j++) printf("%d -> ", local[j]);
        for (int j = i - 1; j >= 0; j--) printf("%d -> ", local[j]);
    } else {
        for (int j = i; j >= 0; j--) printf("%d -> ", local[j]);
        for (int j = i + 1; j < n; j++) printf("%d -> ", local[j]);
    }

    int total = abs(head - (dir == 1 ? size - 1 : 0)) + abs(local[0] - local[n - 2]);
    printf("\b\b  \nTotal Seek Time: %d\n", total);
}

void cscan(int req[], int n, int head, int size, int dir) {
    int local[MAX];
    for (int i = 0; i < n; i++) local[i] = req[i];
    local[n++] = head;
    local[n++] = 0;
    local[n++] = size - 1;

    qsort(local, n, sizeof(int), compare);
    int i;
    for (i = 0; i < n; i++) if (local[i] == head) break;

    printf("C-SCAN Order: ");

    if (dir == 1) {
        for (int j = i; j < n; j++) printf("%d -> ", local[j]);
        for (int j = 0; j < i; j++) printf("%d -> ", local[j]);
    } else {
        for (int j = i; j >= 0; j--) printf("%d -> ", local[j]);
        for (int j = n - 1; j > i; j--) printf("%d -> ", local[j]);
    }

    int total = (dir == 1)
        ? (size - 1 - head + size - 1)
        : (head + size - 1);

    printf("\b\b  \nTotal Seek Time: %d\n", total);
}

void look(int req[], int n, int head, int dir) {
    int local[MAX];
    for (int i = 0; i < n; i++) local[i] = req[i];
    local[n++] = head;

    qsort(local, n, sizeof(int), compare);
    int i;
    for (i = 0; i < n; i++) if (local[i] == head) break;

    printf("LOOK Order: ");

    int total;
    if (dir == 1) {
        for (int j = i; j < n; j++) printf("%d -> ", local[j]);
        for (int j = i - 1; j >= 0; j--) printf("%d -> ", local[j]);
        total = local[n - 1] - head + local[n - 1] - local[0];
    } else {
        for (int j = i; j >= 0; j--) printf("%d -> ", local[j]);
        for (int j = i + 1; j < n; j++) printf("%d -> ", local[j]);
        total = head - local[0] + local[n - 1] - local[0];
    }

    printf("\b\b  \nTotal Seek Time: %d\n", total);
}

void clook(int req[], int n, int head, int dir) {
    int local[MAX];
    for (int i = 0; i < n; i++) local[i] = req[i];
    local[n++] = head;

    qsort(local, n, sizeof(int), compare);
    int i;
    for (i = 0; i < n; i++) if (local[i] == head) break;

    printf("C-LOOK Order: ");

    int total;
    if (dir == 1) {
        for (int j = i; j < n; j++) printf("%d -> ", local[j]);
        for (int j = 0; j < i; j++) printf("%d -> ", local[j]);
        total = local[n - 1] - head + local[n - 1] - local[0];
    } else {
        for (int j = i; j >= 0; j--) printf("%d -> ", local[j]);
        for (int j = n - 1; j > i; j--) printf("%d -> ", local[j]);
        total = head - local[0] + local[n - 1] - local[0];
    }

    printf("\b\b  \nTotal Seek Time: %d\n", total);
}

int main() {
    int req[MAX], n, head, choice, dir;
    const int size = 200;

    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);

    do {
        printf("\nDisk Scheduling Algorithms\n");
        printf("1. FCFS\n2. SSTF\n3. SCAN\n4. C-SCAN\n5. LOOK\n6. C-LOOK\n0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice >= 3 && choice <= 6) {
            printf("Enter direction (0 = left, 1 = right): ");
            scanf("%d", &dir);
        }

        switch (choice) {
            case 1: fcfs(req, n, head); break;
            case 2: sstf(req, n, head); break;
            case 3: scan(req, n, head, size, dir); break;
            case 4: cscan(req, n, head, size, dir); break;
            case 5: look(req, n, head, dir); break;
            case 6: clook(req, n, head, dir); break;
        }

    } while (choice != 0);

    return 0;
}
