#include <iostream>
#include <cmath>
using namespace std;

const double epsilon = 1e-8;

struct Vector3D {
    Vector3D(double first, double second, double third): x(first), y(second), z(third) {}
    double x;
    double y;
    double z;
    double len() { // длина
        return sqrt(x * x + y * y + z * z);
    }
};

double scalar_product(const Vector3D &v1, const Vector3D &v2) { // скалярное произведение
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3D operator+(const Vector3D &v1, const Vector3D &v2) {
    return Vector3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3D operator-(const Vector3D &v1, const Vector3D &v2) {
    return Vector3D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3D operator*(double k, const Vector3D &v) {
    return Vector3D(k * v.x, k * v.y, k * v.z);
}

void v1_coeff_correction (double& v1_coeff_numerator, double& v1_coeff_denumerator, const double potential_numerator, const double potential_denumerator) {
    if (potential_numerator <= 0) {
        v1_coeff_numerator = 0;
    } else if (abs(potential_numerator / potential_denumerator) <= 1) {
        v1_coeff_numerator = potential_numerator;
        v1_coeff_denumerator = potential_denumerator;
    } else {
        v1_coeff_numerator = v1_coeff_denumerator;
    }
}

double dist_between_segments_3D(const Vector3D &v1, const Vector3D &v2, const Vector3D &v0) {
    double scalar_1_0 = scalar_product(v1, v0);
    double scalar_1_1 = scalar_product(v1, v1);
    double scalar_1_2 = scalar_product(v1, v2);
    double scalar_2_2 = scalar_product(v2, v2);
    double scalar_0_2 = scalar_product(v0, v2);
    double v1_coeff, v2_coeff; // coeff -- коэффициенты на длины векторов
    double v1_coeff_numerator = scalar_1_2 * scalar_0_2 - scalar_2_2 * scalar_1_0; // числители и знаменатели для вычисления coeff-ов
    double v2_coeff_numerator = scalar_1_1 * scalar_0_2 - scalar_1_2 * scalar_1_0;
    double v1_coeff_denumerator = scalar_1_1 * scalar_2_2 - scalar_1_2 * scalar_1_2;
    double v2_coeff_denumerator = scalar_1_1 * scalar_2_2 - scalar_1_2 * scalar_1_2;
    if (scalar_1_1 * scalar_2_2 - scalar_1_2 * scalar_1_2 == 0 || v1_coeff_numerator <= 0) { // отрезки параллельны или ближайший край -- v1_coeff = 0
        v1_coeff_numerator = 0;
        v2_coeff_numerator = scalar_0_2;
        v2_coeff_denumerator = scalar_2_2;
    } else if (v1_coeff_numerator >= v1_coeff_denumerator) { // ближайший край -- v1_coeff = 1
        v1_coeff_numerator = v1_coeff_denumerator;
        v2_coeff_numerator = scalar_1_2 + scalar_0_2;
        v2_coeff_denumerator = scalar_2_2;
    }
    // дальше не можем считать так просто, т.к. мы уже, возможно, кое-что знаем о взаимном расположении отрезков
    if (v2_coeff_numerator <= 0) { // ближайший край -- v2_coeff = 0
        v2_coeff_numerator = 0;
        v1_coeff_correction(v1_coeff_numerator, v1_coeff_denumerator, -1 * scalar_1_0, scalar_1_1);
    } else if (v2_coeff_numerator >= v2_coeff_denumerator) { // ближайший край -- v2_coeff = 1
        v2_coeff_numerator = v2_coeff_denumerator;
        v1_coeff_correction(v1_coeff_numerator, v1_coeff_denumerator, scalar_1_2 - scalar_1_0, scalar_1_1);
    }
    v1_coeff = v1_coeff_numerator / v1_coeff_denumerator;
    v2_coeff = v2_coeff_numerator / v2_coeff_denumerator;
    if (abs(v1_coeff_numerator) < epsilon || abs(v1_coeff) < epsilon) {
        v1_coeff = 0;
    }
    if (abs(v2_coeff_numerator) < epsilon || abs(v2_coeff) < epsilon) {
        v2_coeff = 0;
    }
    Vector3D dist = v0 + (v1_coeff * v1) - (v2_coeff * v2);
    return dist.len();
}

int main() {
    int x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
    cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3 >> x4 >> y4 >> z4;
    Vector3D v1(x1 - x2, y1 - y2, z1 - z2);
    Vector3D v2(x3 - x4, y3 - y4, z3 - z4);
    Vector3D v0(x3 - x1, y3 - y1, z3 - z1); // вектор из певого конца первого отрезка в первый конец второго
    printf("%.8f",dist_between_segments_3D(v1, v2, v0));
    return 0;
}