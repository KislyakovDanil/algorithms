#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double epsilon = 1e-5;

struct Vector2D {
    double x;
    double y;
    Vector2D (double first, double second): x(first), y(second) {}
    friend Vector2D operator+ (const Vector2D& v1, const Vector2D& v2);
    friend Vector2D operator- (const Vector2D& v1, const Vector2D& v2);
};

Vector2D operator+ (const Vector2D& first, const Vector2D& second) {
    return Vector2D(first.x + second.x, first.y + second.y);
}

Vector2D operator- (const Vector2D& first, const Vector2D& second) {
    return Vector2D(first.x - second.x, first.y - second.y);
}

bool angle_min_cmp(const Vector2D &first, const Vector2D &second) {
    double norm_first_x = first.x / sqrt(first.x * first.x + first.y * first.y); // значение x у первого, если бы длина вектора была = 1
    double norm_second_x = second.x / sqrt(second.x * second.x + second.y * second.y); // значение x у второго, если бы длина вектора была = 1
    return norm_first_x - norm_second_x > epsilon; // в связи с особенностями вида, в котором храним фигуры
}

vector<Vector2D> Minkowsky (const vector<Vector2D>& polygon_1, const vector<Vector2D>& polygon_2) { // сумма Минковского
    vector<Vector2D> result;
    int i = 0, j = 0;
    while (i < polygon_1.size() || j < polygon_2.size()) {
        result.push_back(polygon_1[i] + polygon_2[j]);
        if (angle_min_cmp(polygon_1[(i + 1) % polygon_1.size()] - polygon_1[i],
                          polygon_2[(j + 1) % polygon_2.size()] - polygon_2[j])) {
            ++i;
        } else if (angle_min_cmp(polygon_2[(j + 1) % polygon_2.size()] - polygon_2[j],
                                 polygon_1[(i + 1) % polygon_1.size()] - polygon_1[i])) {
            ++j;
        } else {
            ++i;
            ++j;
        }
    }
    return result;
}

bool cross_zero(const vector<Vector2D>& polygon) {
    vector<double> zero_x;
    for (int i = 0; i < polygon.size(); ++i) {
        if (polygon[i].y * polygon[(i + 1) % polygon.size()].y < 0) {
            zero_x.push_back((polygon[i].x + polygon[(i + 1) % polygon.size()].x) / 2);
        }
        if (abs(polygon[i].y) < epsilon) {
            zero_x.push_back(polygon[i].x);
        }
    }
    if (zero_x.empty()) {
        return false;
    }
    double min = INFINITY;
    double max = -INFINITY;
    for (double x: zero_x) {
        if (x < min) {
            min = x;
        }
        if (x > max) {
            max = x;
        }
    }
    return abs(max) < epsilon || abs(min) < epsilon || max * min < 0;
}

vector<Vector2D> normal(const vector<Vector2D>& polygon) {
    vector<Vector2D> normal_polygon;
    int min = 0; // первым элементом является самая левая нижняя точка множества
    for (int i = 1; i < polygon.size(); ++i) {
        if (polygon[i].x < polygon[min].x || polygon[min].x - polygon[i].x < epsilon && polygon[i].y < polygon[min].y) {
            min = i;
        }
    }
    for (int i = polygon.size() - 1; i >= 0; --i) { // сортируем в порядке обхода ПРОТИВ часовой стрелки
        normal_polygon.push_back(polygon[(i + min + 1) % polygon.size()]);
    }
    return normal_polygon;
}

void read (vector<Vector2D>& polygon_1, vector<Vector2D>& polygon_2) { // читаем два многоугольника
    int polygon_size;
    double x, y;
    cin >> polygon_size;
    for (int i = 0; i < polygon_size; ++i) {
        cin >> x >> y;
        polygon_1.push_back(Vector2D(x, y));
    }
    polygon_1 = normal(polygon_1);
    cin >> polygon_size;
    for (int i = 0; i < polygon_size; ++i) {
        cin >> x >> y;
        polygon_2.push_back(Vector2D(-1 * x, -1 * y));
    }
    polygon_2 = normal(polygon_2);
}

int main() {
    vector<Vector2D> polygon_1;
    vector<Vector2D> polygon_2;
    read(polygon_1, polygon_2);
    if (cross_zero(Minkowsky(polygon_1, polygon_2))) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}