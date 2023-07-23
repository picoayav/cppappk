#pragma once
#include <iostream>
#include <unordered_map>

enum class Blocks {
    DIRT,
    GRASS,
    VOIDBLOCK,
    WOOD,
};


inline Blocks stringToBlocks(const std::string& str) {
    static const std::unordered_map<std::string, Blocks> blockMap = {
            {"dirt", Blocks::DIRT},
            {"grass", Blocks::GRASS},
            {"VOID", Blocks::VOIDBLOCK},
            {"wood", Blocks::WOOD}
    };

    auto it = blockMap.find(str);
    if (it != blockMap.end()) {
        return it->second;
    }

    return Blocks::GRASS;
}

