#ifndef OPTSP_CTPCORE_ST_HANS123_H_
#define OPTSP_CTPCORE_ST_HANS123_H_

/* Base Header */
#include "../include/stbase.hpp"


#include <boost/lockfree/queue.hpp>


typedef struct TickField {
    uint64_t    TimeStamp;              ///时间戳, "yyyy-MM-dd hh:mm:ss.zzz"
    double      Price;                  ///时间切片的最新价格
    uint64_t    Volume;                 ///成交量
    double      Turnover;               ///成交额
    uint64_t    Position;               ///持仓量
    double      Average;                ///当日均价
    double      BidPrice;               ///申买价1
    uint64_t    BidVolume;              ///申买量1
    double      AskPrice;               ///申卖价1
    uint64_t    AskVolume;              ///申卖量1
    char        InstrumentID[32];       ///合约编码，p.s. 字节未对齐
} TickField;


class StHans123 : public StBase {
private:
    boost::lockfree::queue<TickField> *tickQueue = nullptr;

public:
    StHans123();

public:
    ///获取策略的交易上下文
    virtual StContext * GetStContext();
    ///设置交易接口，直接调用接口的函数，即可实现下单/撤单等操作
    virtual void SetTradeApi();
    ///用于程序初始化时，向策略提供历史的Tick数据
    virtual void InitTick();
    ///向策略提供实时的Tick数据
    virtual void PushTick();
};

#endif // !OPTSP_CTPCORE_ST_HANS123_H_

