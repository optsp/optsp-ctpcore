#ifndef OPTSP_CTPCORE_STBASE_HPP_
#define OPTSP_CTPCORE_STBASE_HPP_

#include <atomic>
#include <mutex>


typedef struct CbQuoteRtnDepthMarketDataField {
    char                TradingDay[9];          ///交易日
    char                InstrumentID[31];       ///合约编码，p.s. 字节未对齐} HandicapField;
    char                ExchangeID[9];          ///交易所代码
    char                ExchangeInstID[31];     ///合约在交易所的代码
    double              PreClosePrice;          ///昨收盘
    double              PreSettlementPrice;     ///昨结算
    uint64_t            PreOpenInterest;        ///昨持仓
    double              OpenPrice;              ///今开盘
    double              HighestPrice;           ///最高价
    double              LowestPrice;            ///最低价
    double              ClosePrice;             ///今收盘
    double              SettlementPrice;        ///今结算
    double              UpperLimitPrice;        ///涨停板
    double              LowerLimitPrice;        ///跌停板
    double              PreDelta;               ///昨虚实度
    double              CurrDelta;              ///今虚实度
    double              BidPrice[5];            ///申买价1-5
    uint64_t            BidVolume[5];           ///申买量1-5
    double              AskPrice[5];            ///申卖价1-5
    uint64_t            AskVolume[5];           ///申卖量1-5
    uint64_t            TimeStamp;              ///时间戳, "yyyy-MM-dd hh:mm:ss.zzz"
    double              LastPrice;              ///时间切片的最新价格
    uint64_t            Volume;                 ///成交量
    double              Turnover;               ///成交额
    uint64_t            OpenInterest;           ///持仓量
    double              AveragePrice;           ///当日均价
} CbQuoteRtnDepthMarketDataField;


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
