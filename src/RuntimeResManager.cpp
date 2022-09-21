//
// Created by 克莉斯丁 on 2022/9/21.
//

#include "RuntimeResManager.h"

RuntimeResManager *RuntimeResManager::instance= nullptr;
RuntimeResManager::RuntimeResManager() {
    instance=this;
}