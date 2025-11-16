#include "IQR_manager.hpp"
#include "setup.hpp"

void IQRManager::tim4_handler(){
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    SetUp::count_++;
    if(SetUp::count_ >= SetUp::delay_times){
        SetUp::count_ = 0;
        *StaticBuilder::led[0]->get_singleled().SET_LED = !(*StaticBuilder::led[0]->get_singleled().SET_LED);
    }
}
