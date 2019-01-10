#include "../include/stgroup.h"
#include "st-hans123.h"
#include "st-dual-thrust.h"


StGroup::StGroup(Config *config, Logger *logger, quote_callback_fn qfn, trade_callback_fn tfn, stgroup_callback_fn sfn)
    : config(config), logger(logger), quote_callback(qfn), trade_callback(tfn), stgroup_callback(sfn)
{
    cbfn = this;
    std::stringstream log;

    plat = new PlatCtp(config, logger, PlatCallBack);
    stContainer = new std::vector<StBase*>();

    StBase *st1 = new StHans123();
    StDualThrust *st2 = new StDualThrust();
    stContainer->push_back(st1);
    stContainer->push_back(st2);

    for (auto st : *stContainer) {
        st->GetStContext();
    }
}


void StGroup::DispatchSpi(int cbtype, void* ptr)
{
    if (cbtype > CB_QUOTE_TYPE_BEGIN && cbtype < CB_QUOTE_TYPE_END) {
        (*quote_callback)(cbtype, ptr);
    }
    else if (cbtype > CB_TRADE_TYPE_BEGIN && cbtype < CB_TRADE_TYPE_END) {
        (*trade_callback)(cbtype, ptr);
    }
    else if (cbtype > CMD_PLAT_QUOTE_TYPE_BEGIN && cbtype < CMD_PLAT_QUOTE_TYPE_END) {

    }
    else if (cbtype > CMD_PLAT_TRADE_TYPE_BEGIN && cbtype < CMD_PLAT_TRADE_TYPE_END) {

    }
    else {

    }
}


void PlatCallBack(int cbtype, void* ptr) {
    StGroup *stgroup = (StGroup*)cbfn;
    stgroup->DispatchSpi(cbtype, ptr);
}