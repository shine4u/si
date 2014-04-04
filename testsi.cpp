#include "SI.h"

int main(int argc, char **argv)  {
    SI_NOTICE("this is a notice.");
    
    si::TimeDate td1, td2;
    td1.set_now();
    sleep(1);
    td2.set_now();
    SI_NOTICE("%d", td2.diff_secs(td1));

    return 0;
}
