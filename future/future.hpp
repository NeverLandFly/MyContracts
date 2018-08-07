#include <eosiolib/eosio.hpp>
#include <eosiolib/multi_index.hpp>
#include <string.h>

using namespace eosio;
using namespace std;

//@abi table description i64
struct description {
    account_name contract_account;
    uint16_t multiple;
    uint32_t precision;
    uint32_t counter = 0;

    auto primary_key() const { return contract_account; }
    EOSLIB_SERIALIZE(description, (contract_account)(multiple)(precision)(counter))
};

typedef multi_index<N(description), description> contract_description;

//@abi table orders i64
struct order{
    uint64_t id;
    uint8_t type;
    uint32_t price;
    account_name owner;

    auto primary_key() const { return id; }
    EOSLIB_SERIALIZE(order, (id)(type)(price)(owner))
};
typedef multi_index<N(order), order> orders;