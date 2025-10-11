#include <stdio.h>

typedef struct Point {
    int x, y;
} Point;

// Orientation function
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// Jarvis March (Gift Wrapping) Algorithm
void convexHull(Point points[], int n) {
    if (n < 3) return;

    int hull[n];
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;

    int p = l, q;
    int idx = 0;

    do {
        hull[idx++] = p;
        q = (p + 1) % n;

        for (int i = 0; i < n; i++) {
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        }

        p = q;
    } while (p != l);

    printf("Points in Convex Hull are:\n");
    for (int i = 0; i < idx; i++)
        printf("(%d, %d)\n", points[hull[i]].x, points[hull[i]].y);
}

int main() {
    int n;
    printf("Enter number of points: ");
    scanf("%d", &n);

    Point points[n];
    printf("Enter coordinates (x y):\n");
    for (int i = 0; i < n; i++)
        scanf("%d%d", &points[i].x, &points[i].y);

    convexHull(points, n);
    return 0;
}
