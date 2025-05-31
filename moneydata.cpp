#include "moneydata.h"

MoneyData* MoneyData::instance = 0;

MoneyData *MoneyData::getInstace()
{
    if(instance == 0)
    {
        instance = new MoneyData;
    }
    return instance;
}

MoneyData::MoneyData()
{

}

MoneyData::MoneyData(const MoneyData &other)
{

}

MoneyData::~MoneyData()
{

}

