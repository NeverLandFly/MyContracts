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
    string underlying;
    uint64_t expiration;
    uint64_t ask1key = 0;
    uint64_t bid1key = 0;
    uint32_t lastprice = 0;

    auto primary_key() const { return contract_account; }
    EOSLIB_SERIALIZE(description, (contract_account)(multiple)(precision)(counter)(underlying)(expiration)(ask1key)(bid1key)(lastprice))
};

typedef multi_index<N(description), description> contract_description;

//@abi table order i64
struct order{
    uint64_t id;
    uint32_t price;
    uint32_t volume;
    uint32_t closedvolume;
    uint8_t type;
    account_name owner;

    auto primary_key() const { return id; }
    auto get_unclosed() const {return volume - closedvolume;}
    EOSLIB_SERIALIZE(order, (id)(price)(volume)(closedvolume)(type)(owner))
};
typedef multi_index<N(order), order> orders;