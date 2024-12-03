#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
#include "fcntl.h"

//50*400000 spin
void spin()
{
   int i = 0;
   int j = 0;
   int k = 0;
   for(i = 0; i < 50; ++i)
   {
      for(j = 0; j < 400000; ++j)
      {
         k = j % 10;
         k = k + 1;
      }
   }
}

int
main(int argc, char *argv[]){
//1. 각각 20, 10, 30개의 티켓을 가지고 있는 프로세스 생성
   int numtickets[]={20,10,30};
   int pid_chds[3];

   //1번 프로세스//
   pid_chds[0]=getpid();         //system call
   settickets(numtickets[0]);    //TODO

   //2, 3번 프로세스//
   int i;
   for(i=1;i<3;i++){
      pid_chds[i]=fork();        //process 분기
      if(pid_chds[i]==0){        //분기된 프로세스라면
         for (;;){               //spin lock
            spin();              //dummy 작업 실행
         }
      }
      else{
         settickets(numtickets[i]);    //부모 프로세스라면 티켓 할당
      }
   }

//2. 생성한 프로세스의 실행 시간 기록
   /* 부모 프로세스만 실행
    * pid_chds[] = 20, 10, 30
    * pid_chds[] = pid1, pid2, pid3
   **/
   struct pstat st;           //process state structure
   int time=0;
   int ticks[3]={0,0,0};      //각 프로세스의 실행 시간

   printf(1,"pid:%d, pid:%d, pid:%d\n",pid_chds[0],pid_chds[1],pid_chds[2]);
   printf(1,"tickets:%d, tickets:%d, tickets:%d\n",30,20,10);

   while(time<1000000){
      //현재 process의 정보 받아옴
      if(getpinfo(&st)!=0){
         printf(1,"check failed: getpinfo\n");
         goto Cleanup;
      }

      int j;
      int pid;
      for(i=0;i<3;i++){
         pid=pid_chds[i];
         for(j=0;j<NPROC;j++){         //전체 프로세스에 대하여
            if(st.pid[j]==pid){        //현재 진행 중인 프로세스의 tick에
               ticks[i]=st.ticks[j];   //프로세스 실행 시간 기록
               // printf(1,"pid:%d, tickets:%d, ticks:%d\n",pid,st.tickets[j],st.ticks[j]);
            }
         }
      }

      spin();        //pid3 spin
      time++;
   }

   for(i=0;i<3;i++){
      printf(1,"%d, ",ticks[i]);
   }
   printf(1,"\n");

Cleanup:
   for (i = 0; pid_chds[i] > 0; i++){
      kill(pid_chds[i]);
   }
   while(wait() > -1);

   exit();
}
