#include <eosiolib/eosio.hpp>
#include <eosiolib/multi_index.hpp>
#include <string.h>

using namespace eosio;
using namespace std;

//@abi table description i64
struct description {
    uint64_t id;
    uint8_t multiple;

    auto primary_key() const { return id; }
    auto get_multiple() const {return multiple;}

    EOSLIB_SERIALIZE(description, (id)(multiple))
};

typedef multi_index<N(description), description> contract_description;