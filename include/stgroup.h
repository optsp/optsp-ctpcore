#ifndef OPTSP_CTPCORE_STGROUP_H_
#define OPTSP_CTPCORE_STGROUP_H_

#include <vector>
#include "../include/platctp.h"
#include "../include/config.h"
#include "../include/logger.h"
#include "../include/datatype.hpp"


static volatile void* cbfn = nullptr;
void PlatCallBack(int cbtype, void* ptr);


class StGroup
{
private:
    Config * config = nullptr;
    Logger * logger = nullptr;
    PlatCtp * plat = nullptr;

    quote_callback_fn quote_callback = nullptr;
    trade_callback_fn trade_callback = nullptr;
    stgroup_callback_fn stgroup_callback = nullptr;

    std::vector<StBase*> *stContainer = nullptr;


public:
    StGroup(Config *config, Logger *logger, quote_callback_fn qfn, trade_callback_fn tfn, stgroup_callback_fn sfn);
    void DispatchSpi(int cbtype, void* ptr);

};

#endif // !OPTSP_CTPCORE_STGROUP_H_

