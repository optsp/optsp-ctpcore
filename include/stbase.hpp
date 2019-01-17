#ifndef OPTSP_CTPCORE_STBASE_HPP_
#define OPTSP_CTPCORE_STBASE_HPP_

#include <atomic>
#include <mutex>

typedef struct StContext {
    char    InstrumentID[32];       ///合约编号
    double  LastPrice;              ///最新价
    double  OpenPrice;              ///开仓价
    double  StopLoss;               ///止损价
    double  TargetProfit;           ///止盈价

    int     PositionVolume;         ///持仓量
    char    Direction;              ///价格变动方向
    char    PositionState;          ///持仓状态
} StContext;


typedef struct StParameter {
    char    Label[128];             ///参数说明
    double  Parameter;              ///参数值
    double  Lower;                  ///参数值的下限
    double  Upper;                  ///参数值的上限
};


class StBase {
public:
    ///获取策略的交易上下文
    virtual StContext* GetStContext() = 0;
    ///获取策略的参数定义
    virtual StParameter* GetStParameter() = 0;
    ///设置交易接口，直接调用接口的函数，即可实现下单/撤单等操作
    virtual void SetTradeApi() = 0;
    ///用于程序初始化时，向策略提供历史的Tick数据
    virtual void InitTick() = 0;
    ///向策略提供实时的Tick数据
    virtual void PushTick() = 0;

    
    

};


#endif // !OPTSP_CTPCORE_STBASE_HPP_
