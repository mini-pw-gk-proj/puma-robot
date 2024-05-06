//
// Created by faliszewskii on 06.05.24.
//

#ifndef PUMAROBOT_TEXTURE_H
#define PUMAROBOT_TEXTURE_H


#include <string>

class Texture {
    unsigned int id{};

public:
    explicit Texture(const std::string& path);

    void bind(int slot) const;
};


#endif //PUMAROBOT_TEXTURE_H
