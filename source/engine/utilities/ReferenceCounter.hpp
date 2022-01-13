#ifndef REFERENCECOUNTER_H
#define REFERENCECOUNTER_H

class ReferenceCounter
{
public:
    ReferenceCounter() :
        m_refCount(1) {}

    [[nodiscard]] inline int getReferenceCount() const { return m_refCount; }

    inline void addReference() { m_refCount++; }
    inline bool removeReference() { m_refCount--; return m_refCount == 0; }
protected:
private:
    int m_refCount;
};

#endif // REFERENCECOUNTER_H
