#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/time.hpp>
#include <string>

using namespace eosio;

class try_time : public eosio::contract{
    public:
        try_time(account_name self): eosio::contract(self){}

        ///@abi action
        void show(const std::string& time_str)
        {
            const time_point& current_time = time_point::from_iso_string(time_str);
            print(current_time.elapsed._count);
        }
};
EOSIO_ABI(try_time, (show))
