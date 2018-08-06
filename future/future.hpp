#include <eosiolib/eosio.hpp>
#include <eosiolib/multi_index.hpp>
#include <eosiolib/fixedpoint.hpp>
#include <string.h>

using namespace eosio;
using namespace std;

//@abi table description i64
struct description {
    uint128_t id;
    uint16_t multiple;
    uint64_t decimal_place;
    uint64_t price_tick;

    auto primary_key() const { return id; }

    EOSLIB_SERIALIZE(description, (id)(multiple)(decimal_place)(price_tick))
};

typedef multi_index<N(description), description> contract_description;