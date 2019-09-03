
// 正确 
int A(int x, double dx) {
      return (float)x == (float)dx;
}

// 错误，当 y == INT_MIN
int B(int x, double dx, int y, double dy) {
      return dx-dy == (double)(x-y);
}

// 正确 
int C(double dx, double dy, double dz) {
      return (dx+dy)+dz == dx+(dy+dz);
}

// 错误,可能被舍入
int D(double dx, double dy, double dz) {
      return (dx*dy)*dz == dx*(dy*dz);
}

//  错误， 当 dx != 0 and dz == 0
int E(double dx, double dz) {
      return dx/dx == dz/dz;
}

