#include "../include/stgroup.h"
#include <chrono>

#include "st-server.h"
#include "st-hans123.h"
#include "st-dual-thrust.h"


StGroup::StGroup(Config *config, Logger *logger, quote_callback_fn qfn, trade_callback_fn tfn, stgroup_callback_fn sfn)
    : config(config), logger(logger), quote_callback(qfn), trade_callback(tfn), stgroup_callback(sfn)
{
    stcbfn = this;
    std::stringstream log;

    plat = new PlatCtp(config, logger, PlatCallBack);

    stContainer = new std::vector<StBase*>();
    cbQuoteQueue = new boost::lockfree::queue<CbQuoteField>(1024);
    cbTradeQueue = new boost::lockfree::queue<CbTradeField>(1024);


    StBase *st0 = new StServer();           ///用于通过socket与其他平台实现的策略进行交互
    StBase *st1 = new StHans123();          ///demo1
    StBase *st2 = new StDualThrust();       ///demo2
    stContainer->push_back(st0);
    stContainer->push_back(st1);
    stContainer->push_back(st2);

}


void StGroup::SubmitSpi(int cbtype, void* ptr)
{
    if (cbtype > CB_QUOTE_TYPE_BEGIN && cbtype < CB_QUOTE_TYPE_END) {
        cbQuoteQueue->push(*((CbQuoteField*) ptr));
        condi_var_cb_buf.notify_all();
        (*quote_callback)(cbtype, ptr);
    }
    else if (cbtype > CB_TRADE_TYPE_BEGIN && cbtype < CB_TRADE_TYPE_END) {
        cbTradeQueue->push(*((CbTradeField*) ptr));
        condi_var_cb_buf.notify_all();
        (*trade_callback)(cbtype, ptr);
    }
    else if (cbtype > CMD_PLAT_QUOTE_TYPE_BEGIN && cbtype < CMD_PLAT_QUOTE_TYPE_END) {

    }
    else if (cbtype > CMD_PLAT_TRADE_TYPE_BEGIN && cbtype < CMD_PLAT_TRADE_TYPE_END) {

    }
    else {

    }
}


void StGroup::DispatchSpi()
{
    CbQuoteField cbQuote;
    CbTradeField cbTrade;
    /* 优先调度行情回调；在行情回调队列为空时再调度一个交易回调 */
    /* 两个队列都为空时，阻塞等待唤醒或等待一毫秒的timeout */
    while (true) {
        condi_var_cb_buf.wait_for(lock_cb_buf, std::chrono::milliseconds(1));
        while (!cbQuoteQueue->empty()) {
            do {
                //TODO: 将quoteQueue清空
                cbQuoteQueue->pop(cbQuote);


            } while (!cbQuoteQueue->empty());

            do {
                //TODO: 在quoteQueue为空时对tradeQueue进行一次调度
                cbTradeQueue->pop(cbTrade);


            } while (cbQuoteQueue->empty());
        }
    }
}


void PlatCallBack(int cbtype, void* ptr) {
    StGroup *stgroup = (StGroup*)stcbfn;
    stgroup->SubmitSpi(cbtype, ptr);
}