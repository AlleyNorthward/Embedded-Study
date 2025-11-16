#include "IQR_manager.hpp"
#include "setup.hpp"

void IQRManager::exti0_handler(){
    StaticBuilder::key[3]->exti_on(KEY::check_single_key);
}
