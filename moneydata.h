#ifndef MONEYDATA_H
#define MONEYDATA_H


class MoneyData
{
public:
    inline int getPay(){return pay;}
    inline void setPay(int pay){this->pay = pay;}
    static MoneyData* getInstace();
private:
    MoneyData();
    MoneyData(const MoneyData& other);
    ~MoneyData();
    static MoneyData* instance;
private:
    int pay;
};

#endif // MONEYDATA_H
