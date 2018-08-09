#include <eosiolib/eosio.hpp>
#include <eosiolib/multi_index.hpp>


using namespace eosio;
using namespace std;

//@abi table description i64
struct description {
    account_name contract_account;
    uint32_t multiple;
    uint32_t precision;
    uint32_t counter = 0;
    uint32_t rcounter = (2<<29) - 1;
    string underlying;
    uint64_t expiration;
    uint64_t ask1key = 0;
    uint64_t bid1key = 0;
    uint32_t lastprice = 0;

    auto primary_key() const { return contract_account; }
    EOSLIB_SERIALIZE(description, (contract_account)(multiple)(precision)(counter)(rcounter)(underlying)(expiration)(ask1key)(bid1key)(lastprice))
};

typedef multi_index<N(description), description> contract_description;

//@abi table order i64
struct order{
    uint64_t id;
    uint64_t rid;
    uint32_t price;
    uint32_t volume;
    uint32_t closedvolume;
    uint8_t type;
    account_name owner;

    auto primary_key() const { return id; }
    auto get_unclosed() const {return volume - closedvolume;}
    auto by_rid() const {return rid;}
    EOSLIB_SERIALIZE(order, (id)(rid)(price)(volume)(closedvolume)(type)(owner))
};
typedef multi_index<N(order), order,
    indexed_by<N(rid), const_mem_fun<order, uint64_t , &order::by_rid>>
> orders;