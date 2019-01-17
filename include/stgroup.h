#ifndef OPTSP_CTPCORE_STGROUP_H_
#define OPTSP_CTPCORE_STGROUP_H_

#include <vector>
#include <mutex>
#include <boost/lockfree/queue.hpp>
#include <condition_variable>
#include "../include/platctp.h"
#include "../include/config.h"
#include "../include/logger.h"
#include "../include/datatype.hpp"
#include "../include/stbase.hpp"
#include "../include/platstruct.hpp"
#include "../include/tradestruct.hpp"
#include "../include/quotestruct.hpp"


static volatile void* stcbfn = nullptr;
void PlatCallBack(int cbtype, void* ptr);

std::mutex mutex_cb_buf;
std::unique_lock<std::mutex> lock_cb_buf(mutex_cb_buf);

class StGroup
{
private:   
    std::condition_variable condi_var_cb_buf;

private:
    Config * config = nullptr;
    Logger * logger = nullptr;
    PlatCtp * plat = nullptr;

    quote_callback_fn quote_callback = nullptr;
    trade_callback_fn trade_callback = nullptr;
    stgroup_callback_fn stgroup_callback = nullptr;

    std::vector<StBase*> *stContainer = nullptr;
    boost::lockfree::queue<CbQuoteField> *cbQuoteQueue = nullptr;
    boost::lockfree::queue<CbTradeField> *cbTradeQueue = nullptr;

public:
    StGroup(Config *config, Logger *logger, quote_callback_fn qfn, trade_callback_fn tfn, stgroup_callback_fn sfn);
    void SubmitSpi(int cbtype, void* ptr);
    void DispatchSpi(); ///new thread for dispatch packages from plat.
};

#endif // !OPTSP_CTPCORE_STGROUP_H_

