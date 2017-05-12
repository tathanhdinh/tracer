#include <stdio.h>
#include <stddef.h>

#include "dr_api.h"
#include "drmgr.h"
#include "drreg.h"
#include "drutil.h"
//#include "utils.h"

void event_thread_init(void *drcontext);

DR_EXPORT void
dr_client_main(client_id_t id, int argc, const char *argv[]) {
    drreg_options_t reg_ops = { sizeof (reg_ops), 3, false };
    if (drreg_init(&ops) != DRREG_SUCCESS) {
        DR_ASSERT(false);
        return;
    }

    if (!drmgr_register_thread_init_event(event_thread_init)) {
        DR_ASSERT(false);
        return;
    }

}


static void
event_thread_init(void *drcontext) {

}
