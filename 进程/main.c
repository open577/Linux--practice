#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
//int main()
//{
    //printf("我的进程：%d\n",getpid());
  //  printf("我的父进程：%d\n",getppid());
//    return 0;
//}

//int main()
//{
//    int ret=fork();
  //  while(1)
   // {
   // printf("我是一个父进程：%d\n",getppid());
    //printf("我是一个子进程:%d,ret :%d\n",getpid(),ret);
    //sleep(1);
    //}
    //return 0;
//}
//


//int main()
//{
  //  pid_t id = fork();
     //   if(id == 0)
        //{
          //  //child
            //int count=5;
           // while(1)
            //{
              //  printf("我是一个子进程：%d\n",getpid());
                //sleep(1);
          ///  }
       // }
        
        //else
        //{
         //   while(1)
          //  {
           //     printf("我是一个父进程：%d\n",getpid());
             //   sleep(1);
           // }
        //}

        

       // return 0;
//
//
//}
//
//

//int main()
//{
//    int ret=fork();
//    if(ret<0)
//    {
//        perror("fork file!\n");
//        return 1;
//    }
//
//    else if(ret==0)
//    {
//        printf("我是一个子进程\n");
//    }
//
//    else 
//    {
//        printf("我是一个父进程\n");
//    }
//    return 0;
//
//}
//


//int main() 
//{
//    int val = 100;
//    pid_t pid = fork();
//        
//        if (pid == 0) 
//        {
//                // 子进程修改val的值
//                     int  val = 200;
//                         printf("子进程：val = %d，地址：%p\n", val, &val);
//        }
//                         else 
//                         {
//                                  
//                           sleep(1); // 等待子进程先执行
//                          printf("父进程：val = %d，地址：%p\n", val, &val);
//                                           
//                         }
//                                               
//             return 0;
//}

int main()
{

  while(1)
  {
    printf("我是一个进程,%d\n",getpid());
    sleep(1);
  }
  return 0;
}
