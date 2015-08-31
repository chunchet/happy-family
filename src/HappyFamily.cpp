#include "IHusband.h"
#include "IStore.h"
#include "IMilkCarton.h"
#include "IEgg.h"
#include "Wife.h"
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>

using namespace std;

class Husband : public IHusband
{
public:
    virtual vector<shared_ptr<IEgg>> BuyEggs(shared_ptr<IStore> store, int pieces)
    {
        vector<shared_ptr<IEgg>> eggs;
        store->ProceedPurchaseEggs(eggs, pieces);
        return eggs;
    }
    virtual vector<shared_ptr<IMilkCarton>> BuyMilk(shared_ptr<IStore> store, int cartons)
    {
        vector<shared_ptr<IMilkCarton>> milkCartons;
        store->ProceedPurchaseMilk(milkCartons, cartons);
        return milkCartons;
    }
};

class Egg : public IEgg
{
    virtual std::string ToString() const
    {
        return "Egg";
    }
};

class MilkCarton : public IMilkCarton
{
    virtual std::string ToString() const
    {
        return "Milk Carton";
    }
};

class Store : public IStore
{
public:
    virtual bool HasMilk() const
    {
        return true;
    }
    virtual bool HasEggs() const
    {
        return true;
    }
    virtual bool ProceedPurchaseEggs(vector<shared_ptr<IEgg>>& eggs, int quantity)
    {
        for (int i = 0; i < quantity; ++i)
        {
            shared_ptr<IEgg> egg(new Egg());
            eggs.push_back(egg);
        }
        if (eggs.size() > 0)
            cout << boost::format("%1% of %2% purchased.") % boost::lexical_cast<string>(eggs.size()) % eggs[0]->ToString();
        return eggs.size() == (size_t)quantity;
    }
    virtual bool ProceedPurchaseMilk(vector<shared_ptr<IMilkCarton>>& milkCartons, int quantity)
    {
        for (int i = 0; i < quantity; ++i)
        {
            shared_ptr<IMilkCarton> milkCarton(new MilkCarton());
            milkCartons.push_back(milkCarton);
        }
        if (milkCartons.size() > 0)
            cout << boost::format("%1% of %2% purchased.") % boost::lexical_cast<string>(milkCartons.size()) % milkCartons[0]->ToString();
        return milkCartons.size() == (size_t)quantity;
    }
};

int main()
{
    Wife wife;
    shared_ptr<IHusband> husband(new Husband());
    shared_ptr<IStore> store(new Store());
    vector<shared_ptr<IMilkCarton>> milkCartons;
    vector<shared_ptr<IEgg>> eggs;
    return wife.RequestPurchase(husband, store, milkCartons, eggs);
}
