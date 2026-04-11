#ifndef MEMORY_H
#define MEMORY_H

class Memory final
{
public:
    Memory();

    void add(double value);
    void subtract(double value);
    void clear();
    double get() const;

private:
    double storedValue;
};

#endif // MEMORY_H

