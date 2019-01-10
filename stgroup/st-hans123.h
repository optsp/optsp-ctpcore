#ifndef OPTSP_CTPCORE_ST_HANS123_H_
#define OPTSP_CTPCORE_ST_HANS123_H_

#include "stbase.hpp"

class StHans123 : public StBase {
public:
    ///获取策略的交易上下文
    virtual StContext * GetStContext() {}
    ///设置交易接口，直接调用接口的函数，即可实现下单/撤单等操作
    virtual void SetTradeApi() {}
    ///用于程序初始化时，向策略提供历史的Tick数据
    virtual void InitTick() {}
    ///向策略提供实时的Tick数据
    virtual void PushTick() {}
};

#endif // !OPTSP_CTPCORE_ST_HANS123_H_
