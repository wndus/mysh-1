#include "signal_handlers.h"
#include<signal.h>

void catch_sigint(int sig)
{

signal(sig,SIG_IGN);

signal(SIGINT,catch_sigint);

}
void catch_sigtstp(int sig)
{
 signal(sig,SIG_IGN);

signal(SIGTSTP,catch_sigtstp);


}
