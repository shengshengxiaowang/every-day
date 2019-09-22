//读者写者问题
/*允许多位读者用时访问某数据，但是同一时间，只允许一位写者写入数据
当没有读者在读取数据的时候，才允许写者写入数据
当有写者正在写入数据的时候，不允许读者进行数据的读写
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

#define REANER_MAX 3      //最多允许多少人一起读取数据
#define WRITER_MAX 2      //最多允许多少人写数据
pthread_rwlock_t rw_lock; //读写锁

void *reader_thread(void *arg)
{
    while (1) //尝试加只读锁
    {
        if (pthread_rwlock_tryrdlock(&rw_lock))
        { //加只读锁不成功，打印信息，1秒钟后继续尝试
            printf("读\t者%u暂时不能读取数据.\n", (unsigned int)pthread_self());
            sleep(1);
        }
        else
        { //加只读锁成功，显示哪位读者正在进行数据读取
            printf("读\t者%u正在读取数据.\n", (unsigned int)pthread_self());
            sleep(1);
            printf("读\t者%u读取数据完毕.\n", (unsigned int)pthread_self());
            pthread_rwlock_unlock(&rw_lock);
            sleep(2); //休息一段时间后再尝试进行数据读取
        }
    }
}

void *writer_thread(void *arg)
{
    while (1)
    {
        if (pthread_rwlock_trywrlock(&rw_lock))
        {
            printf("写者%u暂时不能写入数据\n", (unsigned int)pthread_self());
            sleep(2);
        }
        else
        {
            printf("写者%u正在写入数据\n", (unsigned int)pthread_self());
            sleep(2);
            printf("写者%u写入数据完毕\n", (unsigned int)pthread_self());
            pthread_rwlock_unlock(&rw_lock);
            sleep(3);
        }
    }
}

int main(int argc, char *argv[])
{
    pthread_t reader, writer;            //记录读者和写者的线程号
    int i = 0;                           //循环变量
    pthread_rwlock_init(&rw_lock, NULL); //初始化读写锁
    //创建REANER_MAX个读者
    for (i = 0; i < REANER_MAX; i++)
    {
        pthread_create(&reader, NULL, reader_thread, NULL);
    }
    for (i = 0; i < WRITER_MAX; i++)
    {
        pthread_create(&writer, NULL, writer_thread, NULL);
    }
    sleep(10);
    return 0;
}
