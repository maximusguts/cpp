#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

#define MAX_SHAPES 10
#define MAX_LINE 100

// ============== Abstract base class ==============

class Shape {
public:
    virtual void Show() const = 0;
    virtual void Save(FILE* f) const = 0;
    virtual void Load(FILE* f) = 0;
    virtual ~Shape() {}
};

// ===================== Square =====================

class Square : public Shape {
private:
    int x, y, side;
public:
    Square(int x_=0, int y_=0, int s_=0) : x(x_), y(y_), side(s_) {}

    void Show() const override {
        printf("Square: top-left(%d,%d), side=%d\n", x, y, side);
    }

    void Save(FILE* f) const override {
        fprintf(f, "Square %d %d %d\n", x, y, side);
    }

    void Load(FILE* f) override {
        fscanf(f, "%d %d %d", &x, &y, &side);
    }
};

// ==================== Rectangle ====================

class Rectangle : public Shape {
private:
    int x, y, width, height;
public:
    Rectangle(int x_=0, int y_=0, int w_=0, int h_=0) : x(x_), y(y_), width(w_), height(h_) {}

    void Show() const override {
        printf("Rectangle: top-left(%d,%d), width=%d, height=%d\n", x, y, width, height);
    }

    void Save(FILE* f) const override {
        fprintf(f, "Rectangle %d %d %d %d\n", x, y, width, height);
    }

    void Load(FILE* f) override {
        fscanf(f, "%d %d %d %d", &x, &y, &width, &height);
    }
};

// ==================== Circle ====================

class Circle : public Shape {
private:
    int cx, cy, r;
public:
    Circle(int cx_=0, int cy_=0, int r_=0) : cx(cx_), cy(cy_), r(r_) {}

    void Show() const override {
        printf("Circle: center(%d,%d), radius=%d\n", cx, cy, r);
    }

    void Save(FILE* f) const override {
        fprintf(f, "Circle %d %d %d\n", cx, cy, r);
    }

    void Load(FILE* f) override {
        fscanf(f, "%d %d %d", &cx, &cy, &r);
    }
};

// ==================== Ellipse ====================
class Ellipse : public Shape {
private:
    int x, y, width, height;
public:
    Ellipse(int x_=0, int y_=0, int w_=0, int h_=0) : x(x_), y(y_), width(w_), height(h_) {}

    void Show() const override {
        printf("Ellipse: top-left(%d,%d), width=%d, height=%d\n", x, y, width, height);
    }

    void Save(FILE* f) const override {
        fprintf(f, "Ellipse %d %d %d %d\n", x, y, width, height);
    }

    void Load(FILE* f) override {
        fscanf(f, "%d %d %d %d", &x, &y, &width, &height);
    }
};

// ==================== Main Function ====================
int main() {
    Shape* shapes[MAX_SHAPES];
    int count = 0;

    // створюємо масив фігур
    shapes[count++] = new Square(0, 0, 10);
    shapes[count++] = new Rectangle(5, 5, 20, 10);
    shapes[count++] = new Circle(15, 15, 7);
    shapes[count++] = new Ellipse(2, 3, 12, 8);

    // =================== Saving to file ===================
    FILE* fout = fopen("shapes.txt", "w");
    if (fout) {
        for (int i = 0; i < count; i++) {
            shapes[i]->Save(fout);
        }
        fclose(fout);
    }

    // ================== Loading from file ==================
    FILE* f = fopen("shapes.txt", "r");
    Shape* loaded_shapes[MAX_SHAPES];
    int loaded_count = 0;
    char type[MAX_LINE];

    if (f) {
        while (fscanf(f, "%s", type) != EOF) {
            Shape* s = nullptr;
            if (strcmp(type, "Square") == 0) s = new Square();
            else if (strcmp(type, "Rectangle") == 0) s = new Rectangle();
            else if (strcmp(type, "Circle") == 0) s = new Circle();
            else if (strcmp(type, "Ellipse") == 0) s = new Ellipse();
            else continue;

            s->Load(f);
            loaded_shapes[loaded_count++] = s;
        }
        fclose(f);
    }

    // ==================== Printing loaded shapes ====================
    printf("Loaded Shapes:\n");
    for (int i = 0; i < loaded_count; i++) {
        loaded_shapes[i]->Show();
    }

    // ==================== Freeing memory ====================
    for (int i = 0; i < count; i++) delete shapes[i];
    for (int i = 0; i < loaded_count; i++) delete loaded_shapes[i];

    return 0;
}
