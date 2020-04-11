#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int policy_arg = atoi(argv[1]);
  int ret = policy(policy_arg);
  printf(1,"%d",ret);
  if (ret==0){
    printf(1, "Policy has been successfuly changed to %s Policy\n", policy_arg == 0 ? "Default" :
                                                                    policy_arg == 1 ? "Priority" :
                                                                    "CFS");
  }
  else
  {
    printf(1, "Error replacing policy, no such a policy number (%d)\n",policy_arg);
  }
  exit(0);
}