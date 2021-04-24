//
// Created by peter on 4/24/21.
//

class UPNumber {
public:
    UPNumber();
    UPNumber(int initValue);
    UPNumber(double initValue);
    UPNumber(const UPNumber& initValue);
    void destroy() const { delete this; }
private:
    ~UPNumber();
};

class NonNegativeUPNumber : public UPNumber
{
};

class Asset
{
public:
    Asset(int initValue);
    ~Asset();
private:
    UPNumber* value;
};

Asset::Asset(int initValue) : value(new UPNumber(initValue))
{
}

Asset::~Asset() {
    value->destroy();
}

int main()
{
    UPNumber n;
    UPNumber * p1 = new UPNumber();
    delete p1;
    p1->destroy();
}