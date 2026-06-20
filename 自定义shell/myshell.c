#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <unordered_map>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

//关于重定向
#define NONE_REDIR 0
#define INPUT_REDIR 1
#define OUTPUT_REDIR 2
#define APPEND_REDIR 3
int redir=NONE_REDIR;
string filename;

//全局环境变量
char **original_env=NULL;
#define COMMAND_SIZE 1024
int lastcode=0;
//命令行
#define MAX_ARGC 128
char *g_argv[MAX_ARGC];
int g_argc=0;

//环境变量
#define MAX_ENV 200
char *g_env[MAX_ENV];
int g_envs=0;

char cwd[1024];
//命令行解析
bool CommandParse(char *commandline)
{
#define Step " "
    g_argc=0;
    char *token=strtok(commandline,Step);
    if(token==nullptr) return false;

    g_argv[g_argc++]=token;
    while((token=strtok(nullptr,Step))!=nullptr)
            g_argv[g_argc++]=token;
    g_argv[g_argc]=NULL;
    return g_argc>0;
}

void Initenv()
{
    extern char **environ;
    original_env=environ;
    g_envs=0;

    memset(g_env,0,sizeof(g_env));

    for(int i=0;environ[i];i++)
    {
        g_env[i]=(char*)malloc(strlen(environ[i])+1);
        strcpy(g_env[i],environ[i]);
        g_envs++;
    }

    g_env[g_envs]=NULL;

    for(int i=0;g_env[i];i++)
    {
        putenv(g_env[i]);
    }

}
//家目录
const char *GetHome()
{
    const char * home=getenv("HOME");
    return home==NULL?"":home;
}
//用户名
const char* GetUserName()
{
    const char *name=getenv("USER");
    return name;
}

//主机名
const char *GetHostName()
{
    const char *hostname=getenv("HOSTNAME");
    return hostname;
}

//简单路径
string DirName(const char *pwd)
{
#define FLASH "/"
    
    std::string pos=pwd;
    if(pos==FLASH)
        return FLASH;
    auto p=pos.rfind(FLASH);
    if(p == string::npos) return "BUG?";
    return pos.substr(p+1);
}

//绝对路径
const char *GetPwd()
{
    // const char *pwd=getenv("PWD");
    
    const char *pwd=getcwd(cwd,sizeof(cwd));
    return pwd==NULL?"None":pwd;
}

bool Cd()
{
    if(g_argc==1||g_argv[1]=="~")
    {
        string where=GetHome();
        if(where.empty())
            return true;
        chdir(where.c_str());
    }
     
    else
    {
        string where =g_argv[1];
        if(where=="-")
        {
            //
        }

        else
            chdir(where.c_str());
    }

    return true;
}

void Echo()
{
    if(g_argc==2)
    {
        //cout<<g_argv[0]<<" "<<g_argv[1]<<endl;
        string opt=g_argv[1];
        if(opt=="$?")
        {
            cout<<lastcode<<endl;
        }

        else if(opt[0]=='$')
        {
            string env_name=opt.substr(1);
            cout<<getenv(env_name.c_str());
        }

        else
        {
            cout<<opt<<endl;
        }

        lastcode=0;
    }

}

bool GetCommandLine(char *out, int size)
{
        
        char *c=fgets(out,size,stdin);
        if(c==NULL) return false;
        c[strlen(c)-1]=0;
        if(strlen(c)==0) return false;
        return true;

}

void MakeCommandLine(char out[],int size)
{
    snprintf(out,size,"[%s@%s %s]# ",GetUserName(),GetHostName(),DirName(GetPwd()).c_str());
}

//释放环境变量
void FreeEnv()
{
    for(int i=0;g_env[i]!=NULL;i++)
    {
        free(g_env[i]);
        g_env[i]=NULL;
    }

    g_envs=0;

    environ=original_env;
}
void PrintCommandPrompt()
{
    char prompt[COMMAND_SIZE];
    MakeCommandLine(prompt,sizeof(prompt));
    printf("%s",prompt);
    fflush(stdout);
}

void TrimSpace(char *cmd,int& end)
{
    while(isspace(cmd[end]))
        end++;
}
void RedirCheck(char cmd[])
{
    redir=NONE_REDIR;
    filename.clear();
    // >> > 输出 
    // < 输入
    int end=strlen(cmd)-1;
    while(end>0)
    {
        if(cmd[end]=='<')
        {
            redir=INPUT_REDIR;
            cmd[end++]=0;
            TrimSpace(cmd,end);
            filename=cmd+end;
            break;
        }

        else if(cmd[end]=='>')
        {
            if(cmd[end-1]=='>')
            {
                cmd[end-1]=0;
                redir=APPEND_REDIR;
            }

            else
            {
                redir=OUTPUT_REDIR;
            }

            cmd[end++]=0;
            TrimSpace(cmd,end);
            filename=cmd+end;
            break;
        }

        else
            end--;
    }
}
int Execute()
{
    pid_t id=fork();
    if(id==0)
    {
        //子进程
        int fg=-1;
        if(redir==INPUT_REDIR)
        {
            fg=open(filename.c_str(),O_RDONLY);
            if(fg<0) exit(1);
            dup2(fg,0);
            close(fg);
        }

        else if(redir==OUTPUT_REDIR)
        {
            fg=open(filename.c_str(),O_CREAT | O_WRONLY | O_TRUNC, 0666);
            if(fg<0) exit(1);
            dup2(fg,1);
            close(fg);
        }


        else if(redir==APPEND_REDIR)
        {
            fg=open(filename.c_str(),O_CREAT | O_WRONLY | O_APPEND, 0666);
            if(fg<0) exit(1);
            dup2(fg,2);
            close(fg);
        }
        execvp(g_argv[0],g_argv);
        exit(0);

    }


    int status=0;
    pid_t wt=waitpid(id,&status,0);
    if(wt>0) lastcode=WEXITSTATUS(status);
    return 0;
}
bool CheckAndExecBuiltin()
{
    string where=g_argv[0];
    if(where=="cd")
    {
        Cd();
        return true;
    }

    if(where=="echo")
    {
        Echo();
        return true;
    }

    return false;
}
int main()
{
    while(1)
    {
        //命令行提示符
        PrintCommandPrompt();
        
        //获取命令行
        char commandline[COMMAND_SIZE];
        if(!GetCommandLine(commandline,sizeof(commandline)))
             continue;

        //重定向
        RedirCheck(commandline);
        //命令行解析
        if(!CommandParse(commandline))
            continue;

        //判断内建命令 
        if(CheckAndExecBuiltin())
            continue;
        //执行
        Execute();

        //释放环境变量
        
        FreeEnv();
    }
    return 0;
}

