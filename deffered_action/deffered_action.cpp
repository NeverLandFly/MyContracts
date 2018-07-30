#include <vector>
#include <string>
#include <eosiolib/eosio.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/time.hpp>

using namespace eosio;
using namespace std;

class deffered_action : public eosio::contract{
    public:
        deffered_action(account_name self): eosio::contract(self){}

        ///@abi action
        void counter(uint32_t count){
            print("Current count:", count);
            count++;
            if(count > 10)
                return;
            transaction out{};
            out.actions.emplace_back(permission_level{_self, N(active)}, _self, N(counter), 
                make_tuple(count));
            out.delay_sec = 2;
            out.send(count, _self);
        }
};

EOSIO_ABI(deffered_action, (counter))

