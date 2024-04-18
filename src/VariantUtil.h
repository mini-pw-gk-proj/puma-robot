//
// Created by faliszewskii on 18.04.24.
//

#ifndef PUMAROBOT_VARIANTUTIL_H
#define PUMAROBOT_VARIANTUTIL_H

template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

#endif //PUMAROBOT_VARIANTUTIL_H
