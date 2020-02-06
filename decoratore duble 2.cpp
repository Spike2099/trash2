#include <iostream>

using namespace std;

class Beverage {
public:
   //������ ����������� ����������� ��������
    virtual void description() const = 0;
    //���������� ������ ,������ �� �� ��
    virtual ~Beverage() {}
};
//����������� ������� Beverage
class Espresso: public Beverage {
public:
    //�������������� ������������ �������. override ���������� ��������� ����������� ������� ��� �����
    void description() const override {
        cout<<" Fresh Espresso!\n";
    }
};

class Cappuccino: public Beverage {
public:
    //�������������� ������������ �������.
    void description() const override {
        cout<<" Fresh Capuccino!\n";
    }
};


//
class MilkBeverage: public Beverage {
    private:
        Beverage& bev_;
    public:
    //����� ����������� ����������� ,���������� ��� ����� ����������� �������� ������ .
    explicit MilkBeverage(Beverage& b): bev_(b) {}
    void description() const override
    {
        cout << "Milk + ";
        bev_.description();
    }
};

class ChocBeverage: public Beverage {
    private:
    Beverage& bev_;
    public:
    explicit ChocBeverage(Beverage& b): bev_(b) {}

    void description() const override
    {
        cout << "Chocolate + ";
        bev_.description();
    }
};

class MochaBeverage: public Beverage{
    private:
    Beverage& bev_;
    public:
    explicit MochaBeverage(Beverage& b): bev_(b){}

    void description() const override
    {
        cout<<"Mocha + ";
        bev_.description();
    }

};
//������� ������� ��� ���������.
int main() {
    Cappuccino cap;
    Espresso e;

    MilkBeverage m{e};
    ChocBeverage c{m};
    MochaBeverage d{c};

    MilkBeverage m1{cap};
    ChocBeverage c1{m1};
    MochaBeverage d1{c1};
    d.description();
    //c.description();
    c1.description();
}
