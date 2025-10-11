#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point {
    int x, y;
} Point;

// To find next to top in stack
Point nextToTop(Point stack[], int top) {
    return stack[top - 1];
}

// Swap two points
void swap(Point *p1, Point *p2) {
    Point temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// Distance squared between two points
int distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

// Orientation test: 0 = collinear, 1 = clockwise, 2 = counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// Global variable for the bottom-most point
Point p0;

// Compare function for qsort()
int compare(const void *vp1, const void *vp2) {
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;
    return (o == 2) ? -1 : 1;
}

// Graham Scan function
void convexHull(Point points[], int n) {
    // Find the bottom-most point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        if ((points[i].y < ymin) || 
           (points[i].y == ymin && points[i].x < points[min].x)) {
            ymin = points[i].y;
            min = i;
        }
    }

    swap(&points[0], &points[min]);
    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(Point), compare);

    Point stack[n];
    int top = 0;
    stack[top++] = points[0];
    stack[top++] = points[1];
    stack[top++] = points[2];

    for (int i = 3; i < n; i++) {
        while (orientation(nextToTop(stack, top), stack[top - 1], points[i]) != 2)
            top--;
        stack[top++] = points[i];
    }

    printf("Points in Convex Hull are:\n");
    for (int i = 0; i < top; i++)
        printf("(%d, %d)\n", stack[i].x, stack[i].y);
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
