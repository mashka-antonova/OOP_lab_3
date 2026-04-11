#include "memory.h"

Memory::Memory()
    : storedValue(0.0) {}

void Memory::add(double value) {
    storedValue += value;
}

void Memory::subtract(double value) {
    storedValue -= value;
}

void Memory::clear() {
    storedValue = 0.0;
}

double Memory::get() const {
    return storedValue;
}
