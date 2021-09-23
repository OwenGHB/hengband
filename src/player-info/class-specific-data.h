#pragma once

#include <memory>
#include <variant>

struct no_class_specific_data {
};
struct smith_data_type;
struct spell_hex_data_type;

using ClassSpecificData = std::variant<

    no_class_specific_data,
    std::shared_ptr<smith_data_type>,
    std::shared_ptr<spell_hex_data_type>

    >;
