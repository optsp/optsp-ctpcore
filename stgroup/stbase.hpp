#ifndef OPTSP_CTPCORE_STBASE_HPP_
#define OPTSP_CTPCORE_STBASE_HPP_

#include <atomic>
#include <mutex>

typedef char InstrumentIDType[31];

typedef struct StContext {
    InstrumentIDType        InstrumentID;

    double                  LastPrice;
    double                  OpenPrice;
    double                  StopLoss;
    double                  TargetProfit;

    int                     PositionVolume;
    char                    Direction;
    char                    PositionState;
    bool                    IsLast;
} StContext;


class StBase {
public:
    ///获取策略的交易上下文
    virtual StContext * GetStContext() = 0;
    ///设置交易接口，直接调用接口的函数，即可实现下单/撤单等操作
    virtual void SetTradeApi() = 0;
    ///用于程序初始化时，向策略提供历史的Tick数据
    virtual void InitTick() = 0;
    ///向策略提供实时的Tick数据
    virtual void PushTick() = 0;
    

};


#endif // !OPTSP_CTPCORE_STBASE_HPP_
