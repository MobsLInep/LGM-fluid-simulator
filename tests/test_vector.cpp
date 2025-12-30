#include <cassert>
#include "math/vector.h"

int main() {
    lbm::Vector2D a{3.0, 4.0};
    lbm::Vector2D b{1.0, -2.0};
    auto c = a + b;
    assert(c.x == 4.0 && c.y == 2.0);
    auto d = a - b;
    assert(d.x == 2.0 && d.y == 6.0);
    auto e = a * 2.0;
    assert(e.x == 6.0 && e.y == 8.0);
    auto f = a / 2.0;
    assert(f.x == 1.5 && f.y == 2.0);
    assert(a.dot(b) == (3.0 * 1.0 + 4.0 * -2.0));
    assert(a.magnitude() == 5.0);
    auto n = a.normalize();
    assert(std::abs(n.x - 0.6) < 1e-12);
    assert(std::abs(n.y - 0.8) < 1e-12);
    return 0;
}

